#include "MapReduceFramework.h"
#include <cstdlib>
#include <cstdio>
#include <atomic>
#include <list>
#include <algorithm>
#include <pthread.h>
#include <unistd.h>

struct JobContext;
struct ThreadContext;

// helper functions
void* threadRun(void* arg);
unsigned long getInputPairIndex(ThreadContext *tc);
unsigned long getInputPairIndex_after_reduce(ThreadContext *tc);
void map_next_pair(ThreadContext *tc, unsigned long index);
void reduce_next_pair(ThreadContext *tc, IntermediateVec cur_pairs);
void init_shuffle_data(JobContext *jobContext);
void shuffle_state(JobContext* jobContext);
void start_reduce_stage(JobContext *jobContext);
void sort_cur_thread_array(ThreadContext *tc);
void check_destroy(int check_input);

/**
 * class Barrier - make a barrier before the shuffle and release the thread after finish the shuffle
 */
class Barrier {
public:
	Barrier(int numThreads);
    void barrier(JobContext *jobContext);

private:
	int count;
	int numThreads;
};

/**
 * struct for each thread that has his IntermediateArray and  pointer to the job
 */
struct ThreadContext {
    int threadID;
    JobContext* jobContext;
    std::vector<IntermediatePair> IntermediateArray;  // READY order of threads
};

/**
 *  struct that hold all the information in this job
 */
struct JobContext{
    ThreadContext* contexts;
    int multiThreadLevel;
    Barrier* barrier;
    std::atomic<uint64_t>* atomic_counter;
    const InputVec* inputVec;
    OutputVec* outputVec;
    const MapReduceClient* client;
    pthread_t* threads;
    int flag_wait;
    pthread_mutex_t barrier_mutex;
    pthread_mutex_t vector_mutex;
    pthread_mutex_t counter_mutex;
    pthread_mutex_t stage_mutex;
    pthread_cond_t cv;
    std::vector<std::vector<IntermediatePair>> shuffleArray;
    JobState jobState;
    unsigned long max_size;
};

/**
 * constructor
 * @param numThreads - num of the thread that work in this job
 */
Barrier::Barrier(int numThreads):
         count(0)
        , numThreads(numThreads){}

/**
 * lock all the thread until the lest one, the lest one make the shuffle
 * change the state and the atomic counter before and after. once shuffle state finish unlock all the thread.
 * all the function in mutex
 * @param jobContext - struct that hold all the information in this job
 */
void Barrier::barrier(JobContext* jobContext)
{
    if (pthread_mutex_lock(&jobContext->barrier_mutex) != 0){
        fprintf(stderr, "[[Barrier]] error on pthread_mutex_lock");
        exit(1);
    }
    if (++count < numThreads) {
        //lock all the thread
        if (pthread_cond_wait(&jobContext->cv, &jobContext->barrier_mutex) != 0){
            fprintf(stderr, "[[Barrier]] error on pthread_cond_wait");
            exit(1);
        }
    } else {
        //the last thread do the shuffle
        shuffle_state(jobContext);
        start_reduce_stage(jobContext);
        //unlock all the thread for reduce state
        if (pthread_cond_broadcast(&jobContext->cv) != 0) {
            fprintf(stderr, "[[Barrier]] error on pthread_cond_broadcast");
            exit(1);
        }
    }
    if (pthread_mutex_unlock(&jobContext->barrier_mutex) != 0) {
        fprintf(stderr, "[[Barrier]] error on pthread_mutex_unlock");
        exit(1);
    }
}

/**
 * get a pair of key value and push it to the IntermediateArray of the thread that send this pair
 * all the function is in mutex
 * @param key - the key of the IntermediatePair
 * @param value - the value of the IntermediatePair
 * @param context - struct that belong to the thread that send this pair and has the IntermediateArray
 */
void emit2 (K2* key, V2* value, void* context){
    ThreadContext* tc = (ThreadContext*) context;
    // add new key to the IntermediateArray of the thread
    IntermediatePair cur_pair;
    cur_pair.first = key;
    cur_pair.second = value;
    // add +1 to the num of processed pairs
    if (pthread_mutex_lock(&tc->jobContext->vector_mutex) != 0){
        fprintf(stderr, "[[After Map, Before +1 processed pairs]] error on pthread_mutex_lock");
        exit(1);
    }
    (tc->IntermediateArray).push_back(cur_pair); // add new value to array of mapped values of this thread
    if (pthread_mutex_unlock(&tc->jobContext->vector_mutex) != 0){
        fprintf(stderr, "[[After Map, After +1 processed pairs]] error on pthread_mutex_unlock");
        exit( 1);
    }
}

