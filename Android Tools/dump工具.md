Android O之后因为Full Treble计划，在原有的binder基础上， 新增了hwbinder以及vndbinder， 以实现binder域隔离。
Android Binder和HwBinder都可供了相应的工具来dump进程的信息
+ Binder服务 -->> **dumpsys**
+ HwBinder服务 -->> **lshal**
# dumpsys工具 -- dump Binder服务
## 在Bn端实现代码里面继承并实现dump()接口
virtual     status_t    dump(int fd, const Vector<String16>& args);
```
class AudioFlinger :
    public BinderService<AudioFlinger>,
    public BnAudioFlinger
{
public:
    ...
    virtual     status_t    dump(int fd, const Vector<String16>& args);
    ...
}

status_t AudioFlinger::dump(int fd, const Vector<String16>& args)
{
    String8 result(kHardwareLockedString);
    write(fd, result.string(), result.size());
}
```
## service工具 ##
```
generic_x86_64:/ $ service list | grep audio                                                                                                                                                                
55	audio: [android.media.IAudioService]
124	media.audio_policy: [android.media.IAudioPolicyService]
125	media.audio_flinger: [android.media.IAudioFlinger]
```
## dumpsys xxx ##
```
generic_x86_64:/ $ dumpsys media.audio_flinger
Libraries NOT loaded:
Libraries loaded:
 Library loudness_enhancer
  path: /vendor/lib/soundfx/libldnhncr.so
  Loudness Enhancer / The Android Open Source Project
    UUID: fa415329-2034-4bea-b5dc-5b381c8d1e2c
    TYPE: fe3199be-aed0-413f-87bb-11260eb63cf1
    apiVersion: 00020000
    flags: 00000008
 Library downmix
  path: /vendor/lib/soundfx/libdownmix.so
  Multichannel Downmix To Stereo / The Android Open Source Project
    UUID: 93f04452-e4fe-41cc-91f9-e475b6d1d69f
    TYPE: 381e49cc-a858-4aa2-87f6-e8388e7601b2
    apiVersion: 00020000
    flags: 00000008
 Library visualizer
...
```
# lshal工具-- dump HAL服务
由于新增了hwbinder, 原理的dumpsys工具无法适应在hwservice上 
registerAsService(...)添加的HAL Service都可以用lshal来dump
## 在Ixxx代码实现端，继承实现debug(...)接口
virtual Return<void> debug(const hidl_handle& fd, const hidl_vec<hidl_string>& options) override;
```
using ::android::hardware::hidl_handle;
using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_string;
class MediaCasService : public IMediaCasService {
public:
    ...
    virtual Return<void> debug(const hidl_handle& fd, const hidl_vec<hidl_string>& options) override;
    ...
}

#include <utils/String8.h>
Return<void> MediaCasService::debug(const hidl_handle& fd, const hidl_vec<hidl_string>& options) {
    ALOGE("android.hardware.cas@1.0-MediaCasService debug");
    (void)options;
    const native_handle_t *handle = fd.getNativeHandle();
    if (handle->numFds < 1) {
      return Void();
    }
    int fileHandle = handle->data[0];

    android::String8 content;

    content.append("MediaCasService \n");
    content.appendFormat("debug: test 1 = %d \n", xxx);
    content.appendFormat("debug: test 2 = %d \n", yyy);

    content.append("\n");
    ssize_t written = write(fileHandle, content.string(), content.size());

    if (written != (ssize_t)content.size()) {
        ALOGE("SERVER(MediaCasService) debug errno = %d", errno);
    }
    return Void();
}
```
## lshal工具
- **lshal list**
    + 列出所有的Hal 服务名称
    ```
    generic_x86_64:/ # lshal list
    All binderized services (registered services through hwservicemanager)
    Interface                                                                       	Thread Use	Server	Clients
    android.frameworks.displayservice@1.0::IDisplayService/default                  	0/1     	1426 	1336
    android.frameworks.schedulerservice@1.0::ISchedulingPolicyService/default       	0/4     	1640 	1336
    android.frameworks.sensorservice@1.0::ISensorManager/default                    	0/4     	1640 	1336
    android.hardware.audio.effect@2.0::IEffectsFactory/default                      	0/3     	1389 	1551 1336
    android.hardware.audio@2.0::IDevicesFactory/default                             	0/3     	1389 	1551 1336
    android.hardware.automotive.vehicle@2.0::IVehicle/default                       	0/2     	1407 	6472 1414 1336
    android.hardware.biometrics.fingerprint@2.1::IBiometricsFingerprint/default     	0/1     	1732 	1336
    android.hardware.camera.provider@2.4::ICameraProvider/legacy/0                  	0/3     	1390 	1552 1336
    android.hardware.cas@1.0::IMediaCasService/default                            	0/2     	1391 	1336
    ...
    generic_x86_64:/ # lshal list | grep MediaCasServic
    android.hardware.cas@1.0::IMediaCasService/default                            	0/2     	1391 	1336
    ```
- **lshal debug xxx**
    + 其中xxx 是servicename + instance, 
    + ep: lshal debug android.hardware.cas@1.0::IMediaCasService/default
    ```
    generic_x86_64:/ # lshal debug android.hardware.cas@1.0::IMediaCasService/default                                                                                                                           
    MediaCasService 
    debug: test 1 = xxx 
    debug: test 2 = yyy
    ```

