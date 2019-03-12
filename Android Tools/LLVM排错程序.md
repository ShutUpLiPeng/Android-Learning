# LLVM排错程序

该文档主要参考https://source.android.google.cn/devices/tech/debug/sanitizers

LLVM 是用于编译 Android 的编译器基础架构，包含可执行静态和动态分析的多个组件。

在这些组件中，排错程序（特别是 AddressSanitizer 和 UndefinedBehaviorSanitizer）可以广泛用于分析 Android。排错程序是包含在 external/compiler-rt 中的基于编译器的插桩组件，可用于在开发和测试期间消除错误和改进 Android。Android 目前的排错程序系列可以发现和诊断许多内存滥用错误以及可能危险的未定义行为。

Android 建议编译版本最好在启用排错程序（如 AddressSanitizer 和 UndefinedBehaviorSanitizer）的情况下启动并运行。本文主要是讨论用户空间的排错程序， 内核部分不涉及。

- AddressSanitizer：基于编译器的插桩功能，可在运行时检测 C/C++ 代码中许多类型的内存错误。可以检测如下的内存错误：
  - 出界内存访问
  - 双重释放
  - 释放后再使用
- UndefinedBehaviorSanitizer： 在执行编译时插桩，以检查各种类型的未定义行为

## 1 Clang 编译基础

第一步是要确保您的代码是使用 Clang 编译的，以下讨论的排错程序都是基于Clang编译器， 如果不确定当前的编译器是否是Clang， 请在mk或者bp文件中声明以下编译选项：

```Android.mk
LOCAL_CLANG:=true
```

```Android.bp
clang: true
```

排错程序的实现主要是基于在Android.mk或者Android.bp中添加如下的编译选项， 通过不同的配置选项来控制排错的类型

```Android.mk
LOCAL_SANITIZE
LOCAL_SANITIZE_DIAG
```

```Android.bp
sanitize: {
  ...
}
```

## 2 AddressSanitizer -- 内存排错工具

该文档主要参考https://source.android.google.cn/devices/tech/debug/asan

AddressSanitizer (ASan) 是一种基于编译器的快速检测工具，用于检测原生代码中的内存错误。

Android 允许在完整编译级别和在应用级别通过 asanwrapper 进行 ASan 插桩。

AddressSanitizer 对所有与内存相关的函数调用（包括 alloca、malloc 和 free）进行插桩，并使用被读取或写入时会触发 ASan 回调的内存填充所有变量和已分配的内存区域。

### 2.1 AddressSanitizer 编译可执行文件

将 LOCAL_SANITIZE:=address 添加到可执行文件的编译规则中。

```
LOCAL_SANITIZE:=address
```

检测到错误时，ASan 会向标准输出和 logcat 发送一份详细报告，然后让相应进程崩溃。

### 2.2 AddressSanitizer 编译共享库

根据 ASan 的工作原理，未通过 ASan 编译的可执行文件将无法使用 ASan 编译的共享库。

***注意：在运行时，如果将 ASan 库加载到错误的进程中，系统将显示以 _asan 或 _sanitizer 开头的消息，提示您有无法解析的符号***

如果对多个可执行文件（并非所有这些可执行文件都是使用 ASan 编译的）使用的共享库进行测试时， 需要建立库的副本，只是建立副本， 原有的需要保存。配置额外的Android.mk

```Andro
LOCAL_SANITIZE:=address
LOCAL_MODULE_RELATIVE_PATH := asan
```

会生成到/system/lib/asan中， 将路径放到LD_LIBRARY_PATH里面

```
LD_LIBRARY_PATH=/system/lib/asan
```

如果该库是守护进程使用到，请添加到/init.rc或者/init.$device$.rc的相应部分。

```
setenv LD_LIBRARY_PATH /system/lib/asan
```

***注意：为了满足测试，上述操作都是基于推库进行，不建议全编然后烧写机器(可能导致无法启动)***

通过读取 /proc/$PID/maps，验证相应进程使用的库是否来自 /system/lib/asan（如果此库存在）。如果不是，您可能需要停用 SELinux，如下所示：

```shell
adb root
adb shell setenforce 0
```

### 2.3 AddressSanitizer 堆栈跟踪

// TODO
