# 42_philosophers

So, threads themselves cannot span multiple processes, but processes can have their own threads

Processes: A process is an independent program in execution. Each process has its own memory space, resources, and execution context. Processes do not share memory directly with each other, which provides isolation but can make communication between processes more complex.

Threads: Threads are the smallest unit of execution within a process. Multiple threads within the same process share the same memory space and resources. This allows them to communicate more easily with each other compared to processes but also requires careful management to avoid issues like race conditions.

https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=2
  
