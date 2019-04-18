# HAL服务

Android 8由于退出了Android Treble计划， 规定了vendor进程只能使用HwBinder，不能访问之前的/dev/binder设备节点

因此发布和获取服务的时候， Framework层通过HIDL接口， 走/dev/hwbinder设备节点， 与底层Hal进程进行IPC通信

## Binder和HwBinder的区别

| Binder                                                       | HwBinder                                                     |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| Binder服务端需要继承Bn端                                     | Hal服务端结合继承的是Ixx端                                   |
| Bn端是继承的BnInterface<INTERFACE>                           | Ixxx端继承的是::android::hidl::base::V1_0::IBase             |
| 发布服务addservice(NAME)                                     | 发布服务的registerAsService，把descriptor和ServiceName注册到HwServiceManager |
| ServiceManager进程                                           | HwServiceManager进程                                         |
| dump工具：实现dump()函数用 dumpsys SERVICENAME可以dump进程信息 | dump工具：需要实现debug函数用 lshal list/ lshal debug descriptor+ServiceName来dump hal进程的信息 |
| NAME: 服务名称是发布时字符串                                 | NAME: descriptor + ServiceName，descriptor在自动生成头文件定义，ServiceName默认是default |
| 获取服务： getService/interface_cast                         | 获取服务： getService(会阻塞)/tryGetService(不阻塞)          |
| 配置： SEAndroid                                             | 配置： 除了SEAndroid之外，还需要专门配置个manifest.xml       |
| ServiceManager里面存放的是IBinder指针                        | HwServiceManager里面存放的是IBase对象指针                    |

## HIDL基础知识

详情请参考： 

首先我们需要知道的是：

- HIDL的代码可以根据工具来自动生成，我们一般只需要写一个Ixxx.hal的接口文件以及一个types.hal的文件

- 运行update-makefiles.sh脚本，调用hidl-gen工具来自动生成Android.mk和Android.bp, 该自动生成makedile的工具是hidl-gen (system/tools/hidl)。Android8会生成两个makefile, Android.mk和Android.bp, 其中Android.mk是生成Java相关的库文件的， Android.bp是生成C++库文件的。但是Android9生成规则改变了， 只会生成一个Android.bp，会不会生成Java的库是由Android.bp的gen_java变量来控制。

- 通过上面生成的Makefile， 我们可以make相应的module库文件，最终会生成到out/soong/.intermediates/目录下

- 为了理解HIDL的原理， 我们必须知道清楚生成的库文件代码

  ``` shell
  # out/soong/.intermediates/hardware/interfaces/dumpstate目录下的生成Example
  zmy@zmy-HP:dumpstate$ tree
  .
  └── 1.0
      ├── android.hardware.dumpstate@1.0_genc++
      │   └── gen
      │       └── android
      │           └── hardware
      │               └── dumpstate
      │                   └── 1.0
      │                       ├── DumpstateDeviceAll.cpp          # 非常重要, Ixxx,Bnxxx,Bpxxx的实现
      └── android.hardware.dumpstate@1.0_genc++_headers
          └── gen
              └── android
                  └── hardware
                      └── dumpstate
                          └── 1.0
                              ├── BnHwDumpstateDevice.h          # 生成的Bnxxx
                              ├── BpHwDumpstateDevice.h          # 生成的Bpxxx
                              ├── BsDumpstateDevice.h            # 暂时没研究过
                              ├── IDumpstateDevice.h             # 需要继承的Ixxx
                              └── IHwDumpstateDevice.h
  ```

本文是在你对HIDL C++/Java有初步的认知之后， 较为深入地探讨：

- 分析为什么继承的是Ixxx，而不是Bnxxx
- Ixxx.getService()是怎么转换成Bpxxx的
- 如果没有继承Bnxxx对象， 那么Bn和Bp是怎么实现跨进程通信的

### Ixxx

在Binder的服务端， 我们是继承的Bnxxx, Binder的客户端拿到Bp对象之后， 通过remote()->transact()调用到Bn侧

