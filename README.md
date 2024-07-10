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

## Valuable info:
Three uses of threads:
- For I/O-bound tasks where the program is waiting for external resources.
- When you need lightweight concurrent execution without heavy memory overhead.
- To keep a GUI responsive while performing background tasks.
Reasons:
light-weight, not a problem to use same memory space, and in those tasks the program spends a lot of time waiting for external resources.
- Lightweight Concurrency: Threads are lighter-weight than processes. They share the same memory space, making context switching between threads faster and more efficient compared to processes.
- Shared Memory: Since threads share the same memory space, they can easily share data without the need for inter-process communication (IPC). This can simplify the design for tasks that need to share data frequently.
- Reduced Overhead: Creating and managing threads typically incurs less overhead than processes, making them suitable for I/O-bound tasks where the program spends a lot of time waiting for external resources.
- Efficiency for Network I/O: Web scraping often involves making numerous network requests, which are I/O-bound operations. Threads can handle these requests concurrently without being limited by the GIL, making them efficient for such tasks.
- Simpler Design: Using threads for web scraping allows you to manage multiple connections within the same memory space, simplifying the design and making it easier to share data between threads.
- Responsive UI: In GUI applications, using threads for background tasks ensures that the main thread (which handles the user interface) remains responsive. This improves the user experience by preventing the UI from freezing while background tasks are running.

Three uses of processes:
- For CPU-bound tasks that require heavy computations.
- When you need true parallelism to take full advantage of multiple CPU cores.
- For running independent subprocesses that do not share state.
Reasons:
1 - True Parallelism because processes allowing multiple CPU cores to be utilized effectively.
2 - Isolation: Each process runs in its own memory space, preventing memory corruption and other issues that can arise from concurrent access in threads. This isolation makes processes more robust for tasks that require heavy computation and large memory usage.
3 - Scalability: Processes can handle large datasets by distributing the load across multiple CPU cores, making them ideal for data processing tasks. This scalability can significantly reduce the time required to process large volumes of data.
4 - Independent Execution: Since each process operates independently, failures or exceptions in one process do not affect others. This is useful for data processing tasks where different data chunks might require different handling.

## Hits Counter:
How many times people visit this repository:

[![HitCount](https://hits.dwyl.com/itamar-sh/Operating-Systems-Course.svg?style=flat-square)](http://hits.dwyl.com/itamar-sh/Operating-Systems-Course)

How many unique users visit this repository:

[![HitCount](https://hits.dwyl.com/itamar-sh/Operating-Systems-Course.svg?style=flat-square&show=unique)](http://hits.dwyl.com/itamar-sh/Operating-Systems-Course)