/**
 * get a pair of key value and push it to the OutputArray of the thread that send this pair
 * all the function is in mutex
 * @param key - the key of the OutputPair
 * @param value - the value of the OutputPair
 * @param context - struct that belong to the thread that send this pair and has the IntermediateArray
 */
void emit3 (K3* key, V3* value, void* context){
    ThreadContext* tc = (ThreadContext*) context;
    OutputPair cur_pair;
    cur_pair.first = key;
    cur_pair.second = value;
    // add +1 to the num of processed pairs
    if (pthread_mutex_lock(&tc->jobContext->vector_mutex) != 0){
        fprintf(stderr, "[[After Reduce, Before +1 processed pairs]] error on pthread_mutex_lock");
        exit(1);
    }
    (tc->jobContext->outputVec)->push_back(cur_pair); // add new value to output vector
    if (pthread_mutex_unlock(&tc->jobContext->vector_mutex) != 0){
        fprintf(stderr, "[[After Reduce, After +1 processed pairs]] error on pthread_mutex_unlock");
        exit(1);
    }
}

/**
 * init the jobContext struct and make all the thread create
 * @param client - the client that give the input vector, and the map and reduce functions
 * @param inputVec - the input vector with the date to map reduce
 * @param outputVec - the vector with the finish values from the map and reduce
 * @param multiThreadLevel - num of the thread to create
 * @return - struct that hold all the information in this job
 */
JobHandle startMapReduceJob(const MapReduceClient& client,
                            const InputVec& inputVec, OutputVec& outputVec,
                            int multiThreadLevel){
    //init argument for job context and init the job context
    pthread_t* threads = new pthread_t[multiThreadLevel] ;
    Barrier* barrier = new Barrier(multiThreadLevel);
    std::atomic<uint64_t>* atomic_counter = new std::atomic<uint64_t>;
    (*atomic_counter).operator=(0);
    ThreadContext* contexts = new ThreadContext[multiThreadLevel] ;
    JobContext* jobContext  = new JobContext;
    for (int i = 0; i < multiThreadLevel; ++i) {
        contexts[i] = {i, jobContext};
    }
    *jobContext = {contexts,multiThreadLevel, barrier,atomic_counter,  &inputVec,
                   &outputVec, &client, threads, 0};

    jobContext->cv = PTHREAD_COND_INITIALIZER;
    jobContext->barrier_mutex = PTHREAD_MUTEX_INITIALIZER;
    jobContext->vector_mutex = PTHREAD_MUTEX_INITIALIZER;
    jobContext->stage_mutex = PTHREAD_MUTEX_INITIALIZER;
    jobContext->counter_mutex = PTHREAD_MUTEX_INITIALIZER;
    jobContext->max_size = inputVec.size();
    jobContext->jobState = {UNDEFINED_STAGE, 0};
    // make array of pairs for each thread
    for (int i = 0; i < multiThreadLevel; ++i) {
        pthread_create(&threads[i], nullptr, threadRun, contexts + i);
    }
    return jobContext;
}

/**
 * the function of the theard that run the map and reduce
 * @param arg - ThreadContext struct that belong to the thread
 */
void* threadRun(void* arg){
    ThreadContext* tc = (ThreadContext*) arg;
    // map state
    tc->jobContext->jobState.stage = MAP_STAGE;
    unsigned long InputPairIndex = 0;
    while(InputPairIndex < (tc->jobContext->inputVec)->size()){
        //take the next index to take from vector
        InputPairIndex = getInputPairIndex(tc);
        if(InputPairIndex >= (tc->jobContext->inputVec)->size()){
            break;
        }
//        const InputVec our_vec = *tc->jobContext->inputVec;
//        const InputPair cur_pair = (tc->jobContext->inputVec)->at(InputPairIndex);
        map_next_pair(tc, InputPairIndex);
    }
    // sort state
    sort_cur_thread_array(tc);
    // barrier after map and sort
    tc->jobContext->barrier->barrier(tc->jobContext);
    //finish the shuffle state and start reduce state
    unsigned long OutputPairIndex = 0;
    unsigned long shuffle_len = (tc->jobContext->shuffleArray.size());
    while(OutputPairIndex < shuffle_len){
        //take the next index to take from vector
        OutputPairIndex = getInputPairIndex_after_reduce(tc);
        if(OutputPairIndex >= shuffle_len){
            break;
        }
        std::vector<std::vector<IntermediatePair>> cur_vec = tc->jobContext->shuffleArray;
        const IntermediateVec cur_pairs_vec = tc->jobContext->shuffleArray.at(OutputPairIndex);
        reduce_next_pair(tc, cur_pairs_vec);
    }
}