但是在Hal服务端，我们需要继承的是Ixxx, 那么就有个问题了， 当客户端拿到Hal的Bp端的时候，是怎么调用到我们的服务端的

之后会讨论， 这里只给样例代码：

```C++
...

struct IDumpstateDevice : public ::android::hidl::base::V1_0::IBase {

    // 这个是根据*.hal文件自动生成的接口， 声明了几个接口就会生成几个
    virtual ::android::hardware::Return<void> dumpstateBoard(const ::android::hardware::hidl_handle& h) = 0;
    
	virtual ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;
    
    virtual ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;
    
    virtual ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;
    
    static const char* descriptor;            // 重要，服务名称的组成部分
    
    static ::android::hardware::Return<::android::sp<::android::hardware::dumpstate::V1_0::IDumpstateDevice>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);
    
    static ::android::sp<IDumpstateDevice> getService(const std::string &serviceName="default", bool getStub=false);
    
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
};
...
```

生成文件中包含根据hal接口文件生成接口以及所有的共同的接口(如getservice， 都是Ibase的接口)

其中：

(1) debug函数:  服务端继承实现这个方法， 可以通过lshal工具来dump服务信息

(2) linkToDeath/unlinkToDeath: 死亡监听

(3) castFrom: 这个函数比较重要，在该函数里面会创建Bp对象, 将IBase对象转换成Bp对象

(4) getService/trygetService: 获取服务

(5) registerAsService： 发布服务

(5) descriptor： 组成服务名称的一部分

### Bnxxx

Bnxxx样例代码:

```C++
...
struct BnHwDumpstateDevice : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwDumpstateDevice(const ::android::sp<IDumpstateDevice> &_hidl_impl);
    
    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;
    
    ::android::sp<IDumpstateDevice> getImpl() { return _hidl_mImpl; }
    
    // Methods from ::android::hardware::dumpstate::V1_0::IDumpstateDevice follow.
    static ::android::status_t _hidl_dumpstateBoard(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);
    
private:
    ...
        
    ::android::sp<IDumpstateDevice> _hidl_mImpl;    //非常重要， 稍后会提及到
}

```

其中：

(1) onTransact函数:  类似Binder的Bn中的onTransact函数

(2) getImpl()：返回_hidl_mImpl对象

(3) _hidl_mImpl对象， 存放服务端的实现

(4) 构造函数注意一下

### Bpxxx

Bpxxx样例代码:

```C++
struct BpHwDumpstateDevice : public ::android::hardware::BpInterface<IDumpstateDevice>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwDumpstateDevice(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    // Methods from ::android::hardware::dumpstate::V1_0::IDumpstateDevice follow.
    static ::android::hardware::Return<void>  _hidl_dumpstateBoard(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::hidl_handle& h);

    // Methods from ::android::hardware::dumpstate::V1_0::IDumpstateDevice follow.
    ::android::hardware::Return<void> dumpstateBoard(const ::android::hardware::hidl_handle& h) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const 
    ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;
    ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;

private:
    std::mutex _hidl_mMutex;
    std::vector<::android::sp<::android::hardware::hidl_binder_death_recipient>> _hidl_mDeathRecipients;
};
```

其中：

(1) 构造函数需要也别注意一下，这个Bpxxx和Binder的Bp对象类似，其内部有一个mRemote对象， 这个对象是构造函数是赋值的

(2) 其它的接口和Ixxx类似

### xxxAll.cpp

样例代码：

