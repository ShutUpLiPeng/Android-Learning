# Samba服务器
实现 Windows 和 linux 的文件共享

https://tutorials.ubuntu.com/tutorial/install-and-configure-samba#0
## 安装Samba
```shell
sudo apt update
sudo apt install samba

whereis samba
```
## 配置Samba
```
mkdir /home/<username>/sambashare/

sudo nano /etc/samba/smb.conf
[sambashare]
    comment = Samba on Ubuntu
    path = /home/username/sambashare
    read only = no
    browsable = yes
    
sudo service smbd restart
```
## 配置Samba用户密码
```
sudo smbpasswd -a username
```
**Note:** Username used must belong to a system account, else it won't save.
## 连接
Windows上Win+R 
输入 \\ip-address\sambashare
输入用户和密码就可以登录了
