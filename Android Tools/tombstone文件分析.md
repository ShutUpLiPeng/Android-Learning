https://source.android.com/devices/tech/debug

# tombstone文件
tombstone 是一个包含与崩溃进程相关的额外数据的文件。需要特别指出的是，它包含对以下内容进行的堆栈跟踪：
崩溃进程中的所有线程（而不只是捕捉到信号的线程）、完整的内存映射，以及所有打开的文件描述符的列表。

```
$ cat /data/tombstones/tombstone_0*
*** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
Build fingerprint: 'Android/aosp_angler/angler:7.1.1/NYC/enh12211018:eng/test-keys'
Revision: '0'
ABI: 'arm'
pid: 17946, tid: 17949, name: crasher  >>> crasher <<<
signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0xc
    r0 0000000c  r1 00000000  r2 00000000  r3 00000000
    r4 00000000  r5 0000000c  r6 eccdd920  r7 00000078
    r8 0000461a  r9 ffc78c19  sl ab209441  fp fffff924
    ip ed01b834  sp eccdd800  lr ecfa9a1f  pc ecfd693e  cpsr 600e0030

backtrace:
    #00 pc 0004793e  /system/lib/libc.so (pthread_mutex_lock+1)
    #01 pc 0001aa1b  /system/lib/libc.so (readdir+10)
    #02 pc 00001b91  /system/xbin/crasher (readdir_null+20)
    #03 pc 0000184b  /system/xbin/crasher (do_action+978)
    #04 pc 00001459  /system/xbin/crasher (thread_callback+24)
    #05 pc 00047317  /system/lib/libc.so (_ZL15__pthread_startPv+22)
    #06 pc 0001a7e5  /system/lib/libc.so (__start_thread+34)
Tombstone written to: /data/tombstones/tombstone_06
```
# addr2line工具
cd到AOSP编译出来的out目录下的symbols(如out/target/product/generic_x86_64/symbols/)
```
$ addr2line -a 0004793e -e ./system/lib/libc.so -if
0x0004793e
getanswer
bionic/libc/dns/net/getaddrinfo.c:1379
```

# stack工具
假设您有可用的未剥离二进制文件，则可以将堆栈粘贴到 development/scripts/stack 中，从而获取更详细的展开信息（包含行号信息）
stack在lunch时候已加载在环境变量中， 可直接使用
```
$ stack < FS/data/tombstones/tombstone_05
Reading native crash info from stdin
03-02 23:53:49.477 17951 17951 F DEBUG   : *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
03-02 23:53:49.477 17951 17951 F DEBUG   : Build fingerprint: 'Android/aosp_angler/angler:7.1.1/NYC/enh12211018:eng/test-keys'
03-02 23:53:49.477 17951 17951 F DEBUG   : Revision: '0'
03-02 23:53:49.477 17951 17951 F DEBUG   : ABI: 'arm'
03-02 23:53:49.478 17951 17951 F DEBUG   : pid: 17946, tid: 17949, name: crasher  >>> crasher <<<
03-02 23:53:49.478 17951 17951 F DEBUG   : signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0xc
03-02 23:53:49.478 17951 17951 F DEBUG   :     r0 0000000c  r1 00000000  r2 00000000  r3 00000000
03-02 23:53:49.478 17951 17951 F DEBUG   :     r4 00000000  r5 0000000c  r6 eccdd920  r7 00000078
03-02 23:53:49.478 17951 17951 F DEBUG   :     r8 0000461a  r9 ffc78c19  sl ab209441  fp fffff924
03-02 23:53:49.478 17951 17951 F DEBUG   :     ip ed01b834  sp eccdd800  lr ecfa9a1f  pc ecfd693e  cpsr 600e0030
03-02 23:53:49.491 17951 17951 F DEBUG   :
03-02 23:53:49.491 17951 17951 F DEBUG   : backtrace:
03-02 23:53:49.492 17951 17951 F DEBUG   :     #00 pc 0004793e  /system/lib/libc.so (pthread_mutex_lock+1)
03-02 23:53:49.492 17951 17951 F DEBUG   :     #01 pc 0001aa1b  /system/lib/libc.so (readdir+10)
03-02 23:53:49.492 17951 17951 F DEBUG   :     #02 pc 00001b91  /system/xbin/crasher (readdir_null+20)
03-02 23:53:49.492 17951 17951 F DEBUG   :     #03 pc 0000184b  /system/xbin/crasher (do_action+978)
03-02 23:53:49.492 17951 17951 F DEBUG   :     #04 pc 00001459  /system/xbin/crasher (thread_callback+24)
03-02 23:53:49.492 17951 17951 F DEBUG   :     #05 pc 00047317  /system/lib/libc.so (_ZL15__pthread_startPv+22)
03-02 23:53:49.492 17951 17951 F DEBUG   :     #06 pc 0001a7e5  /system/lib/libc.so (__start_thread+34)
03-02 23:53:49.492 17951 17951 F DEBUG   :     Tombstone written to: /data/tombstones/tombstone_06
Reading symbols from /huge-ssd/aosp-arm64/out/target/product/angler/symbols
Revision: '0'
pid: 17946, tid: 17949, name: crasher  >>> crasher <<<
signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0xc
     r0 0000000c  r1 00000000  r2 00000000  r3 00000000
     r4 00000000  r5 0000000c  r6 eccdd920  r7 00000078
     r8 0000461a  r9 ffc78c19  sl ab209441  fp fffff924
     ip ed01b834  sp eccdd800  lr ecfa9a1f  pc ecfd693e  cpsr 600e0030
Using arm toolchain from: /huge-ssd/aosp-arm64/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.9/bin/

Stack Trace:
  RELADDR   FUNCTION                   FILE:LINE
  0004793e  pthread_mutex_lock+2       bionic/libc/bionic/pthread_mutex.cpp:515
  v------>  ScopedPthreadMutexLocker   bionic/libc/private/ScopedPthreadMutexLocker.h:27
  0001aa1b  readdir+10                 bionic/libc/bionic/dirent.cpp:120
  00001b91  readdir_null+20            system/core/debuggerd/crasher.cpp:131
  0000184b  do_action+978              system/core/debuggerd/crasher.cpp:228
  00001459  thread_callback+24         system/core/debuggerd/crasher.cpp:90
  00047317  __pthread_start(void*)+22  bionic/libc/bionic/pthread_create.cpp:202 (discriminator 1)
  0001a7e5  __start_thread+34          bionic/libc/bionic/clone.cpp:46 (discriminator 1)

```