```C++
const char* IDumpstateDevice::descriptor("android.hardware.dumpstate@1.0::IDumpstateDevice");

__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IDumpstateDevice::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwDumpstateDevice(static_cast<IDumpstateDevice *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IDumpstateDevice::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsDumpstateDevice(static_cast<IDumpstateDevice *>(iIntf));
            });
};

__attribute__((destructor))static void static_destructor() {
    ::android::hardware::details::getBnConstructorMap().erase(IDumpstateDevice::descriptor);
    ::android::hardware::details::getBsConstructorMap().erase(IDumpstateDevice::descriptor);
};

::android::hardware::Return<::android::sp<::android::hardware::dumpstate::V1_0::IDumpstateDevice>> IDumpstateDevice::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IDumpstateDevice, ::android::hidl::base::V1_0::IBase, BpHwDumpstateDevice>(
            parent, "android.hardware.dumpstate@1.0::IDumpstateDevice", emitError);
}

BpHwDumpstateDevice::BpHwDumpstateDevice(const ::android::sp<::android::hardware::IBinder> &_hidl_impl)
        : BpInterface<IDumpstateDevice>(_hidl_impl),
          ::android::hardware::details::HidlInstrumentor("android.hardware.dumpstate@1.0", "IDumpstateDevice") {
}

BnHwDumpstateDevice::BnHwDumpstateDevice(const ::android::sp<IDumpstateDevice> &_hidl_impl)
        : ::android::hidl::base::V1_0::BnHwBase(_hidl_impl, "android.hardware.dumpstate@1.0", "IDumpstateDevice") { 
            _hidl_mImpl = _hidl_impl;
            auto prio = ::android::hardware::details::gServicePrioMap.get(_hidl_impl, {SCHED_NORMAL, 0});
            mSchedPolicy = prio.sched_policy;
            mSchedPriority = prio.prio;
}

// static
::android::sp<IDumpstateDevice> IDumpstateDevice::getService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwDumpstateDevice>(serviceName, true, getStub);
}

::android::status_t IDumpstateDevice::registerAsService(const std::string &serviceName) {
    ::android::hardware::details::onRegistration("android.hardware.dumpstate@1.0", "IDumpstateDevice", serviceName);

    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return ::android::INVALID_OPERATION;
    }
    ::android::hardware::Return<bool> ret = sm->add(serviceName.c_str(), this);
    return ret.isOk() && ret ? ::android::OK : ::android::UNKNOWN_ERROR;
}
...
```

其中

(1) static_constructor/static_destructor 两个__attribute__((constructor))和__attribute__((destructor))的两个函数， 可以实现在main函数之前和结束之后运行这段代码

(2) getService()/registerAsService()

(3) Bn和Bp的构造函数

## 类图

### Binder的类图

![Class Binder](D:\GitHub\Android-Learning\Binder_HwBinder相关\Class Binder.png)

### HWBinder的类图

![Class HwBinder](D:\GitHub\Android-Learning\Binder_HwBinder相关\Class HwBinder.png)

需要注意的是, Binder和HwBinder有些区别

| Binder                     | HwBinder                          |
| -------------------------- | --------------------------------- |
| 有BnInterface, BpInterface | 没有BnInterface， 只有BpInterface |
| BpRefbase里面的mRemote     | BpHwRefbase里面的mRemote          |
| 继承Bnxxx                  | 继承Ixxx                          |

## main 之前执行的代码块

static_constructor/static_destructor 两个__attribute__((constructor))和__attribute__((destructor))的两个函数， 可以实现在main函数之前和结束之后运行这段代码， 在main之前会先调用static_constructor函数， 该函数的作用是把IDumpstateDevice::descriptor以及BnHwDumpstateDevice的构造函数lamba表达式， 存放到一个static的BnConstructorMap中。之后会分析什么时候用到了这个BnConstructorMap。

```C++
__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IDumpstateDevice::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwDumpstateDevice(static_cast<IDumpstateDevice *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IDumpstateDevice::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsDumpstateDevice(static_cast<IDumpstateDevice *>(iIntf));
            });
};
```

HIDL中用到了很多C++ 11的新特性，如lamba表达式，std::function。 如下是lamba表达式

```C++
// 函数入参是void *iIntf, 返回值是::android::sp<::android::hardware::IBinder>，内部是根据传入的iIntf来构造BnHwDumpstateDevice
[](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwDumpstateDevice(static_cast<IDumpstateDevice *>(iIntf));
            }
```

