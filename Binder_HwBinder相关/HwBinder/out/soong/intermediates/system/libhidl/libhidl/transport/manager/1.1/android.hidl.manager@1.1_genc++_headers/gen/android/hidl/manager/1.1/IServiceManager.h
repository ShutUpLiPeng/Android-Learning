#ifndef HIDL_GENERATED_ANDROID_HIDL_MANAGER_V1_1_ISERVICEMANAGER_H
#define HIDL_GENERATED_ANDROID_HIDL_MANAGER_V1_1_ISERVICEMANAGER_H

#include <android/hidl/manager/1.0/IServiceManager.h>
#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hidl {
namespace manager {
namespace V1_1 {

struct IServiceManager : public ::android::hidl::manager::V1_0::IServiceManager {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    virtual bool isRemote() const override { return false; }


    /**
     * Retrieve an existing service that supports the requested version.
     * 
     * WARNING: This function is for libhidl/HwBinder use only. You are likely
     * looking for 'IMyInterface::getService("name")' instead.
     * 
     * @param iface    Fully-qualified interface name.
     * @param name     Instance name. Same as in IServiceManager::add.
     * 
     * @return service Handle to requested service, same as provided in
     *                 IServiceManager::add. Will be nullptr if not available.
     */
    virtual ::android::hardware::Return<::android::sp<::android::hidl::base::V1_0::IBase>> get(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name) = 0;

    /**
     * Register a service. The service manager must retrieve the (inherited)
     * interfaces that this service implements, and register them along with
     * the service.
     * 
     * Each interface must have its own namespace for instance names. If you
     * have two unrelated interfaces IFoo and IBar, it must be valid to call:
     * 
     * add("my_instance", foo); // foo implements IFoo
     * add("my_instance", bar); // bar implements IBar
     * 
     * WARNING: This function is for libhidl/HwBinder use only. You are likely
     * looking for 'INTERFACE::registerAsService("name")' instead.
     * 
     * @param name           Instance name. Must also be used to retrieve service.
     * @param service        Handle to registering service.
     * 
     * @return success       Whether or not the service was registered.
     * 
     */
    virtual ::android::hardware::Return<bool> add(const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::base::V1_0::IBase>& service) = 0;

    /**
     * Get the transport of a service.
     * 
     * @param fqName     Fully-qualified interface name.
     * @param name       Instance name. Same as in IServiceManager::add
     * 
     * @return transport Transport of service if known.
     */
    virtual ::android::hardware::Return<::android::hidl::manager::V1_0::IServiceManager::Transport> getTransport(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name) = 0;

    using list_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& fqInstanceNames)>;
    /**
     * List all registered services. Must be sorted.
     * 
     * @return fqInstanceNames List of fully-qualified instance names.
     */
    virtual ::android::hardware::Return<void> list(list_cb _hidl_cb) = 0;

    using listByInterface_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& instanceNames)>;
    /**
     * List all instances of a particular service. Must be sorted.
     * 
     * @param fqName         Fully-qualified interface name.
     * 
     * @return instanceNames List of instance names running the particular service.
     */
    virtual ::android::hardware::Return<void> listByInterface(const ::android::hardware::hidl_string& fqName, listByInterface_cb _hidl_cb) = 0;

    /**
     * Register for service notifications for a particular service. Must support
     * multiple registrations.
     * 
     * onRegistration must be sent out for all services which support the
     * version provided in the fqName. For instance, if a client registers for
     * notifications from "android.hardware.foo@1.0", they must also get
     * notifications from "android.hardware.foo@1.1". If a matching service
     * is already registered, onRegistration must be sent out with preexisting
     * = true.
     * 
     * @param fqName   Fully-qualified interface name.
     * @param name     Instance name. If name is empty, notifications must be
     *                 sent out for all names.
     * @param callback Client callback to recieve notifications.
     * 
     * @return success Whether or not registration was successful.
     */
    virtual ::android::hardware::Return<bool> registerForNotifications(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& callback) = 0;

    using debugDump_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hidl::manager::V1_0::IServiceManager::InstanceDebugInfo>& info)>;
    /**
     * Similar to list, but contains more information for each instance.
     * @return info a vector where each item contains debug information for each
     *         instance.
     */
    virtual ::android::hardware::Return<void> debugDump(debugDump_cb _hidl_cb) = 0;

    /**
     * When the passthrough service manager returns a service via
     * get(string, string), it must dispatch a registerPassthroughClient call
     * to the binderized service manager to indicate the current process has
     * called get(). Binderized service manager must record this PID, which can
     * be retrieved via debugDump.
     */
    virtual ::android::hardware::Return<void> registerPassthroughClient(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name) = 0;

    /**
     * Unregister for service notifications for a specific callback.
     * 
     * @param fqName   Fully-qualified interface name. If empty, unregister for
     *                 all notifications the callback receives.
     * @param name     Instance name. If name is empty, unregister for all instance
     *                 names.
     * @param callback Client callback that was previously registered.
     * 
     * @return success Whether or not deregistration was successful.
     */
    virtual ::android::hardware::Return<bool> unregisterForNotifications(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& callback) = 0;

    using interfaceChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& descriptors)>;
    virtual ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;

    using interfaceDescriptor_cb = std::function<void(const ::android::hardware::hidl_string& descriptor)>;
    virtual ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;

    using getHashChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_array<uint8_t, 32>>& hashchain)>;
    virtual ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> setHALInstrumentation() override;

    virtual ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;

    virtual ::android::hardware::Return<void> ping() override;

    using getDebugInfo_cb = std::function<void(const ::android::hidl::base::V1_0::DebugInfo& info)>;
    virtual ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> notifySyspropsChanged() override;

    virtual ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;
    // cast static functions
    static ::android::hardware::Return<::android::sp<::android::hidl::manager::V1_1::IServiceManager>> castFrom(const ::android::sp<::android::hidl::manager::V1_1::IServiceManager>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hidl::manager::V1_1::IServiceManager>> castFrom(const ::android::sp<::android::hidl::manager::V1_0::IServiceManager>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hidl::manager::V1_1::IServiceManager>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IServiceManager> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IServiceManager> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IServiceManager> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IServiceManager> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IServiceManager> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IServiceManager> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IServiceManager> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IServiceManager> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hidl::manager::V1_1::IServiceManager>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hidl::manager::V1_1::IServiceManager::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_1
}  // namespace manager
}  // namespace hidl
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HIDL_MANAGER_V1_1_ISERVICEMANAGER_H