/**
 * take the next index and add 1 to the atomic counter
 * @param tc - ThreadContext struct that belong to the thread
 * @return the next index in the array that the thread need to work on
 */
unsigned long getInputPairIndex(ThreadContext *tc) {
    // get next valid input
    if (pthread_mutex_lock(&tc->jobContext->counter_mutex) != 0){
        fprintf(stderr, "[[Before Map, Before Get Next Input]] error on pthread_mutex_lock");
        exit(1);
    }
    unsigned long mask;
    mask = (1 << 31) - 1;
    unsigned long cur_value = (tc->jobContext->atomic_counter->load());
    unsigned long next_value_index = cur_value & mask; // first 31 bit - the num of unmapped values
    (*(tc->jobContext->atomic_counter))++;
    if (pthread_mutex_unlock(&tc->jobContext->counter_mutex) != 0) {
        fprintf(stderr, "[[Before Map, After Get Next Input]] error on pthread_mutex_unlock");
        exit(1);
    }
    return next_value_index;
}

/**
 * take the next index and add 1 to the atomic counter
 * @param tc - ThreadContext struct that belong to the thread
 * @return the next index in the array that the thread need to work on
 */
unsigned long getInputPairIndex_after_reduce(ThreadContext *tc) {
    // get next valid input
    if (pthread_mutex_lock(&tc->jobContext->counter_mutex) != 0){
        fprintf(stderr, "[[Before Reduce, Before Get Next Input]] error on pthread_mutex_lock");
        exit(1);
    }
    unsigned long mask;
    mask = (1 << 31) - 1;
    unsigned long cur_value = (tc->jobContext->atomic_counter->load());
    unsigned long next_value_index = cur_value & mask; // first 31 bit - the num of unmapped values
    (*(tc->jobContext->atomic_counter))++;
    if (pthread_mutex_unlock(&tc->jobContext->counter_mutex) != 0) {
        fprintf(stderr, "[[Before Reduce, After Get Next Input]] error on pthread_mutex_unlock");
        exit(1);
    }
    return next_value_index;
}

/**
 * send the pair to the map func and add that one finish to the atomic counter
 * @param tc - ThreadContext struct that belong to the thread
 * @param cur_pair pair of key value that map function get
 */
void map_next_pair(ThreadContext *tc, unsigned long i) {
    // use map on cur_pair
(*(tc->jobContext->client)).map((tc->jobContext->inputVec)->at(i).first, (tc->jobContext->inputVec)->at(i).second, tc);

    if (pthread_mutex_lock(&tc->jobContext->counter_mutex) != 0){
        fprintf(stderr, "[[After Map, Before +1 processed pairs]] error on pthread_mutex_lock");
        exit(1);
    }
    //add one to the finish map pairs
    (*(tc->jobContext->atomic_counter)) += 0x80000000;  // + 8 equal 1000, 0 equal 0000, we have 3+4*7=31 zero
    unsigned long done_precessed = (tc->jobContext->atomic_counter)->load() >> 31 & (0x7fffffff);
    tc->jobContext->jobState.percentage = ((float)done_precessed) / (float)tc->jobContext->max_size *100;
    if (pthread_mutex_unlock(&tc->jobContext->counter_mutex) != 0){
        fprintf(stderr, "[[After Map, After +1 processed pairs]] error on pthread_mutex_lock");
        exit(1);
    }
}

/**
 * send the pair to the reduce func and add that one finish to the atomic counter
 * @param tc - ThreadContext struct that belong to the thread
 * @param cur_pair pair of key value that reduce function get
 */
void reduce_next_pair(ThreadContext *tc, const IntermediateVec cur_pairs) {
    // use map on cur_pair
    (*(tc->jobContext->client)).reduce(&cur_pairs, tc);
    if (pthread_mutex_lock(&tc->jobContext->counter_mutex) != 0){
        fprintf(stderr, "[[After Reduce, Before +1 processed pairs]] error on pthread_mutex_lock");
        exit(1);
    }
    //add one to the finish reduce pairs
    (*(tc->jobContext->atomic_counter)) += 0x80000000;  // + 8 equal 1000, 0 equal 0000, we have 3+4*7=31 zero
    unsigned long done_precessed = (tc->jobContext->atomic_counter)->load() >> 31 & (0x7fffffff);
    tc->jobContext->jobState.percentage = ((float)done_precessed) / (float)tc->jobContext->max_size * 100;
    if (pthread_mutex_unlock(&tc->jobContext->counter_mutex) != 0){
        fprintf(stderr, "[[After Reduce, After +1 processed pairs]] error on pthread_mutex_lock");
        exit(1);
    }
}

