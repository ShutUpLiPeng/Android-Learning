# jar 工具
查看jar包的内部组成
```
$ jar tvf classes.jar 
     0 Thu Mar 14 12:08:58 CST 2019 META-INF/
    61 Thu Mar 14 12:08:58 CST 2019 META-INF/MANIFEST.MF
     0 Tue Jan 01 00:00:00 CST 2008 android/
     0 Tue Jan 01 00:00:00 CST 2008 android/arch/
     0 Tue Jan 01 00:00:00 CST 2008 android/arch/core/
 12713 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$anim.class
  2017 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$animator.class
  4725 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$array.class
 39220 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$attr.class
  4502 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$bool.class
 19970 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$color.class
 60657 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$dimen.class
 39818 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$drawable.class
  1191 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$fraction.class
 38714 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$id.class
  8104 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$integer.class
  4609 Thu Mar 14 12:08:40 CST 2019 android/arch/core/R$interpolator.class 
```
# javap 工具
打印class文件信息
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
