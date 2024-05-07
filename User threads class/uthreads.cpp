//
// Created by itama on 31/03/2022.
//
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <map>
#include <list>
#include <algorithm>
#include <ostream>
#include <iostream>
#include "uthreads.h"

#define ERROR_RETURN -1;
#define SUCCED_RETURN 0;
#define ALLOC_ERROR "system error: the allocation failed"
#define INPUT_ERROR "system error: the input value is invalid"
#define SIG_ERROR "system error: the signal action not work"
#define PLACE_ERROR "system error: no place to a new thread"
#define SLEEP_ERROR "system error: thread 0 cant go to sleep"


#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
                 "rol    $0x11,%0\n"
    : "=g" (ret)
    : "0" (addr));
    return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5


/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
                 "rol    $0x9,%0\n"
    : "=g" (ret)
    : "0" (addr));
    return ret;
}
#endif

typedef struct thread_struct {
    char* stack;
    bool is_blocked;
    int num_of_thread_quantums;
    int sleeping_time;
} thread_struct;

// global values
signed int cur_thread = 0;
sigjmp_buf env[MAX_THREAD_NUM+1];
int QUANTUM_USECS;
std::map<unsigned int, thread_struct> tmap;
std::list<unsigned int> tqueue;
std::list<unsigned int> sleeping_threads;
int min_empty_id[MAX_THREAD_NUM+1];
int num_of_quantums;
sigset_t new_set;
struct sigaction sa = {0};
struct itimerval timer;
int therad_to_terminate = -1;
int change_thread = 0;

void timer_handler(int sig);


unsigned int min_id(){
    for (int i=1;i<MAX_THREAD_NUM+1;i++){
        if (min_empty_id[i]==0){
            return i;
        }
    }
    std::cerr << PLACE_ERROR << std::endl;
    exit(1);  // all threads are used

    return *(std::min_element(begin(tqueue), end(tqueue)));
}

// we already saved last thread state. only need to run a new thread.
void activate_next_thread(){
    change_thread = 1;
    // sets quantums numbers
    num_of_quantums += 1;
    // find next thread
    unsigned int next_tid = *tqueue.begin();
    tqueue.pop_front();
    // sets thread quantums numbers
    tmap.find(next_tid)->second.num_of_thread_quantums += 1;
    //check if time_sleep is over and put the thread in the queue;
    int to_remove = -1;
    for (unsigned int &i : sleeping_threads){
        thread_struct thread = tmap.find(i)->second;
        if (to_remove != -1){
            sleeping_threads.remove(to_remove);
            to_remove = -1;
        }
        if (thread.sleeping_time == uthread_get_total_quantums()){
            to_remove = i;
            if (!thread.is_blocked){
                tqueue.push_back(i);
            }
        }
    }
    if (to_remove != -1){
        sleeping_threads.remove(to_remove);
    }
    //check if there is thread to deleta
    if (therad_to_terminate != -1){
        free(tmap.find(therad_to_terminate)->second.stack);
        // delete from map
        tmap.erase(therad_to_terminate);
        // delete from queue
        tqueue.remove(therad_to_terminate);
        therad_to_terminate = -1;
    }
    timer.it_value.tv_sec = 0;        // first time interval, seconds part
    timer.it_value.tv_usec = QUANTUM_USECS;        // first time interval, microseconds part
    // Start a virtual timer. It counts down whenever this process is executing.
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL))
    {
        std::cerr << SIG_ERROR << std::endl;
        exit(1);
    }
    // run next thread
    cur_thread = next_tid;
    change_thread = 0;
    sigprocmask( SIG_UNBLOCK, &new_set, NULL );
    siglongjmp(env[next_tid], 1);
}

void timer_handler(int sig)
{
    if(sig != 26){
        return;
    }
    if (change_thread == 1){
        return;
    }
    tqueue.push_back(cur_thread);
    int ret_val = sigsetjmp(env[cur_thread], 1);
    bool did_just_save_bookmark = ret_val == 0;
    // jump to the next thread
    if (did_just_save_bookmark)
    {
        activate_next_thread();
    }

}

int uthread_init(int quantum_usecs){
    if (quantum_usecs <= 0){
        std::cerr << INPUT_ERROR << std::endl;
        return ERROR_RETURN;   // invalid input for virtual time
    }
    num_of_quantums = 1;
    QUANTUM_USECS = quantum_usecs;
    for (int & i : min_empty_id){
        i = 0;
    }
    thread_struct new_struct;
    new_struct.num_of_thread_quantums = 1;
    tmap.insert({0,new_struct});
    sa.sa_handler = &timer_handler;  // Install timer_handler as the signal handler for SIGVTALRM.
    if (sigaction(SIGVTALRM, &sa, NULL) < 0)
    {
        std::cerr << SIG_ERROR << std::endl;
        exit(1);
    }
    timer.it_value.tv_sec = 0;        // first time interval, seconds part
    timer.it_value.tv_usec = QUANTUM_USECS;        // first time interval, microseconds part
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL))
    {
        std::cerr << SIG_ERROR << std::endl;
        exit(1);
    }
    return SUCCED_RETURN;
}