/**
 * change the state to shuffle and init the atomic counter to 0 finish and
 * count all the pair and add in the 31 bit the count
 * @param jobContext - struct that hold all the information in this job
 */
void init_shuffle_data(JobContext *jobContext) {//change the state of job to shuffle
    if (pthread_mutex_lock(&jobContext->stage_mutex) != 0){
        fprintf(stderr, "[[After Map, Before Shuffle]] error on pthread_mutex_lock");
        exit(1);
    }
    (jobContext->atomic_counter)->operator=(0);
    (*(jobContext->atomic_counter)) += 0x8000000000000000;  // + 8 equal 1000, 0 equal 0000, we have 3+4*15=63 zero
    jobContext->jobState = {SHUFFLE_STAGE, 0};
    unsigned long count = 0;
    for (int i = 0; i < jobContext->multiThreadLevel;i++){
        count += (jobContext->contexts + i)->IntermediateArray.size();
    }
    jobContext->max_size = count;
    (*(jobContext->atomic_counter)) += 0x80000000 * count;  // + 8 equal 1000, 0 equal 0000, we have 3+4*7=31 zero
    if (pthread_mutex_unlock(&jobContext->stage_mutex) != 0){
        fprintf(stderr, "[[After Map, Before Shuffle]] error on pthread_mutex_unlock");
        exit(1);
    }
}

/**
 * in loop take the biggest key chack in ak the thread and add all the pair with this key
 * to vector and add the vector to the shuffleArray
 * @param jobContext - struct that hold all the information in this job
 */
void shuffle_state(JobContext* jobContext){
    std::vector<IntermediatePair> cur_array;
    float finish_count = 0;
    IntermediatePair biggest_pair;
    init_shuffle_data(jobContext);
    while (jobContext->jobState.percentage < 100) {
        //find same key to start
        for(int i = 0; i < jobContext->multiThreadLevel; i++){
            cur_array = jobContext->contexts[i].IntermediateArray;
            if(cur_array.size() > 0){
                biggest_pair = cur_array.at(cur_array.size()-1);
                break;
            }
        }
        //take the biggest key
        for (int i = 0; i < jobContext->multiThreadLevel; i++) {
            cur_array = (jobContext->contexts + i)->IntermediateArray;
            if (!cur_array.empty()){
                if (!(*cur_array.at(cur_array.size()-1).first < *biggest_pair.first)) {
                    biggest_pair = cur_array.at(cur_array.size() - 1);
                }
            }
        }
        //made vector for this key
        std::vector<IntermediatePair> key_biggest_vector;
        for (int i = 0; i < jobContext->multiThreadLevel; i++) {
            cur_array = (jobContext->contexts + i)->IntermediateArray;
            //finish this array
            while (!cur_array.empty() && !(*cur_array.at(cur_array.size()-1).first < *biggest_pair.first) &&
            !(*biggest_pair.first < *cur_array.at(cur_array.size()-1).first)) {
                //check if the least one of all the thread vector is good for this vector
                bool check_eq = !(*cur_array.at(cur_array.size()-1).first < *biggest_pair.first) &&
                        !(*biggest_pair.first < *cur_array.at(cur_array.size()-1).first);
                if(check_eq){
                    //insert to the vector, delete, update the percentage
                    key_biggest_vector.push_back(cur_array.at(cur_array.size()-1));
                    cur_array.pop_back();
                    (jobContext->contexts + i)->IntermediateArray.pop_back();
                    (*(jobContext->atomic_counter))++;
                    finish_count += 1;
                    jobContext->jobState.percentage = finish_count/(float) jobContext->max_size * 100;
                }
            }
        }
        jobContext->shuffleArray.push_back(key_biggest_vector);
    }
}

/**
 *  change the state to reduce and init the atomic counter to 0
 * @param jobContext - struct that hold all the information in this job
 */