getBnConstructorMap: system/libhidl/transport/static.cpp

```C++
// Static.h
using BnConstructorMap = ConcurrentMap<std::string, std::function<sp<IBinder>(void*)>>;
// For HidlBinderSupport and autogenerated code
// value function receives reinterpret_cast<void *>(static_cast<IFoo *>(foo)),
// returns sp<IBinder>
// deprecated; use getBnConstructorMap instead.
extern BnConstructorMap gBnConstructorMap;
BnConstructorMap& getBnConstructorMap();

// Static.cpp
// For static executables, it is not guaranteed that gBnConstructorMap are initialized before
// used in HAL definition libraries.
BnConstructorMap& getBnConstructorMap() {
    static BnConstructorMap map{};
    return map;
}
```

因此在main函数之前， 把BnConstructorMap构造函数以lamba表达式的方式存放到static的map里面， 之后会看到什么时候会调用到这个函数。

## 发布服务 registerAsService

进程启动的main函数， 实例化以及发布服务的过程

```C++
// service.cpp
int main(int /* argc */, char* /* argv */ []) {
    sp<IDumpstateDevice> dumpstate = new DumpstateDevice; //实例化IDumpstateDevice
    configureRpcThreadpool(1, true /* will join */);
    if (dumpstate->registerAsService() != OK) {       //发布服务的地方
        ALOGE("Could not register service.");
        return 1;
    }
    joinRpcThreadpool();

    ALOGE("Service exited!");
    return 1;
}
// DumpstateDevice.h
struct DumpstateDevice : public IDumpstateDevice {
    // Methods from ::android::hardware::dumpstate::V1_0::IDumpstateDevice follow.
    Return<void> dumpstateBoard(const hidl_handle& h) override;

};
```

深入到registerAsService， 分析

```C++
::android::status_t IDumpstateDevice::registerAsService(const std::string &serviceName) {
    ::android::hardware::details::onRegistration("android.hardware.dumpstate@1.0", "IDumpstateDevice", serviceName);

    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();              // 获取HwServiceManager的Bp
    if (sm == nullptr) {
        return ::android::INVALID_OPERATION;
    }
    ::android::hardware::Return<bool> ret = sm->add(serviceName.c_str(), this);  // add this指针
    return ret.isOk() && ret ? ::android::OK : ::android::UNKNOWN_ERROR;
}
```

可以看到首先获取HwServiceManager的Bp对象sm, 然后调用add把创建的DumpstateDevice对象存在HwServiceManager中，从这里可以看到**HwServiceManager进程中， 存储的是指向DumpstateDevice对象的IBase指针**。

**流程分析：**

（1）继承Ixxx, 并实例化， 调用registerAsService

（2）注册服务的时候，首先获取到HwServiceManager的Bp对象, 然后把this指针add到HwServiceManager进程里面

## 获取服务 getService

当客户端调用到服务端的时候， 在Binder里面是首先获取getService(SERVICENAME), 然后利用interface_cast转换生成Bp对象， 然后跨进程调用到服务端。

下面的代码里面我们会分析整个getService的过程：

```C++
// static
::android::sp<IDumpstateDevice> IDumpstateDevice::getService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwDumpstateDevice>(serviceName, true, getStub);    // BpHwDumpstateDevice作为模板的参数传递到getServiceInternal中
}
```

### 获取Bp对象 getServiceInternal

```C++
// system/libhidl/transport/include/hidl/HidlTransportSupport.h
template <typename BpType, typename IType = typename BpType::Pure,
          typename = std::enable_if_t<std::is_same<i_tag, typename IType::_hidl_tag>::value>,
          typename = std::enable_if_t<std::is_same<bphw_tag, typename BpType::_hidl_tag>::value>>
sp<IType> getServiceInternal(const std::string& instance, bool retry, bool getStub) {
    using ::android::hidl::base::V1_0::IBase;

    sp<IBase> base = getRawServiceInternal(IType::descriptor, instance, retry, getStub);  // 第一步

    if (base == nullptr) {
        return nullptr;
    }

    if (base->isRemote()) {
        // getRawServiceInternal guarantees we get the proper class
        return sp<IType>(new BpType(toBinder<IBase>(base)));
    }

    return IType::castFrom(base);        // 第二步
}
```

