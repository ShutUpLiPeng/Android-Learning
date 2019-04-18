#ifndef HIDL_GENERATED_ANDROID_HARDWARE_DUMPSTATE_V1_0_IDUMPSTATEDEVICE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_DUMPSTATE_V1_0_IDUMPSTATEDEVICE_H

#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace dumpstate {
namespace V1_0 {

struct IDumpstateDevice : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    virtual bool isRemote() const override { return false; }


    /**
     * Dump device-specific state into the given file descriptors.
     * 
     * One file descriptor must be passed to this method but two may be passed:
     * the first descriptor must be used to dump device-specific state in text
     * format, the second descriptor is optional and may be used to dump
     * device-specific state in binary format.
     * 
     * @param h A native handle with one or two valid file descriptors.
     */
    virtual ::android::hardware::Return<void> dumpstateBoard(const ::android::hardware::hidl_handle& h) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::dumpstate::V1_0::IDumpstateDevice>> castFrom(const ::android::sp<::android::hardware::dumpstate::V1_0::IDumpstateDevice>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::dumpstate::V1_0::IDumpstateDevice>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IDumpstateDevice> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IDumpstateDevice> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IDumpstateDevice> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IDumpstateDevice> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IDumpstateDevice> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IDumpstateDevice> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IDumpstateDevice> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IDumpstateDevice> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::dumpstate::V1_0::IDumpstateDevice>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::dumpstate::V1_0::IDumpstateDevice::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace dumpstate
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_DUMPSTATE_V1_0_IDUMPSTATEDEVICE_H
