Windows上用github, 及其配置
# 安装git 
https://gitforwindows.org/

在windows上安装git for windows， 安装目录：C:\Program Files\Git\
**包括如下git工具：**
  + Git Bash
  + Gitk
  + tig
  + Git Gui
  + Git lfs
# 配置ssh key
https://help.github.com/en/articles/connecting-to-github-with-ssh
## 本地生成ssh key
在git bash里面生成ssh key值
```
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
```
*确保ssh-agent启动成功*
```
# start the ssh-agent in the background
$ eval $(ssh-agent -s)
> Agent pid 59566

ssh-add ~/.ssh/id_rsa
```
## 将生成的公钥配置到github服务器上
https://help.github.com/en/articles/adding-a-new-ssh-key-to-your-github-account

公钥: clip < ~/.ssh/id_rsa.pub
## 本地测试ssh是否连接成功
```
$ ssh -T git@github.com
> Hi username! You've successfully authenticated, but GitHub does not
> provide shell access.
```
# 拉取代码
在git bash里面
```
git clone git@github.com:xxx/yyy.git
git clone https://github.com/xxx/yyy.git
```
# 修改并提交修改