#### 获取IBase对象 getRawServiceInternal



```C++
// system/libhidl/transport/ServiceManagement.cpp
sp<::android::hidl::base::V1_0::IBase> getRawServiceInternal(const std::string& descriptor,
                                                             const std::string& instance,
                                                             bool retry, bool getStub) {
    using Transport = ::android::hidl::manager::V1_0::IServiceManager::Transport;
    using ::android::hidl::base::V1_0::IBase;
    using ::android::hidl::manager::V1_0::IServiceManager;
    sp<Waiter> waiter;

    const sp<IServiceManager1_1> sm = defaultServiceManager1_1();     // 获取HwServiceManager Bp对象
    if (sm == nullptr) {
        ALOGE("getService: defaultServiceManager() is null");
        return nullptr;
    }

    Return<Transport> transportRet = sm->getTransport(descriptor, instance);   // getTransport， 主要作用是从配置的manifest.xml 查找过滤服务， 有配置才会接着走

    if (!transportRet.isOk()) {
        ALOGE("getService: defaultServiceManager()->getTransport returns %s",
              transportRet.description().c_str());
        return nullptr;
    }
    Transport transport = transportRet;
    const bool vintfHwbinder = (transport == Transport::HWBINDER);
    const bool vintfPassthru = (transport == Transport::PASSTHROUGH);

#ifdef ENFORCE_VINTF_MANIFEST

#ifdef LIBHIDL_TARGET_DEBUGGABLE
    const char* env = std::getenv("TREBLE_TESTING_OVERRIDE");
    const bool trebleTestingOverride = env && !strcmp(env, "true");
    const bool vintfLegacy = (transport == Transport::EMPTY) && trebleTestingOverride;
#else   // ENFORCE_VINTF_MANIFEST but not LIBHIDL_TARGET_DEBUGGABLE
    const bool trebleTestingOverride = false;
    const bool vintfLegacy = false;
#endif  // LIBHIDL_TARGET_DEBUGGABLE

#else   // not ENFORCE_VINTF_MANIFEST
    const char* env = std::getenv("TREBLE_TESTING_OVERRIDE");
    const bool trebleTestingOverride = env && !strcmp(env, "true");
    const bool vintfLegacy = (transport == Transport::EMPTY);
#endif  // ENFORCE_VINTF_MANIFEST

    for (int tries = 0; !getStub && (vintfHwbinder || vintfLegacy); tries++) {
        if (waiter == nullptr && tries > 0) {
            waiter = new Waiter(descriptor, instance, sm);      // 阻塞模式
        }
        if (waiter != nullptr) {
            waiter->reset();  // don't reorder this -- see comments on reset()
        }
        Return<sp<IBase>> ret = sm->get(descriptor, instance);      // 从HwServiceManager获取IBase对象
        if (!ret.isOk()) {
            ALOGE("getService: defaultServiceManager()->get returns %s for %s/%s.",
                  ret.description().c_str(), descriptor.c_str(), instance.c_str());
            break;
        }
        sp<IBase> base = ret;
        if (base != nullptr) {
            Return<bool> canCastRet =
                details::canCastInterface(base.get(), descriptor.c_str(), true /* emitError */);

            if (canCastRet.isOk() && canCastRet) {
                if (waiter != nullptr) {
                    waiter->done();
                }
                return base; // still needs to be wrapped by Bp class.
            }

            if (!handleCastError(canCastRet, descriptor, instance)) break;
        }

        // In case of legacy or we were not asked to retry, don't.
        if (vintfLegacy || !retry) break;

        if (waiter != nullptr) {
            ALOGI("getService: Trying again for %s/%s...", descriptor.c_str(), instance.c_str());
            waiter->wait();
        }
    }

    if (waiter != nullptr) {
        waiter->done();
    }

    if (getStub || vintfPassthru || vintfLegacy) {
        const sp<IServiceManager> pm = getPassthroughServiceManager();
        if (pm != nullptr) {
            sp<IBase> base = pm->get(descriptor, instance).withDefault(nullptr);
            if (!getStub || trebleTestingOverride) {
                base = wrapPassthrough(base);
            }
            return base;
        }
    }

    return nullptr;
}

```

