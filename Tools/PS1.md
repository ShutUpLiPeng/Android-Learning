设置PS1：

source ~/.git-prompt.sh

PS1='\n\[\033[32m\]\u\[\033[36m\]: \W \[\033[33m\]$(__git_ps1 "(%s) ")\[\033[0m\]$ '

- **__git_ps1**
需要安装.git-prompt.sh
```
curl -o ~/.git-prompt.sh https://raw.githubusercontent.com/git/git/master/contrib/completion/git-prompt.sh
```
```
bash.rc里面添加
source ~/.git-prompt.sh
```
