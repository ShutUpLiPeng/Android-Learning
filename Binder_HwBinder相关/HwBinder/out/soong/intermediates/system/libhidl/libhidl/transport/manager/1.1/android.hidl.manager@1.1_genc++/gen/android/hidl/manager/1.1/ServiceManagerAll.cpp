#define LOG_TAG "android.hidl.manager@1.1::ServiceManager"

#include <android/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>

#include <android/hidl/manager/1.0/IServiceManager.h>
#include <android/hidl/manager/1.1/BpHwServiceManager.h>
#include <android/hidl/manager/1.1/BnHwServiceManager.h>
#include <android/hidl/manager/1.1/BsServiceManager.h>
#include <android/hidl/manager/1.0/BpHwServiceManager.h>
#include <android/hidl/base/1.0/BpHwBase.h>
#include <hidl/ServiceManagement.h>

namespace android {
namespace hidl {
namespace manager {
namespace V1_1 {

const char* IServiceManager::descriptor("android.hidl.manager@1.1::IServiceManager");

__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IServiceManager::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwServiceManager(static_cast<IServiceManager *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IServiceManager::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsServiceManager(static_cast<IServiceManager *>(iIntf));
            });
};

__attribute__((destructor))static void static_destructor() {
    ::android::hardware::details::getBnConstructorMap().erase(IServiceManager::descriptor);
    ::android::hardware::details::getBsConstructorMap().erase(IServiceManager::descriptor);
};

// Methods from ::android::hidl::manager::V1_0::IServiceManager follow.
// no default implementation for: ::android::hardware::Return<::android::sp<::android::hidl::base::V1_0::IBase>> IServiceManager::get(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name)
// no default implementation for: ::android::hardware::Return<bool> IServiceManager::add(const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::base::V1_0::IBase>& service)
// no default implementation for: ::android::hardware::Return<::android::hidl::manager::V1_0::IServiceManager::Transport> IServiceManager::getTransport(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name)
// no default implementation for: ::android::hardware::Return<void> IServiceManager::list(list_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IServiceManager::listByInterface(const ::android::hardware::hidl_string& fqName, listByInterface_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<bool> IServiceManager::registerForNotifications(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& callback)
// no default implementation for: ::android::hardware::Return<void> IServiceManager::debugDump(debugDump_cb _hidl_cb)
// no default implementation for: ::android::hardware::Return<void> IServiceManager::registerPassthroughClient(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name)

// Methods from ::android::hidl::manager::V1_1::IServiceManager follow.
// no default implementation for: ::android::hardware::Return<bool> IServiceManager::unregisterForNotifications(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& callback)

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> IServiceManager::interfaceChain(interfaceChain_cb _hidl_cb){
    _hidl_cb({
        ::android::hidl::manager::V1_1::IServiceManager::descriptor,
        ::android::hidl::manager::V1_0::IServiceManager::descriptor,
        ::android::hidl::base::V1_0::IBase::descriptor,
    });
    return ::android::hardware::Void();}

::android::hardware::Return<void> IServiceManager::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    (void)fd;
    (void)options;
    return ::android::hardware::Void();}

::android::hardware::Return<void> IServiceManager::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    _hidl_cb(::android::hidl::manager::V1_1::IServiceManager::descriptor);
    return ::android::hardware::Void();}