通过getRawServiceInternal， 我们返回的是**注册到HwServiceManager的IBase对象**

#### IBase -> Bp对象 castFrom

```C++
// static 
::android::hardware::Return<::android::sp<::android::hardware::dumpstate::V1_0::IDumpstateDevice>> IDumpstateDevice::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IDumpstateDevice, ::android::hidl::base::V1_0::IBase, BpHwDumpstateDevice>(
            parent, "android.hardware.dumpstate@1.0::IDumpstateDevice", emitError);
}
```

castInterface

```C++
template <typename IChild, typename IParent, typename BpChild>
Return<sp<IChild>> castInterface(sp<IParent> parent, const char* childIndicator, bool emitError) {
    if (parent.get() == nullptr) {
        // casts always succeed with nullptrs.
        return nullptr;
    }
    Return<bool> canCastRet = details::canCastInterface(parent.get(), childIndicator, emitError);
    if (!canCastRet.isOk()) {
        // call fails, propagate the error if emitError
        return emitError
                ? details::StatusOf<bool, sp<IChild>>(canCastRet)
                : Return<sp<IChild>>(sp<IChild>(nullptr));
    }

    if (!canCastRet) {
        return sp<IChild>(nullptr); // cast failed.
    }
    // TODO b/32001926 Needs to be fixed for socket mode.
    if (parent->isRemote()) {
        // binderized mode. Got BpChild. grab the remote and wrap it.
        return sp<IChild>(new BpChild(toBinder<IParent>(parent)));  //创建Bn, Bp， 设置Bp的remote为Bn
    }
    // Passthrough mode. Got BnChild or BsChild.
    return sp<IChild>(static_cast<IChild *>(parent.get()));
}
```

toBinder： 创建Bnxxx

```C++
template <typename IType,
          typename = std::enable_if_t<std::is_same<details::i_tag, typename IType::_hidl_tag>::value>>
sp<IBinder> toBinder(sp<IType> iface) {
    IType *ifacePtr = iface.get();
    if (ifacePtr == nullptr) {
        return nullptr;
    }
    if (ifacePtr->isRemote()) {
        return ::android::hardware::IInterface::asBinder(
            static_cast<BpInterface<IType>*>(ifacePtr));
    } else {
        std::string myDescriptor = details::getDescriptor(ifacePtr);
        if (myDescriptor.empty()) {
            // interfaceDescriptor fails
            return nullptr;
        }

        // for get + set
        std::unique_lock<std::mutex> _lock = details::gBnMap.lock();

        wp<BHwBinder> wBnObj = details::gBnMap.getLocked(ifacePtr, nullptr);
        sp<IBinder> sBnObj = wBnObj.promote();

        if (sBnObj == nullptr) {
            // 这里用到了之前提到的BnConstructorMap
            auto func = details::getBnConstructorMap().get(myDescriptor, nullptr); // getBnConstructorMap
            if (!func) {
                func = details::gBnConstructorMap.get(myDescriptor, nullptr);
                if (!func) {
                    return nullptr;
                }
            }
            
            // func是Bnxxx的构造函数，创建Bn对象并转换成IBinder， ifacePtr是获取到的IBase对象
            sBnObj = sp<IBinder>(func(static_cast<void*>(ifacePtr)));

            if (sBnObj != nullptr) {
                details::gBnMap.setLocked(ifacePtr, static_cast<BHwBinder*>(sBnObj.get()));
            }
        }

        return sBnObj;
    }
}
```









