# Binder

Binder是Android Framework层最常见的跨进程IPC通信的最常见的一种方式。AIDL是Binder的进一步封装， 其本质也是Binder， 目前可以通过aidl-cpp工具自动化生成C++侧代码。本文只讨论显式的Binder服务

![Class Binder](.\Class Binder.png)

## 发布Binder服务

（1）首先我们需要自己实现Ixxx, Bpxxx, Bnxxx， 可以参考IAudioFlinger.h/cpp文件

```C++
// 文件路径： AOSP: frameworks/av/services/audioflinger/
// IAudioFlinger.h
#include <binder/IInterface.h>

class IAudioFlinger : public IInterface
{
public:
    DECLARE_META_INTERFACE(AudioFlinger);    // DECLARE_META_INTERFACE
    ...
}

class BnAudioFlinger : public BnInterface<IAudioFlinger>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

// IAudioFlinger.cpp
#include "IAudioFlinger.h"

class BpAudioFlinger : public BpInterface<IAudioFlinger>
{
public:
    explicit BpAudioFlinger(const sp<IBinder>& impl)         // 构造的时候impl参数， 就是mRemote
        : BpInterface<IAudioFlinger>(impl)                   // 这个MRemote其实是Bnxxx的实例的指针
    {
    }
    
    virtual status_t closeInput(int input)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioFlinger::getInterfaceDescriptor());
        data.writeInt32(input);
        remote()->transact(CLOSE_INPUT, data, &reply);      // remote()返回值是mRemote, 可以调用到Bn端
        return reply.readInt32();
    }
    ... 
}

IMPLEMENT_META_INTERFACE(AudioFlinger, "android.media.IAudioFlinger");  //IMPLEMENT_META_INTERFACE

status_t BnAudioFlinger::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
        switch (code) {
        case CREATE_TRACK: {
        	...
        }
        ...
}


```

（2）必须继承Bnxxx, 并创建出这个类，通过向servicemanager注册Binder服务

```C++
// AOSP: frameworks/av/services/audioflinger/AudioFlinger.h
class AudioFlinger :
    public BinderService<AudioFlinger>,
    public BnAudioFlinger         // 继承BnAudioFlinger
{
public:
    virtual     status_t    dump(int fd, const Vector<String16>& args);
    ...
}

// 因为代码里面同时继承了BinderService<AudioFlinger>， 这个模板中定义了许多通用的方法， public/instantiate等
// main_audioserver.cpp在进程的main函数里面会调用AudioFlinger::instantiate();这样会发布服务
// AOSP frameworks/native/libs/binder/include/binder/BinderService.h
template<typename SERVICE>
class BinderService
{
public:
    static status_t publish(bool allowIsolated = false) {
        sp<IServiceManager> sm(defaultServiceManager());
        return sm->addService(
                String16(SERVICE::getServiceName()),
                new SERVICE(), allowIsolated);        // 创建对象并发布服务
    }

    static void instantiate() { publish(); }
	...
}；
```

### 分析：

- 首先可以看到代码里是把实例化后的Bnxxx对象（继承关系推断出其实是IBinder对象）， 传递到ServiceManger, 最终保存在Service Manager里面的，其实是只是指向AudioFlinger实例化对象的IBinder指针
- 目前我们只看到了Bn端的创建， 以及向ServiceManager里面注册的过程， 接下来在使用Binder过程中，我们可以看到Bp对象的创建过程

## 查找Binder服务 

跨进程访问时， 首先我们需要获取到服务端的Bp对象。然后用Bp对象进行跨进程接口调用

查找Binder服务的方法， 代码如下：

```c++
sp<IServiceManager> sm = defaultServiceManager();

sp<IBinder> binder = sm->getService(String16("media.audio_flinger"));  // 从ServiceManager获取到IBinder对象

sp<IAudioFlinger> flinger = interface_cast<IAudioFlinger>(binder); // 该过程中会转换生成Bp对象

// interface_case 是DECLARE_META_INTERFACE和IMPLEMENT_META_INTERFACE实现的方法
// AOSP: frameworks/native/libs/binder/include/binder/IInterface.h
#define IMPLEMENT_META_INTERFACE(INTERFACE, NAME)                       \
    const ::android::String16 I##INTERFACE::descriptor(NAME);           \
    const ::android::String16&                                          \
            I##INTERFACE::getInterfaceDescriptor() const {              \
        return I##INTERFACE::descriptor;                                \
    }                                                                   \
    ::android::sp<I##INTERFACE> I##INTERFACE::asInterface(              \
            const ::android::sp<::android::IBinder>& obj)               \
    {                                                                   \
        ::android::sp<I##INTERFACE> intr;                               \
        if (obj != NULL) {                                              \
            intr = static_cast<I##INTERFACE*>(                          \
                obj->queryLocalInterface(                               \
                        I##INTERFACE::descriptor).get());               \
            if (intr == NULL) {                                         \
                intr = new Bp##INTERFACE(obj);                          \
            }                                                           \
        }                                                               \
        return intr;                                                    \
    }                                                                   \
    I##INTERFACE::I##INTERFACE() { }                                    \
    I##INTERFACE::~I##INTERFACE() { }                                   \
// intr = new Bp##INTERFACE(obj); new Bp对象，将IBinder传递到BpRefbase中
```

### 分析：

- 首先从ServiceManager里面通过服务名称去获取IBinder对象， 这个对象就是之前注册的Bn实例化的指针
- 将获取的IBinder对象， 在构造Bp对象的时候，将IBinder对象设置到BpRefbase的mRemote，Bp可以通过remote()方法获取到这个对象，然后调用该对象的transact, 利用多态的特性会调用到Bn的onTransact函数

