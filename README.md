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

## Internet Protocol (IP)
TCP is Transmission Control Protocol for socket communication between client and server. The string `SOCK_STREAM` in the code:
` socket(AF_INET, SOCK_STREAM, 0) ` decide which type of protocol it will be. The string ` SOCK_DGRAM ` is for UDP.

TCP requires establishing a connection (Two hands shake) before data is exchanged. Unlike UDP.

We implemented a client-server application that can perform remote command execution over a TCP network connection.

The server listtens for connections on a specified port, while the client connects to the server and sends a command to execute.

The server repeatedly in infinitie loop accents new client connects with get_connection, then read_data and execute the command.

The client uses his own the hostname of his machine, assuming the client and server runs on the same machine, then connects to the server and sends the command argument to the server.

## Q&A:
**Three uses of threads:**
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

**Three uses of processes:**
- For CPU-bound tasks that require heavy computations.
- When you need true parallelism to take full advantage of multiple CPU cores.
- For running independent subprocesses that do not share state.
Reasons:
1 - True Parallelism because processes allowing multiple CPU cores to be utilized effectively.
2 - Isolation: Each process runs in its own memory space, preventing memory corruption and other issues that can arise from concurrent access in threads. This isolation makes processes more robust for tasks that require heavy computation and large memory usage.
3 - Scalability: Processes can handle large datasets by distributing the load across multiple CPU cores, making them ideal for data processing tasks. This scalability can significantly reduce the time required to process large volumes of data.
4 - Independent Execution: Since each process operates independently, failures or exceptions in one process do not affect others. This is useful for data processing tasks where different data chunks might require different handling.

**What is the family of TCP and UDP is called? what is included in this familiy?**
Internet Protocol (IP) suite, or more commonly, the TCP/IP protocol suite.
But the real answer is which layer it is: The Transport Layer (4th) which manages communication and segmentation.

IP is the network layer protocol responsible for addressing and routing packets across networks.

**Where TCP is located in the layers models**
On the OSI (Open Systems Interconnection) model and the TCP/IP model, TCP and UDP are part of the Transport Layer.
OSI Model:

    Physical Layer - Deals with the physical transmission of data.
    Data Link Layer - Ensures reliable data transfer between two devices on the same network.
    Network Layer - Responsible for routing data between devices across different networks (IP).
    Transport Layer - Manages end-to-end communication, error handling, flow control, and segmentation (e.g., TCP, UDP).
    Session Layer - Manages sessions or connections between applications.
    Presentation Layer - Translates data formats, encryption, and compression.
    Application Layer - Provides network services directly to user applications.

TCP/IP Model:

    Link Layer - Combines OSI's Physical and Data Link layers.
    Internet Layer - Corresponds to OSI's Network layer, with protocols like IP.
    Transport Layer - Corresponds to OSI's Transport layer, with protocols like TCP and UDP.
    Application Layer - Combines OSI's Session, Presentation, and Application layers. HTTP, FTP, DNS.

So, TCP and UDP are Transport Layer protocols, and they are responsible for delivering data between applications on different systems across a network.

**Two ways to control threads access to shared resources - advantages and cons for each one**
One way is busy loop - one thread will wait inside a mutex in infinite while loop until the mutex lock will be freed.

The other way is using wait - the thread goes to sleep until someone wakes him. We will need to control which threas
are waiting and in what order in case of more than two threads.

If we have two threads and two cores we will consider busy loop because it's faster and doesn't takes time from one thread to awake the other. If we want to control which threads goes first or if we have only one core and we care about starvation we will need to awake the waiting threads.

**What is the Kernel**

The kernel is a low-level program that has complete control over everything in the system. It operates in a highly privileged mode called kernel mode (or supervisor mode), where it has direct access to the hardware, unlike normal applications that run in user mode with restricted access. The kernel is the first part of the OS that loads into memory during boot-up and remains in memory while the system runs.

It is a binary executable that runs in a special mode of the CPU called kernel mode (or supervisor mode), which has unrestricted access to the hardware. This is in contrast to normal applications that run in user mode with limited permissions.

The kernel is always running as long as the computer is on. It starts running when you boot your system and continues running until you shut it down. Unlike regular applications, which can start and stop, the kernel must continuously manage and monitor system operations.

The kernel always reacting to interrupts (like keyboard input or network packets) and handling system calls made by user programs.

On Linux, for example, the kernel is typically a single file (like /boot/vmlinuz) that gets loaded into memory during boot.



**Roles of the Kernel**

The kernel has several key responsibilities that ensure the system operates smoothly:
1) Process Management

Process Scheduling: The kernel manages how processes (running programs) are scheduled to use the CPU. It allocates CPU time to various processes, ensuring fair resource usage and efficient multitasking.

Process Creation and Termination: It is responsible for creating, pausing, resuming, and terminating processes.

Inter-process Communication (IPC): The kernel facilitates communication between processes, allowing them to exchange data securely.

2) Memory Management
Allocation: The kernel manages the allocation of memory (RAM) to various processes. It tracks which parts of memory are in use, which are free, and how much memory each process is allowed to use.

Virtual Memory: It uses techniques like paging and segmentation to provide each process with a virtual address space, giving the illusion that each process has access to the entire memory.

Swapping: If there isn't enough physical memory, the kernel can swap inactive parts of memory to disk (in a swap file or partition) to free up RAM.

3) File System Management
File Access: The kernel handles access to files and directories, including reading, writing, creating, and deleting files. It enforces access permissions to ensure security.

File System Support: It provides support for different file systems (like FAT, NTFS, EXT4), making it possible for applications to work with files without knowing the specifics of the file system.

4) Device Management
Device Drivers: The kernel includes or loads drivers that act as translators between the hardware devices (like printers, graphics cards, and network interfaces) and software applications. These drivers are responsible for sending and receiving data to and from devices.

Input/Output Operations: It handles communication between devices and the rest of the system, ensuring efficient data transfer.

5) Network Management
The kernel is responsible for handling communication over the network, including managing sockets, network protocols (like TCP/IP), and ensuring data packets are routed correctly.
It includes firewall capabilities to control network traffic.

6) Security and Access Control
The kernel enforces security policies, manages user permissions, and controls access to system resources. It implements access controls that define which users and processes can access or modify system resources.

It plays a critical role in isolating processes to prevent unauthorized access, enhancing the overall security of the system.





## Hits Counter:
How many times people visit this repository:

[![HitCount](https://hits.dwyl.com/itamar-sh/Operating-Systems-Course.svg?style=flat-square)](http://hits.dwyl.com/itamar-sh/Operating-Systems-Course)

How many unique users visit this repository:

[![HitCount](https://hits.dwyl.com/itamar-sh/Operating-Systems-Course.svg?style=flat-square&show=unique)](http://hits.dwyl.com/itamar-sh/Operating-Systems-Course)