::android::hardware::Return<void> IServiceManager::getHashChain(getHashChain_cb _hidl_cb){
    _hidl_cb({
        (uint8_t[32]){11,148,220,135,111,116,158,210,74,152,246,28,65,212,106,215,90,39,81,17,99,241,150,138,8,66,19,163,60,104,78,246} /* 0b94dc876f749ed24a98f61c41d46ad75a27511163f1968a084213a33c684ef6 */,
        (uint8_t[32]){77,4,106,89,142,133,241,194,211,131,195,169,9,108,60,5,120,233,116,88,7,46,231,230,127,112,78,153,213,251,13,63} /* 4d046a598e85f1c2d383c3a9096c3c0578e97458072ee7e67f704e99d5fb0d3f */,
        (uint8_t[32]){189,218,182,24,77,122,52,109,166,160,125,192,130,140,241,154,105,111,76,170,54,17,197,31,46,20,86,90,20,180,15,217} /* bddab6184d7a346da6a07dc0828cf19a696f4caa3611c51f2e14565a14b40fd9 */});
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IServiceManager::setHALInstrumentation(){
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IServiceManager::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    (void)cookie;
    return (recipient != nullptr);
}

::android::hardware::Return<void> IServiceManager::ping(){
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IServiceManager::getDebugInfo(getDebugInfo_cb _hidl_cb){
    _hidl_cb({ -1 /* pid */, 0 /* ptr */, 
    #if defined(__LP64__)
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_64BIT
    #else
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_32BIT
    #endif
    });
    return ::android::hardware::Void();}

::android::hardware::Return<void> IServiceManager::notifySyspropsChanged(){
    ::android::report_sysprop_change();
    return ::android::hardware::Void();}

::android::hardware::Return<bool> IServiceManager::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    return (recipient != nullptr);
}


// static 
::android::hardware::Return<::android::sp<::android::hidl::manager::V1_1::IServiceManager>> IServiceManager::castFrom(const ::android::sp<::android::hidl::manager::V1_1::IServiceManager>& parent, bool /* emitError */) {
    return parent;
}

// static 
::android::hardware::Return<::android::sp<::android::hidl::manager::V1_1::IServiceManager>> IServiceManager::castFrom(const ::android::sp<::android::hidl::manager::V1_0::IServiceManager>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IServiceManager, ::android::hidl::manager::V1_0::IServiceManager, BpHwServiceManager>(
            parent, "android.hidl.manager@1.1::IServiceManager", emitError);
}

// static 
::android::hardware::Return<::android::sp<::android::hidl::manager::V1_1::IServiceManager>> IServiceManager::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IServiceManager, ::android::hidl::base::V1_0::IBase, BpHwServiceManager>(
            parent, "android.hidl.manager@1.1::IServiceManager", emitError);
}

BpHwServiceManager::BpHwServiceManager(const ::android::sp<::android::hardware::IBinder> &_hidl_impl)
        : BpInterface<IServiceManager>(_hidl_impl),
          ::android::hardware::details::HidlInstrumentor("android.hidl.manager@1.1", "IServiceManager") {
}

// Methods from ::android::hidl::manager::V1_1::IServiceManager follow.
::android::hardware::Return<bool> BpHwServiceManager::_hidl_unregisterForNotifications(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& callback) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    atrace_begin(ATRACE_TAG_HAL, "HIDL::IServiceManager::unregisterForNotifications::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&fqName);
        _hidl_args.push_back((void *)&name);
        _hidl_args.push_back((void *)&callback);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "android.hidl.manager", "1.1", "IServiceManager", "unregisterForNotifications", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    bool _hidl_out_success;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwServiceManager::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl_fqName_parent;

    _hidl_err = _hidl_data.writeBuffer(&fqName, sizeof(fqName), &_hidl_fqName_parent);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::writeEmbeddedToParcel(
            fqName,
            &_hidl_data,
            _hidl_fqName_parent,
            0 /* parentOffset */);

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl_name_parent;

    _hidl_err = _hidl_data.writeBuffer(&name, sizeof(name), &_hidl_name_parent);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::writeEmbeddedToParcel(
            name,
            &_hidl_data,
            _hidl_name_parent,
            0 /* parentOffset */);

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (callback == nullptr) {
        _hidl_err = _hidl_data.writeStrongBinder(nullptr);
    } else {
        ::android::sp<::android::hardware::IBinder> _hidl_binder = ::android::hardware::toBinder<
                ::android::hidl::manager::V1_0::IServiceNotification>(callback);
        if (_hidl_binder.get() != nullptr) {
            _hidl_err = _hidl_data.writeStrongBinder(_hidl_binder);
        } else {
            _hidl_err = ::android::UNKNOWN_ERROR;
        }
    }
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    ::android::hardware::ProcessState::self()->startThreadPool();
    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(9 /* unregisterForNotifications */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    _hidl_err = _hidl_reply.readBool(&_hidl_out_success);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_success);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "android.hidl.manager", "1.1", "IServiceManager", "unregisterForNotifications", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<bool>(_hidl_out_success);

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<bool>(_hidl_status);
}


