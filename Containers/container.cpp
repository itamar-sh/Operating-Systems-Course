
#include<sched.h>
#include <cstring>
#include <sys/wait.h>
#include <list>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mount.h>
#include <string>
#include <fstream>

using namespace std;

#define STACK 8192
#define  PID 1
#define PERMISSIONS 0755

#define  PROC "proc"
#define S_PROC "/proc"
#define FS_DIR "/sys/fs"
#define CGROUP_DIR "/sys/fs/cgroup"
#define PIDS_DIR "/sys/fs/cgroup/pids"
#define MAX_DIR "/sys/fs/cgroup/pids/pids.max"
#define PROCS_DIR "/sys/fs/cgroup/pids/cgroup.procs"
#define RELEASE_DIR "/sys/fs/cgroup/pids/notify_on_release"
#define  OPEN_ERROR "system error: %s not open\n"
#define  FUNC_ERROR "system error: %s not work\n"

#define  HOST_NAME "sethostname"
#define CHROOT "chroot"
#define CHDIR "chdir"
#define MOUNT "mount"
#define UMOUNT "umount"
#define EXECVP "execvp"
#define MKDIR "mkdir"
#define REMOVE "remove"
#define RMDIR "rmdir"

/**
 * struct that wrap the value of argv
 */
struct Arg {
    char* new_hostname;
    char* new_filesystem_directory;
    char* num_processes;
    char* path_to_program_to_run_within_container;
    char** args_for_program;
};

void make_path_to_pids(char* num_processes);

void check_func_success(int value, const string& type);

void close_files(Arg* arg);

/**
 * func that run on new container
 * @param arg - arg struct with all the args from the command line
 * @return 0 on success
 */
int child(void* arg) {
    Arg* new_arg = (Arg*) arg;
    check_func_success(sethostname(new_arg->new_hostname, strlen(new_arg->new_hostname)), HOST_NAME);
    check_func_success(chroot(new_arg->new_filesystem_directory), CHROOT);
    check_func_success(chdir(new_arg->new_filesystem_directory), CHDIR);
    make_path_to_pids(new_arg->num_processes);
    check_func_success(mount(PROC, S_PROC, PROC, 0, 0), MOUNT);
    check_func_success(execvp(new_arg->path_to_program_to_run_within_container, new_arg->args_for_program), EXECVP);
    return 0;
}

/**
 *
 * @param num_processes
 */
void make_path_to_pids(char* num_processes) {
    check_func_success(mkdir(FS_DIR, PERMISSIONS), MKDIR);
    check_func_success(mkdir(CGROUP_DIR, PERMISSIONS), MKDIR);
    check_func_success(mkdir(PIDS_DIR, PERMISSIONS), MKDIR);
    ofstream file1;
    file1.open(PROCS_DIR);
    if (!file1.is_open()){
        fprintf( stderr, OPEN_ERROR, PROCS_DIR);
        exit(1);
    }
    file1 << PID;
    file1.close();
    ofstream file2;
    file2.open(MAX_DIR);
    if (!file2.is_open()){
        fprintf( stderr, OPEN_ERROR, MAX_DIR);
        exit(1);
    }
    file2 << num_processes;
    file2.close();
    ofstream file3;
    file3.open(RELEASE_DIR);
    if (!file3.is_open()){
        fprintf( stderr, OPEN_ERROR , RELEASE_DIR);
        exit(1);
    }
    file3 << PID;
    file3.close();
}

/**
 * template for code that could lead to error
 * @param value 0 is success other value on error
 * @param type kind of error
 */
void check_func_success(int value, const string& type) {
    if (value != 0){
        fprintf( stderr, FUNC_ERROR, type.c_str());
        exit(1);
    }
}

/**
 * main func that handle fcalling to container
 * @param argc num of args
 * @param argv array of char* of input
 * @return 0 in success
 */
int main(int argc, char* argv[]) {
    char* stack = new char[STACK];
    char** args_for_program = new char*[argc - 3];
    for (int i = 4; i< argc; i++){
        *(args_for_program+i-4) = argv[i];
    }
    *(args_for_program + argc - 4) = (char*) 0;
    Arg* arg = new Arg;
    *arg = {argv[1], argv[2], argv[3], argv[4], args_for_program};
    int child_pid = clone(child, (void *)(stack+STACK), CLONE_NEWPID | SIGCHLD |CLONE_NEWUTS | CLONE_NEWNS, arg);
    wait(nullptr);
    close_files(arg);
    delete[] stack;
    delete[] args_for_program;
    return 0;
}

/**
 * func that close file and end running
 * @param arg - arg struct with all the args from the command line
 */
void close_files(Arg* arg) {
    string name = string(arg->new_filesystem_directory);
    string to_remove  = name + string(PROCS_DIR);
    check_func_success(remove(to_remove.c_str()), REMOVE);
    to_remove  = name + string(MAX_DIR);
    check_func_success(remove(to_remove.c_str()), REMOVE);
    to_remove  = name + string(RELEASE_DIR);
    check_func_success(remove(to_remove.c_str()), REMOVE);
    to_remove  = name + string(PIDS_DIR);
    check_func_success(rmdir(to_remove.c_str()), RMDIR);
    to_remove  = name + string(CGROUP_DIR);
    check_func_success(rmdir(to_remove.c_str()), RMDIR);
    to_remove  = name + string(FS_DIR);
    check_func_success(rmdir(to_remove.c_str()), RMDIR);
    to_remove  = name + string(S_PROC);
    check_func_success(umount(to_remove.c_str()), UMOUNT);
}

