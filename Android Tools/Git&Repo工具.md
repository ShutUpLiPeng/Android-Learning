# Git
https://git-scm.com/docs

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
- **git diff**
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
- **git reset**
```
git reset --hard HEAD~
```
- **git log**
```
git log dev...master
git log --oneline
```
- **git stash**
- **git stash pop**
- **git format-patch**
- **git am**
```
git format-patch BACK_BRANCH -o ~/patch
git am ~/patch/0* --reject
git am --continue
```
- **git blame**

# Repo
- **repo init**
- **repo sync**
- **repo start**
- **repo status**
- **repo forall**
```
repo init -u https://android.googlesource.com/platform/manifest -b <branch>
repo sync -c
repo start <branch> --all
repo foreall -gc "git log --oneline branch1..branch2" > ~/repoalldiff.txt

```
