#ifndef HIDL_GENERATED_ANDROID_HARDWARE_DUMPSTATE_V1_0_BPHWDUMPSTATEDEVICE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_DUMPSTATE_V1_0_BPHWDUMPSTATEDEVICE_H

#include <hidl/HidlTransportSupport.h>

#include <android/hardware/dumpstate/1.0/IHwDumpstateDevice.h>

namespace android {
namespace hardware {
namespace dumpstate {
namespace V1_0 {

struct BpHwDumpstateDevice : public ::android::hardware::BpInterface<IDumpstateDevice>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwDumpstateDevice(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    typedef IDumpstateDevice Pure;

    typedef android::hardware::details::bphw_tag _hidl_tag;

    virtual bool isRemote() const override { return true; }

    // Methods from ::android::hardware::dumpstate::V1_0::IDumpstateDevice follow.
    static ::android::hardware::Return<void>  _hidl_dumpstateBoard(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, const ::android::hardware::hidl_handle& h);

    // Methods from ::android::hardware::dumpstate::V1_0::IDumpstateDevice follow.
    ::android::hardware::Return<void> dumpstateBoard(const ::android::hardware::hidl_handle& h) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;
    ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;
    ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> setHALInstrumentation() override;
    ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;
    ::android::hardware::Return<void> ping() override;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;
    ::android::hardware::Return<void> notifySyspropsChanged() override;
    ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;

private:
    std::mutex _hidl_mMutex;
    std::vector<::android::sp<::android::hardware::hidl_binder_death_recipient>> _hidl_mDeathRecipients;
};

}  // namespace V1_0
}  // namespace dumpstate
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_DUMPSTATE_V1_0_BPHWDUMPSTATEDEVICE_H
