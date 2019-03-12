可视化工具git-gui, tig, gitk：
```
sudo apt-get install git-gui tig
```
- **git config**
```
git config --global user.email “xxx@yyy.com” 

git config --global user.name  “xxx” 

git config --global commit.template ~/.git.commit_template.txt
```
- **git pull**
- **git add .**
- **git commit**
```
补交代码：
git add.
git commit --amend --no-edit
git push aosp HEAD:refs/for/A_BRANCH
```
- **git remote**
```
$ git remote 
origin
```
- **git push**
```
git remote
git push origin HEAD:refs/for/A_BRANCH
```
- **git branch**
```
git branch -a
```
- **git checkout**
- ****
- **git log**
```
git log dev...master
git log --oneline
```
- **git format-patch**
- **git am**
```
git format-patch BACK_BRANCH -o ~/patch
git am ~/patch/0* --reject
git am --continue
```

