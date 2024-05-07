# Operating Systems Course
Threads, Processes, Mutex, Semaphores, Page Tables, VM, Containers and even Sockets.


## Run Time of System Calls
Trying using System calls in Container and VM.<br/>
Checking System calls of Trap, empty function and single addition instrucion.<br/>
using system calls like: strace, openat, fstat, write, close, unlink, rmdir.


## User Thread Class
Building class of user level thread using interrupts.<br/>
Using sigsetjmp and siglongjmp to jump between threads. Mainly using holding the context of each thread like PC and SP.<br/>
Advantages for using user threads are small overhead compared to processes and not requiring OS to communicate compared to kernel threads.