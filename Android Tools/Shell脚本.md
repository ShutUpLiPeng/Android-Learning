https://linuxtools-rst.readthedocs.io/zh_CN/latest/base/03_text_processing.html#tr
- **sed**
- **sort**
- **cut**
- **awk**
- **grep**
- **uniq**
- **diff**
- **find**
    + find . -regex  ".*\.\(txt\|pdf\)" -exec grep -inr "iauto" {} +
- **wc**
- **xargs**
- **tr**

# case 1
- **repo forall 得到需要的log信息**
```
repo forall -c 'echo "project: $REPO_PROJECT" && git log origin/Leepi_MTK_E3_NoMerge..leepi/master --no-decorate --numstat --author="@iauto.com" --author="@pset.suntec.net" --author="@suntec.net" --no-merges --pretty=format:"%H %ae %cd %s" && echo'
```
- **sed删除**
```
sed -i "/\.java/d" ~/repo.txt
sed -i "/Android.mk/d" ~/repo.txt
sed -i "/Android.bp/d" ~/repo.txt
```
- **查找过滤， 并得到行数**
```
grep -hnr "@" repo.txt > lineuncut.txt
cut -d: -f1 ~/lineuncut.txt > ~/linecut.txt
```
- **计算下一行减去上一行**
```
awk 'NR > 1 { if($0 - prev == 2) print $0 - 2 } { prev = $0 }' <linecut.txt  | sort -nr > line.txt
```
- **删除不必要的空格和需要删除的行**
```
for line in $(cat line.txt); do 
temp=$(($line+1))
sed -i "$temp d" ~/repo.txt; 
sed -i "$line d" ~/repo.txt; 
done

grep -hnr "project:" repo.txt > lineuncut.txt
cut -d: -f1 ~/lineuncut.txt > ~/linecut.txt
awk 'NR > 1 { if($0 - prev == 2) print $0 - 2 } { prev = $0 }' <linecut.txt  | sort -nr > line.txt
for line in $(cat line.txt); do 
temp2=$(($line+1))
sed -i "$temp2 d" ~/repo.txt; 
sed -i "$line d" ~/repo.txt; 
done
```
# case 2
检查android.jar中是否有packages.txt中的所有package信息
source build/envsetup.sh
- **jar工具**
```
jar tvf android.jar >  1.txt
for line in $(cat packages.txt)
do
    if cat 1.txt | grep "$line";then
    	echo -e "\033[32m $line \033[0m"
	else
		echo -e "\033[31m $line not found \033[0m"
	fi
done
```
# case 3
```
croot

echo "============= Check Android.mk Vendor Module ====================="
cd ivi
find -iname "Android.mk" | xargs grep -iEnr "LOCAL_MODULE|LOCAL_PACKAGE_NAME" > ~/module.txt
sed -i "/LOCAL_MODULE_/d" ~/module.txt
cut -d: -f1 ~/module.txt > ~/module1.txt
sort ~/module1.txt | uniq -c > ~/module2.txt

find -iname "Android.mk" | xargs grep -inr LOCAL_VENDOR_MODULE > ~/vendor.txt
cut -d: -f1 ~/vendor.txt > ~/vendor1.txt
sort ~/vendor1.txt | uniq -c > ~/vendor2.txt

diff ~/module2.txt ~/vendor2.txt

echo "================ Check Android.bp Vendor Module =========================="
cd ivi
find -iname "Android.bp" | xargs grep -inr "cc_library" > ~/module.txt
cut -d: -f1 ~/module.txt > ~/module1.txt
sort ~/module1.txt | uniq -c > ~/module2.txt

find -iname "Android.bp" | xargs grep -inr "vendor: true" > ~/vendor.txt
cut -d: -f1 ~/vendor.txt > ~/vendor1.txt
sort ~/vendor1.txt | uniq -c > ~/vendor2.txt

diff ~/module2.txt ~/vendor2.txt

rm ~/vendor*
rm ~/module*
```
