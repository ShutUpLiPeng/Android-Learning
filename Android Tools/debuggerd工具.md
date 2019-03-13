debuggerd可以跟踪堆栈的信息

如果有进程在某个调用过程被阻塞， 或者死锁了， 可以用该工具来进行追踪

**debuggerd -b (pid)**

补充：**ps -eT -o PID,TID,USER,CMD,SCHED,PRI,NI,NAME**
