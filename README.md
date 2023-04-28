# Philosophers

* **WHAT IS A THREAD**:

	In computer science, a thread is a basic unit of execution within a process. It is a lightweight sequence of instructions that can be scheduled to run independently of other threads, allowing for concurrent or parallel execution.

	Each thread has its own program counter, stack, and set of registers, but shares the same memory space as the process and other threads. Threads can communicate and synchronize with each other through shared memory or message passing mechanisms.

	Multithreading is a common technique used in modern software development to increase performance and responsiveness of applications, especially those that involve I/O operations or long-running tasks that can be split into smaller pieces.


* **WHAT IS THE DIFFRENCE BETWEEN THREAD AND PROCESS**:

	In computer science, both threads and processes are units of execution, but they differ in several ways. Here are some of the key differences:

		* Memory: Each process has its own address space, while threads share the same address space. This means that each process has its own copy of the program code and data, while threads share the same code and data.

		* Resources: Each process has its own set of system resources, such as file handles, network sockets, and devices, while threads share the same set of resources as the process.

		* Scheduling: Processes are scheduled independently by the operating system, while threads are scheduled within the context of a process. This means that threads can be scheduled more quickly and efficiently than processes.

		* Creation and Destruction: Processes are created and destroyed using system calls, while threads are created and destroyed within a process using threading libraries or APIs.

		* Communication: Processes can communicate with each other using interprocess communication (IPC) mechanisms such as pipes, sockets, and shared memory. Threads communicate with each other through shared memory or message passing mechanisms.

	In summary, threads are lighter weight than processes and are used to achieve parallelism within a process, while processes are used to achieve concurrency between independent tasks.


* **WHAAT IS RACE CONDITION**:

		A race condition is a situation that can occur in computer software when two or more threads or processes access a shared resource, such as a memory location or a file, in an unexpected or unintended order.

|            Process							|				Thread					|
|--------------------------------------------|---------------------------------------|
| Process means any program is in execution. | Thread means a segment of a process.	|
| The process takes more time to terminate. | The thread takes less time to terminate.	|
| It takes more time for creation. | It takes less time for creation.	|
| 	It also takes more time for context switching. | It takes less time for context switching.	|
| 	The process is less efficient in terms of communication. | Thread is more efficient in terms of communication.	|
| Multiprogramming holds the concepts of multi-process. | We don’t need multi programs in action for multiple threads because a single process consists of multiple threads.	|
| The process is isolated. | Threads share memory.	|
| The process is called the heavyweight process. | A Thread is lightweight as each thread in a process shares code, data, and resources.	|
