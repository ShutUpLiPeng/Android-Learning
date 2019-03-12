# 1 国内不翻墙拉AOSP手顺
https://mirrors.tuna.tsinghua.edu.cn/help/AOSP/
## 安装repo工具
```
mkdir ~/bin
PATH=~/bin:$PATH
curl https://storage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
chmod a+x ~/bin/repo
```
## 建立工作目录
```
mkdir WORKING_DIRECTORY
cd WORKING_DIRECTORY
```
## 拉取代码
```
repo init -u https://aosp.tuna.tsinghua.edu.cn/platform/manifest -b <branch>
ep: repo init -u https://aosp.tuna.tsinghua.edu.cn/platform/manifest -b android-9.0.0_r3

repo sync -c

repo start android-9.0.0_r3 --all
```
* 镜像替换：.repo/manifest.xml 把其中的 aosp 这个 remote 的 fetch 从 https://android.googlesource.com 改为 https://aosp.tuna.tsinghua.edu.cn/
```
<manifest>

   <remote  name="aosp"
-           fetch="https://android.googlesource.com"
+           fetch="https://aosp.tuna.tsinghua.edu.cn"
            review="android-review.googlesource.com" />

   <remote  name="github"
```
# 2 AOSP代码编译
https://source.android.com/setup/build/initializing
## 安装JDK
```
sudo apt-get install openjdk-8-jdk

sudo update-alternatives --config java  
sudo update-alternatives --config javac
sudo update-alternatives --config javadoc
sudo update-alternatives --config javaws
sudo update-alternatives --config jar
```
## 安装依赖的软件包
sudo apt-get install git-core gnupg flex bison gperf build-essential zip curl zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z-dev libgl1-mesa-dev libxml2-utils xsltproc unzip
## 加载环境 
```
source build/envsetup.sh
```
## 选择lunch的target 
```
lunch <target>
如果没有实机， 可以编译模拟器版本
```
## 编译
```
make update-api && make -j4
```
### Out of memory error.Try increasing heap size with java option ‘-Xmx<size>’. 
```
gedit prebuilts/sdk/tools/jack-admin 

找到JACK_SERVER_COMMAND="java -XX:MaxJavaStackTraceDepth=-1 -Djava.io.tmpdir=$TMPDIR $JACK_SERVER_VM_ARGUMENTS -cp $LAUNCHER_JAR $LAUNCHER_NAME" 

在JACK_SERVER_VM_ARGUMENTS后边添加-Xmx4096m,即JACK_SERVER_VM_ARGUMENTS -Xmx4096m. 

设置完成后并点击保存退出，然后在终端上依次输入以下两个命令：
prebuilts/sdk/tools/jack-admin stop-server;
prebuilts/sdk/tools/jack-admin start-server;
```
# 3 fastboot烧写程序并启动
```
fastboot flash system_a system.img
fastboot flash system_b system.img
```
如模拟器可以通过: emulator  -selinux permissive <-show-kernel | ...>启动

# 4 初识out 目录
最后编译会生成到统一的out目录
```
out
├── host
│   ├── common
│   ├── linux-x86
│   └── windows-x86
├── soong
│   ├── host
│   └── ndk
│   └── .intermediates                         生成的中间文件如HIDL， AIDL自动生成的文件
└── target
    ├── common                                   生成的中间库， 文档等
    │   ├── docs
    │   ├── gen
    │   ├── obj
    │   └── R
    └── product
        ├── generic_x86_64                     img文件及最后生成库
        │   ├── gen
        │   ├── obj
        │   ├── obj_x86
        │   ├── recovery
        │   ├── root
        │   ├── symbols
        │   ├── system
        │   └── vendor
        │   └── ...
```
