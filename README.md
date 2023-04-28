# Philosophers

WHAT IS A THREAD:

	In computer science, a thread is a basic unit of execution within a process. It is a lightweight sequence of instructions that can be scheduled to run independently of other threads, allowing for concurrent or parallel execution.

	Each thread has its own program counter, stack, and set of registers, but shares the same memory space as the process and other threads. Threads can communicate and synchronize with each other through shared memory or message passing mechanisms.

	Multithreading is a common technique used in modern software development to increase performance and responsiveness of applications, especially those that involve I/O operations or long-running tasks that can be split into smaller pieces.


WHAT IS THE DIFFRENCE BETWEEN THREAD AND PROCESS:

	In computer science, both threads and processes are units of execution, but they differ in several ways. Here are some of the key differences:

		* Memory: Each process has its own address space, while threads share the same address space. This means that each process has its own copy of the program code and data, while threads share the same code and data.

		* Resources: Each process has its own set of system resources, such as file handles, network sockets, and devices, while threads share the same set of resources as the process.

		* Scheduling: Processes are scheduled independently by the operating system, while threads are scheduled within the context of a process. This means that threads can be scheduled more quickly and efficiently than processes.

		* Creation and Destruction: Processes are created and destroyed using system calls, while threads are created and destroyed within a process using threading libraries or APIs.

		* Communication: Processes can communicate with each other using interprocess communication (IPC) mechanisms such as pipes, sockets, and shared memory. Threads communicate with each other through shared memory or message passing mechanisms.

	In summary, threads are lighter weight than processes and are used to achieve parallelism within a process, while processes are used to achieve concurrency between independent tasks.
	
	
	
<tbody><tr><th>1.</th><td>Process means any program is in execution.</td><td>Thread means a segment of a process.</td></tr><tr><th>2.</th><td>The process takes more time to terminate.</td><td>The thread takes less time to terminate.</td></tr><tr><th>3.</th><td>It takes more time for creation.</td><td>It takes less time for creation.</td></tr><tr><th>4.</th><td>It also takes more time for context switching.</td><td>It takes less time for context switching.</td></tr><tr><th>5.</th><td>The process is less efficient in terms of communication.</td><td>Thread is more efficient in terms of communication.</td></tr><tr><th>6.&nbsp;</th><td>Multiprogramming holds the concepts of multi-process.</td><td>We don’t need multi programs in action for multiple threads because a single process consists of multiple threads.</td></tr><tr><th>7.</th><td>The process is isolated.</td><td>Threads share memory.</td></tr><tr><th>8.</th><td>The process is called the heavyweight process.</td><td>A Thread is lightweight as each thread in a process shares code, data, and resources.</td></tr><tr><th>9.</th><td>Process switching uses an interface in an operating system.</td><td>Thread switching does not require calling an operating system and causes an interrupt to the kernel.</td></tr><tr><th>10.</th><td>If one process is blocked then it will not affect the execution of other processes&nbsp;</td><td>If a user-level thread is blocked, then all other user-level threads are blocked.&nbsp;</td></tr><tr><th>11.</th><td>The process has its own Process Control Block, Stack, and Address Space.</td><td>Thread has Parents’ PCB, its own Thread Control Block, and Stack and common Address space.</td></tr><tr><th>12.</th><td>Changes to the parent process do not affect child processes.</td><td>Since all threads of the same process share address space and other resources so any changes to the main thread may affect the behavior of the other threads of the process.</td></tr><tr><th>13.</th><td>A system call is involved in it.</td><td>No system call is involved, it is created using APIs.</td></tr><tr><th>14.</th><td>The process does not share data with each other.</td><td>Threads share data with each other.</td></tr></tbody>
