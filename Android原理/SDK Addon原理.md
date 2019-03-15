AOSP源代码目录:
```
device/sample/
├── apps
├── etc
├── frameworks
├── overlays
├── products
├── sdk_addon
└── skins
```
sdk 编译原理， 配置及过程简要介绍
- **device/sample/products/sample_addon.mk**
- **build/make/core/tasks/sdk-addon.mk**
根据编译规则
- make PRODUCT-<PRODUCT_NAME>-sdk_addon
最终会生成img和addon的两个zip
```
.
├── platform_library-eng.lipeng-linux-x86-img.zip
└── platform_library-eng.lipeng-linux-x86.zip

platform_library-eng.lipeng-linux-x86-img解压出来
armeabi-v7a
├── armeabi-v7a
│   ├── build.prop
│   ├── data
│   ├── NOTICE.txt
│   ├── ramdisk.img
│   ├── source.properties
│   ├── system.img
└─└── vendor.img

platform_library-eng.lipeng-linux-x86解压后
│   ├── docs
│   ├── hardware.ini
│   ├── libs
│   ├── manifest.ini
│   ├── skins
└─└── source.properties
```
# AndroidProducts.mk 添加编译选项
```
PRODUCT_MAKEFILES := \
  $(LOCAL_DIR)/sample_addon.mk
```
# 添加相应的编译规则sample_addon.mk
```
# List of apps and optional libraries (Java and native) to put in the add-on system image.
PRODUCT_PACKAGES := \
	PlatformLibraryClient \
	com.example.android.platform_library \
	libplatform_library_jni

# Manually copy the optional library XML files in the system image.
PRODUCT_COPY_FILES := \
    device/sample/frameworks/PlatformLibrary/com.example.android.platform_library.xml:system/etc/permissions/com.example.android.platform_library.xml

# name of the add-on
PRODUCT_SDK_ADDON_NAME := platform_library

# Copy the manifest and hardware files for the SDK add-on.
# The content of those files is manually created for now.
PRODUCT_SDK_ADDON_COPY_FILES := \
	device/sample/sdk_addon/source.properties:source.properties \
    device/sample/sdk_addon/manifest.ini:manifest.ini \
    device/sample/sdk_addon/hardware.ini:hardware.ini \
	$(call find-copy-subdir-files,*,device/sample/skins/WVGAMedDpi,skins/WVGAMedDpi)


# Add this to PRODUCT_SDK_ADDON_COPY_FILES to copy the files for an
# emulator skin (or for samples)
#$(call find-copy-subdir-files,*,device/sample/skins/WVGAMedDpi,skins/WVGAMedDpi)

# Copy the jar files for the optional libraries that are exposed as APIs.
PRODUCT_SDK_ADDON_COPY_MODULES := \
    com.example.android.platform_library:libs/platform_library.jar

# Rules for public APIs
PRODUCT_SDK_ADDON_STUB_DEFS := $(LOCAL_PATH)/addon_stub_defs

PRODUCT_SDK_ADDON_SYS_IMG_SOURCE_PROP := device/sample/sdk_addon/source.properties

# Name of the doc to generate and put in the add-on. This must match the name defined
# in the optional library with the tag
#    LOCAL_MODULE:= platform_library
# in the documentation section.
PRODUCT_SDK_ADDON_DOC_MODULES := platform_library

# This add-on extends the default sdk product.
$(call inherit-product, $(SRC_TARGET_DIR)/product/sdk.mk)

# Real name of the add-on. This is the name used to build the add-on.
# Use 'make PRODUCT-<PRODUCT_NAME>-sdk_addon' to build the add-on.
PRODUCT_NAME := sample_addon
```
## PRODUCT_PACKAGES ##
- List of apps and optional libraries (Java and native) to put in the add-on system and vendor image.
- 需要编译的Java动态库静态库， Native C++库和进程文件等，会打包到img文件中
## PRODUCT_COPY_FILES ##
- Manually copy the optional library XML files in the system and vendor image.
- 需要在编译过程中拷贝到img文件中
## PRODUCT_SDK_ADDON_NAME ##
- name of the add-on
- sdk addon的名字，必须要， 不然不会生成编译规则
## PRODUCT_SDK_ADDON_COPY_FILES ##
: Copy the manifest and hardware files for the SDK add-on. The content of those files is manually created for now.
: 只是拷贝到sdk addon根目录里面
## PRODUCT_SDK_ADDON_COPY_MODULES ##
- Copy the jar files for the optional libraries that are exposed as APIs.
- 拷贝到jar到相应的目录
## PRODUCT_SDK_ADDON_STUB_DEFS ##
- Rules for public APIs
```
addon_stub_defs:
+com.example.android.platform_library.*
-com.example.android.platform_library.exculde.*
```
其中：
  + +: 公开出去的package
  + -: 不公开的隐藏package
## PRODUCT_SDK_ADDON_SYS_IMG_SOURCE_PROP ##
- copy source.properties to image
## PRODUCT_SDK_ADDON_DOC_MODULES ##
- Name of the doc to generate and put in the add-on.
## PRODUCT_NAME ##
- Real name of the add-on. This is the name used to build the add-on.
# 编译过程 #
(1) 首先会在out/target/common/obj/JAVA_LIBRARIES/xxx_intermediates生成**stubs.jar**

(2) 然后会根据**PRODUCT_SDK_ADDON_STUB_DEFS := $(LOCAL_PATH)/addon_stub_defs**文件来过滤stubs.jar
```
addon_stub_defs：
+com.example.android.platform_library.*
- com.example2.android.*
其中+表示package会公开, -表示隐藏
```
(3) 过滤生成**stubs_stub-addon.jar**， 并重命名并copy到相应目录
- -rw-rw-r-- 1 lipeng lipeng **1255**  3月 14 12:10 stubs.jar                                   // 过滤前的文件
- -rw-rw-r-- 1 lipeng lipeng  **530**  3月 14 13:25 stubs_stub-addon.jar                // 过滤后的文件
最后生成addon里面的Jar由.class文件组成：
```
platform_library $ javap -c -s PlatformLibrary.class 
public final class com.example.android.platform_library.PlatformLibrary {
  public com.example.android.platform_library.PlatformLibrary();
    descriptor: ()V
    Code:
       0: new           #8                  // class java/lang/RuntimeException
       3: dup
       4: ldc           #10                 // String stub
       6: invokespecial #13                 // Method java/lang/RuntimeException."<init>":(Ljava/lang/String;)V
       9: athrow

  public int getInt(boolean);
    descriptor: (Z)I
    Code:
       0: new           #8                  // class java/lang/RuntimeException
       3: dup
       4: ldc           #10                 // String stub
       6: invokespecial #13                 // Method java/lang/RuntimeException."<init>":(Ljava/lang/String;)V
       9: athrow
}
```