void start_reduce_stage(JobContext *jobContext){
    jobContext->max_size = jobContext->shuffleArray.size();
    //change the state and atomic_counter to reduce
    if (pthread_mutex_lock(&jobContext->stage_mutex) != 0){
        fprintf(stderr, "[[After Shuffle, Before Reduce]] error on pthread_mutex_lock");
        exit(1);
    }
    (jobContext->atomic_counter)->operator=(0);
    (*(jobContext->atomic_counter)) += 0x8000000000000000;  // + 8 equal 1000, 0 equal 0000, we have 3+4*15=63 zero
    (*(jobContext->atomic_counter)) += 0x4000000000000000;  // + 4 equal 0100, 0 equal 0000, we have 2+4*15=62 zero
    jobContext->jobState = {REDUCE_STAGE, 0.0f};
    if (pthread_mutex_unlock(&jobContext->stage_mutex) != 0){
        fprintf(stderr, "[[After Shuffle, Before Reduce]] error on pthread_mutex_lock");
        exit(1);
    }
}

/**
 * @param pair1 - IntermediatePair
 * @param pair2 -IntermediatePair
 * @return pair1 key > pair2 key
 */
bool cmp(const IntermediatePair &pair1, const IntermediatePair &pair2) {
    return *pair1.first < *pair2.first;
}

/**
 * sort the IntermediateArray
 * @param tc ThreadContext struct that belong to the thread
 */
void sort_cur_thread_array(ThreadContext *tc) {
    std::sort((tc->IntermediateArray).begin(),
              (tc->IntermediateArray).end(), cmp); // also sorts by key
}

/**
 * hold the current running until the job will be finished.
 * we will split the behaviour into 3 options by flag_wait. (0 = join(wait) for all the threads,
 *                                                           1 = wait for already waiting thread
 *                                                           2 = the job already finished - dont wait)
 * @param job struct that hold all the information in this job
 */
void waitForJob(JobHandle job){
    JobContext* cur_job = ((JobContext*) job);
    // job already finished
    if(cur_job->flag_wait == 2){
        return;
    }
    // first time we enter this function - wait for all the threads to terminate
    if (cur_job->flag_wait == 0){
        cur_job->flag_wait = 1;
        for (int i = 0; i < cur_job->multiThreadLevel; i++) {
            pthread_join(cur_job->threads[i], NULL);
        }
        if (pthread_cond_broadcast(&cur_job->cv) != 0) {
            fprintf(stderr, "[[Barrier]] error on pthread_cond_broadcast");
            exit(1);
        }
        cur_job->flag_wait = 2;
    }
    // more than one time we enter this function and the job still processing.
    if (cur_job->flag_wait == 1){
        if (pthread_cond_wait(&cur_job->cv, &cur_job->barrier_mutex) != 0){
            fprintf(stderr, "[[Barrier]] error on pthread_cond_wait");
            exit(1);
        }
    }
}

/**
 * take the JobState from the struct JobContext all the function is in mutex
 * @param job - struct that hold all the information in this job
 * @param state - JobState to insert the job state
 */
void getJobState(JobHandle job, JobState* state){
    JobContext* cur_job = (JobContext*)job;
    if (pthread_mutex_lock(&cur_job->stage_mutex) != 0){
        fprintf(stderr, "[[In getJobState]] error on pthread_mutex_lock");
        exit(1);
    }
    *state = ((JobContext*) job)->jobState;
    if (pthread_mutex_unlock(&cur_job->stage_mutex) != 0){
        fprintf(stderr, "[[In getJobState]] error on pthread_mutex_unlock");
        exit(1);
    }

}

/**
 * delete all the memory and destroy all the mutex/cond
 * @param job  - struct that hold all the information in this job
 */
void closeJobHandle(JobHandle job){
    waitForJob(job);
    JobContext* cur_job = ((JobContext*) job);
    check_destroy(pthread_mutex_destroy(&cur_job->barrier_mutex));
    check_destroy(pthread_mutex_destroy(&cur_job->stage_mutex));
    check_destroy(pthread_mutex_destroy(&cur_job->counter_mutex));
    check_destroy(pthread_mutex_destroy(&cur_job->vector_mutex));
    check_destroy(pthread_cond_destroy(&cur_job->cv));
    delete[] cur_job->threads;
    delete[] cur_job->contexts;
    delete cur_job->atomic_counter;
    delete cur_job->barrier;
    delete cur_job;
}

/**
 * check if the destroy of the mutex or cond work , if not print and exit
 * @param check_input - function to check
 */
void check_destroy(int check_input) {
    if (check_input != 0) {
        fprintf(stderr, "[[closeJobHandle]] error on pthread_mutex/cond_destroy");
        exit(1);
    }
}
