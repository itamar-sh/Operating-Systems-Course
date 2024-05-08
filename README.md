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


## MapReduce - Multi Threaded programming
MapReduce is used to parallelise tasks of a specific structure with generic types.<br/>
The framework we built supports asynchronic jobs, together with ability to query the current state of a job while it is running.<br/>
In short, this is how the process should go:<br/>
<img
  src="MapReduce Multi Threaded programming/MapReduce_explain1.png"
  title="MapReduce_explain"
  style="display: inline-block; margin: 0 auto;" width="350" height="145"><br/>
Splitting the input values between the threads will be done using an atomic variable.<br/>
Barrier (Semaphore) is used to make sure no thread are running before the Sort Phase.<br/>
Atomic counter is used to control handeling the shuffled data.<br/>
Mutex is used to take care of shared data.<br/>
The Project is using pthread library to control the threads and use mutexes.


## Virtual Memory, Hierarchial Page Tables
Virtual memory is a memory-management model that allows processes to use more memory
than is actually available on the host.<br/>
We implementeed a virtual memory interface using hierarchical page tables of arbitrary depth using simulated physical memory.<br/>
The mapping between pages and frames is done using page tables.<br/>
Hierarchical page tables use a tree of smaller tables to save memory. This effectively separates
the translation into multiple steps.<br/>

Example Of Hierarchical Page Tables Tree:<br/>
<img
  src="Virtual Memory, Hierarchial Page Tables/Example Of Hierarchical page tables Tree.png"
  title="Example Of Hierarchical Page Tables Tree:"
  style="display: inline-block; margin: 0 auto;" width="350" height="145"><br/>
This Project is using vector as RAM, the Availabe Phsical Memory and unordered_map as the hard disk, the Virtual Memory.


## Hits Counter:
How many times people visit this repository:

[![HitCount](https://hits.dwyl.com/itamar-sh/Operating-Systems-Course.svg?style=flat-square)](http://hits.dwyl.com/itamar-sh/Operating-Systems-Course)

How many unique users visit this repository:

[![HitCount](https://hits.dwyl.com/itamar-sh/Operating-Systems-Course.svg?style=flat-square&show=unique)](http://hits.dwyl.com/itamar-sh/Operating-Systems-Course)