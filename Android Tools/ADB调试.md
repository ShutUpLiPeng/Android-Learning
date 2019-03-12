## 配置adb
lsusb

/etc/udev/rules.d/51-android.rules 添加规则

sudo service udev restart

## 常用命令
- **adb start-server** 
  + ensure that there is a server running
- **adb kill-server**
  + kill the server if it is running
- **adb root**
  + restarts the adbd daemon with root permissions
- **adb remount**
  + remounts the /system partition on the device read-write
- **adb shell**
  + run remote shell interactively
- **adb push/pull**
  + copy file/dir to/from device/
- **adb install/unistall**
  + push this package file to the device and install it/remove this app package from the device
- **adb devices**
  + list all connected devices

## Example
```
adb root
adb remount
adb push out/target/product/generic_x86_64/vendor/lib64/libxxxx.so /vendor/lib64
adb pull /data/tombstone/tombstone_00 ~
```