int uthread_spawn(thread_entry_point entry_point){
    sigemptyset( &new_set );
    sigaddset( &new_set, SIGVTALRM );
    sigprocmask( SIG_BLOCK, &new_set, NULL);
    // validation
    if (entry_point == NULL){
        std::cerr << INPUT_ERROR << std::endl;
        return ERROR_RETURN; // no function as input
    }
    // struct init
    thread_struct new_struct;
    new_struct.is_blocked = false;
    new_struct.sleeping_time = 0;
    new_struct.stack = (char *) calloc(STACK_SIZE, sizeof (char));
    new_struct.num_of_thread_quantums = 0;
    if (new_struct.stack == NULL){
        std::cerr << ALLOC_ERROR << std::endl;  // no space in heap
        exit(1);
    }
    // id insert
    unsigned int tid = min_id();
    min_empty_id[tid] = 1;
    // initializes env[tid] to use the right stack, and to run from the function 'entry_point', when we'll use
    // siglongjmp to jump into the thread.
    address_t sp = (address_t) new_struct.stack + STACK_SIZE - sizeof(address_t);
    address_t pc = (address_t) entry_point;
    sigsetjmp(env[tid], 1);
    (env[tid]->__jmpbuf)[JB_SP] = translate_address(sp);
    (env[tid]->__jmpbuf)[JB_PC] = translate_address(pc);
    sigemptyset(&env[tid]->__saved_mask);
    //add to map and queue
    tmap.insert({tid,new_struct});
    tqueue.push_back(tid);
    sigprocmask( SIG_UNBLOCK, &new_set, NULL );
    return tid;
}

int uthread_terminate(int tid){
    if (tid == 0){
        exit(1);
    }
    sigemptyset( &new_set );
    sigaddset( &new_set, SIGVTALRM );
    sigprocmask( SIG_BLOCK, &new_set, NULL);
    // check if thread is exist
    if(tmap.find(tid) == tmap.end()){
        std::cerr << INPUT_ERROR << std::endl;
        return ERROR_RETURN;
    }
    // check if tid isn't himself
    if (cur_thread == tid){
        therad_to_terminate = tid;
        activate_next_thread();
    }
    else {
        // dealloc from structure
        thread_struct cur_thread = tmap.find(tid)->second;
        free(cur_thread.stack);
        // delete from map
        tmap.erase(tid);
        // delete from queue
        tqueue.remove(tid);
        // return tid to num of threads available
        min_empty_id[tid] = 0;
        sigprocmask(SIG_UNBLOCK, &new_set, NULL);
    }
    return SUCCED_RETURN;
}

int uthread_block(int tid){
    if (tid == 0){
        std::cerr << INPUT_ERROR << std::endl;
        return ERROR_RETURN;  // thread 0 cant blocked
    }
    sigemptyset( &new_set );
    sigaddset( &new_set, SIGVTALRM );
    sigprocmask( SIG_BLOCK, &new_set, NULL);
    // check if thread is exist
    if(tmap.find(tid) == tmap.end()){
        std::cerr << INPUT_ERROR << std::endl;
        return ERROR_RETURN;  // thread not exist
    }
    // change his attribute to BLOCKED
    tmap.find(tid)->second.is_blocked = true;
    // the current thread is the thread to block
    if (cur_thread == tid){
        // save thread state
        int ret_val = sigsetjmp(env[tid], 1);
        bool did_just_save_bookmark = ret_val == 0;
        // jump to the next thread
        if (did_just_save_bookmark)
        {
            activate_next_thread();
        }
    } else{
        // delete from queue
        tqueue.remove(tid);
    }
    sigprocmask( SIG_UNBLOCK, &new_set, NULL );
    return SUCCED_RETURN;
}

int uthread_resume(int tid){
    sigemptyset( &new_set );
    sigaddset( &new_set, SIGVTALRM );
    sigprocmask( SIG_BLOCK, &new_set, NULL);
    // check if the thread exist
    if(tmap.find(tid) == tmap.end()){
        std::cerr << INPUT_ERROR << std::endl;
        return ERROR_RETURN;  // thread not exist
    }
    // change his attribute to not BLOCKED
    tmap.find(tid)->second.is_blocked = false;
    // return to the queue if not already there
    if (std::find(tqueue.begin(), tqueue.end(), tid) == tqueue.end()){
        tqueue.push_back(tid);
    }
    sigprocmask( SIG_UNBLOCK, &new_set, NULL );
    return SUCCED_RETURN;
}

int uthread_sleep(int num_quantums){
    if (cur_thread == 0){
        std::cerr << SLEEP_ERROR << std::endl;
        return ERROR_RETURN;  // thread 0 cant sleep
    }
    sigemptyset( &new_set );
    sigaddset( &new_set, SIGVTALRM );
    sigprocmask( SIG_BLOCK, &new_set, NULL);
    if (num_quantums < 0){
        return ERROR_RETURN;
    }
    unsigned int tid = cur_thread;
    tmap.find(tid)->second.sleeping_time = num_quantums + uthread_get_total_quantums();
    sleeping_threads.push_back(tid);

    //save the information and go to next thread
    int ret_val = sigsetjmp(env[tid], 1);
    bool did_just_save_bookmark = ret_val == 0;
    // jump to the next thread
    if (did_just_save_bookmark)
    {
        activate_next_thread();
    }
    sigprocmask( SIG_UNBLOCK, &new_set, NULL );
    return SUCCED_RETURN;
}

int uthread_get_tid(){
    return cur_thread;
}

int uthread_get_total_quantums(){
    return num_of_quantums;
}

int uthread_get_quantums(int tid){
    if(tmap.find(tid) == tmap.end()){
        std::cerr << INPUT_ERROR << std::endl;
        return ERROR_RETURN;  // thread not exist
    }
    return tmap.find(tid)->second.num_of_thread_quantums;  // weird behaviour
}