// Methods from ::android::hidl::manager::V1_0::IServiceManager follow.
::android::hardware::Return<::android::sp<::android::hidl::base::V1_0::IBase>> BpHwServiceManager::get(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name){
    ::android::hardware::Return<::android::sp<::android::hidl::base::V1_0::IBase>>  _hidl_out = ::android::hidl::manager::V1_0::BpHwServiceManager::_hidl_get(this, this, fqName, name);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwServiceManager::add(const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::base::V1_0::IBase>& service){
    ::android::hardware::Return<bool>  _hidl_out = ::android::hidl::manager::V1_0::BpHwServiceManager::_hidl_add(this, this, name, service);

    return _hidl_out;
}

::android::hardware::Return<::android::hidl::manager::V1_0::IServiceManager::Transport> BpHwServiceManager::getTransport(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name){
    ::android::hardware::Return<::android::hidl::manager::V1_0::IServiceManager::Transport>  _hidl_out = ::android::hidl::manager::V1_0::BpHwServiceManager::_hidl_getTransport(this, this, fqName, name);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::list(list_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::manager::V1_0::BpHwServiceManager::_hidl_list(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::listByInterface(const ::android::hardware::hidl_string& fqName, listByInterface_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::manager::V1_0::BpHwServiceManager::_hidl_listByInterface(this, this, fqName, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwServiceManager::registerForNotifications(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& callback){
    ::android::hardware::Return<bool>  _hidl_out = ::android::hidl::manager::V1_0::BpHwServiceManager::_hidl_registerForNotifications(this, this, fqName, name, callback);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::debugDump(debugDump_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::manager::V1_0::BpHwServiceManager::_hidl_debugDump(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::registerPassthroughClient(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::manager::V1_0::BpHwServiceManager::_hidl_registerPassthroughClient(this, this, fqName, name);

    return _hidl_out;
}


// Methods from ::android::hidl::manager::V1_1::IServiceManager follow.
::android::hardware::Return<bool> BpHwServiceManager::unregisterForNotifications(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& callback){
    ::android::hardware::Return<bool>  _hidl_out = ::android::hidl::manager::V1_1::BpHwServiceManager::_hidl_unregisterForNotifications(this, this, fqName, name, callback);

    return _hidl_out;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BpHwServiceManager::interfaceChain(interfaceChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_debug(this, this, fd, options);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::getHashChain(getHashChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getHashChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::setHALInstrumentation(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_setHALInstrumentation(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwServiceManager::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    ::android::hardware::ProcessState::self()->startThreadPool();
    ::android::hardware::hidl_binder_death_recipient *binder_recipient = new ::android::hardware::hidl_binder_death_recipient(recipient, cookie, this);
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    _hidl_mDeathRecipients.push_back(binder_recipient);
    return (remote()->linkToDeath(binder_recipient) == ::android::OK);
}

::android::hardware::Return<void> BpHwServiceManager::ping(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_ping(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getDebugInfo(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwServiceManager::notifySyspropsChanged(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_notifySyspropsChanged(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwServiceManager::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    for (auto it = _hidl_mDeathRecipients.begin();it != _hidl_mDeathRecipients.end();++it) {
        if ((*it)->getRecipient() == recipient) {
            ::android::status_t status = remote()->unlinkToDeath(*it);
            _hidl_mDeathRecipients.erase(it);
            return status == ::android::OK;
        }}
    return false;
}


BnHwServiceManager::BnHwServiceManager(const ::android::sp<IServiceManager> &_hidl_impl)
        : ::android::hidl::base::V1_0::BnHwBase(_hidl_impl, "android.hidl.manager@1.1", "IServiceManager") { 
            _hidl_mImpl = _hidl_impl;
            auto prio = ::android::hardware::details::gServicePrioMap.get(_hidl_impl, {SCHED_NORMAL, 0});
            mSchedPolicy = prio.sched_policy;
            mSchedPriority = prio.prio;
}

BnHwServiceManager::~BnHwServiceManager() {
    ::android::hardware::details::gBnMap.eraseIfEqual(_hidl_mImpl.get(), this);
}

// Methods from ::android::hidl::manager::V1_1::IServiceManager follow.
::android::status_t BnHwServiceManager::_hidl_unregisterForNotifications(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwServiceManager::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    const ::android::hardware::hidl_string* fqName;
    const ::android::hardware::hidl_string* name;
    ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> callback;

    size_t _hidl_fqName_parent;

    _hidl_err = _hidl_data.readBuffer(sizeof(*fqName), &_hidl_fqName_parent,  reinterpret_cast<const void **>(&fqName));

    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = ::android::hardware::readEmbeddedFromParcel(
            const_cast<::android::hardware::hidl_string &>(*fqName),
            _hidl_data,
            _hidl_fqName_parent,
            0 /* parentOffset */);

    if (_hidl_err != ::android::OK) { return _hidl_err; }

    size_t _hidl_name_parent;

    _hidl_err = _hidl_data.readBuffer(sizeof(*name), &_hidl_name_parent,  reinterpret_cast<const void **>(&name));

    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = ::android::hardware::readEmbeddedFromParcel(
            const_cast<::android::hardware::hidl_string &>(*name),
            _hidl_data,
            _hidl_name_parent,
            0 /* parentOffset */);

    if (_hidl_err != ::android::OK) { return _hidl_err; }

    {
        ::android::sp<::android::hardware::IBinder> _hidl_binder;
        _hidl_err = _hidl_data.readNullableStrongBinder(&_hidl_binder);
        if (_hidl_err != ::android::OK) { return _hidl_err; }

        callback = ::android::hardware::fromBinder<::android::hidl::manager::V1_0::IServiceNotification,::android::hidl::manager::V1_0::BpHwServiceNotification,::android::hidl::manager::V1_0::BnHwServiceNotification>(_hidl_binder);
    }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IServiceManager::unregisterForNotifications::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)fqName);
        _hidl_args.push_back((void *)name);
        _hidl_args.push_back((void *)&callback);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "android.hidl.manager", "1.1", "IServiceManager", "unregisterForNotifications", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    bool _hidl_out_success = static_cast<IServiceManager*>(_hidl_this->getImpl().get())->unregisterForNotifications(*fqName, *name, callback);

    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    _hidl_err = _hidl_reply->writeBool(_hidl_out_success);
    /* _hidl_err ignored! */

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&_hidl_out_success);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "android.hidl.manager", "1.1", "IServiceManager", "unregisterForNotifications", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_cb(*_hidl_reply);
    return _hidl_err;
}


// Methods from ::android::hidl::manager::V1_0::IServiceManager follow.

// Methods from ::android::hidl::manager::V1_1::IServiceManager follow.

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BnHwServiceManager::ping() {
    return ::android::hardware::Void();
}
::android::hardware::Return<void> BnHwServiceManager::getDebugInfo(getDebugInfo_cb _hidl_cb) {
    _hidl_cb({
        ::android::hardware::details::getPidIfSharable(),
        ::android::hardware::details::debuggable()? reinterpret_cast<uint64_t>(this) : 0 /* ptr */,
        #if defined(__LP64__)
        ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_64BIT
        #else
        ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_32BIT
        #endif

    });
    return ::android::hardware::Void();}

::android::status_t BnHwServiceManager::onTransact(
        uint32_t _hidl_code,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        uint32_t _hidl_flags,
        TransactCallback _hidl_cb) {
    ::android::status_t _hidl_err = ::android::OK;

    switch (_hidl_code) {
        case 1 /* get */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hidl::manager::V1_0::BnHwServiceManager::_hidl_get(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 2 /* add */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hidl::manager::V1_0::BnHwServiceManager::_hidl_add(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 3 /* getTransport */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hidl::manager::V1_0::BnHwServiceManager::_hidl_getTransport(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 4 /* list */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hidl::manager::V1_0::BnHwServiceManager::_hidl_list(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 5 /* listByInterface */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hidl::manager::V1_0::BnHwServiceManager::_hidl_listByInterface(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 6 /* registerForNotifications */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hidl::manager::V1_0::BnHwServiceManager::_hidl_registerForNotifications(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 7 /* debugDump */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hidl::manager::V1_0::BnHwServiceManager::_hidl_debugDump(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 8 /* registerPassthroughClient */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hidl::manager::V1_0::BnHwServiceManager::_hidl_registerPassthroughClient(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        case 9 /* unregisterForNotifications */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1 /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::android::hidl::manager::V1_1::BnHwServiceManager::_hidl_unregisterForNotifications(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        default:
        {
            return ::android::hidl::base::V1_0::BnHwBase::onTransact(
                    _hidl_code, _hidl_data, _hidl_reply, _hidl_flags, _hidl_cb);
        }
    }

    if (_hidl_err == ::android::UNEXPECTED_NULL) {
        _hidl_err = ::android::hardware::writeToParcel(
                ::android::hardware::Status::fromExceptionCode(::android::hardware::Status::EX_NULL_POINTER),
                _hidl_reply);
    }return _hidl_err;
}

BsServiceManager::BsServiceManager(const ::android::sp<::android::hidl::manager::V1_1::IServiceManager> impl) : ::android::hardware::details::HidlInstrumentor("android.hidl.manager@1.1", "IServiceManager"), mImpl(impl) {
    mOnewayQueue.start(3000 /* similar limit to binderized */);
}

::android::hardware::Return<void> BsServiceManager::addOnewayTask(std::function<void(void)> fun) {
    if (!mOnewayQueue.push(fun)) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_TRANSACTION_FAILED,
                "Passthrough oneway function queue exceeds maximum size.");
    }
    return ::android::hardware::Status();
}

// static
::android::sp<IServiceManager> IServiceManager::tryGetService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwServiceManager>(serviceName, false, getStub);
}

// static
::android::sp<IServiceManager> IServiceManager::getService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwServiceManager>(serviceName, true, getStub);
}

::android::status_t IServiceManager::registerAsService(const std::string &serviceName) {
    ::android::hardware::details::onRegistration("android.hidl.manager@1.1", "IServiceManager", serviceName);

    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return ::android::INVALID_OPERATION;
    }
    ::android::hardware::Return<bool> ret = sm->add(serviceName.c_str(), this);
    return ret.isOk() && ret ? ::android::OK : ::android::UNKNOWN_ERROR;
}

bool IServiceManager::registerForNotifications(
        const std::string &serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification) {
    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return false;
    }
    ::android::hardware::Return<bool> success =
            sm->registerForNotifications("android.hidl.manager@1.1::IServiceManager",
                    serviceName, notification);
    return success.isOk() && success;
}

static_assert(sizeof(::android::hardware::MQDescriptor<char, ::android::hardware::kSynchronizedReadWrite>) == 32, "wrong size");
static_assert(sizeof(::android::hardware::hidl_handle) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_memory) == 40, "wrong size");
static_assert(sizeof(::android::hardware::hidl_string) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_vec<char>) == 16, "wrong size");

}  // namespace V1_1
}  // namespace manager
}  // namespace hidl
}  // namespace android
