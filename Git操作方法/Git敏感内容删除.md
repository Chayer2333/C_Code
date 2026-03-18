# 删除 GitHub 已提交的敏感内容和历史记录

## 0. 安装插件

```Shell
    pip install git-filter-repo
```

## 1. 创建备份

---

## 2. 进入仓库目录，检查状态

```Shell
    E:
    cd E:\2_Code\00_C艹
    git status
```

应该输出 `nothing to commit, working tree clean`。***ps:如果有未提交的修改，请先处理。***

## 3. 彻底删除文件或重命名

* 删除

```Shell
    git filter-repo --path "your file" --invert-paths --force
```

* 重命名

```Shell
    git filter-repo --path-rename 'Old:New' --force
```

***ps:用单引号避免 `:` 解析错误***

***特别注意，Git使用正斜杠 ` / ` 而非反斜杠 ` \ `***

---

## 4. 重新关联*GitHub*仓库

```Shell
    git remote add origin <你的远程仓库URL>
```

## 5. 可验证历史是否清除

```Shell
    git show <某个旧commit的哈希>
```

## 6. 强制推送至仓库覆盖历史

```Shell
    git push origin --force --all
    git push origin --force --tags    # 如果有标签
```

---

***ps:可直接运行脚本：Git操作方法\CleanSensitiveFiles.ps1***

```Shell
    E:
    cd E:\2_Code\00_C艹
    powershell -File "CleanSensitiveFiles.ps1"  # 适用于输入完整路径
    # 或者：
    .\RenameSensitiveFiles.ps1
```

***ps:Shell中粘贴键为：`ctrl+shift+v`***
***pss：如果遇到乱码问题，基本是控制台和脚本文件编码不一致造成的，需保存为 `UTF-8 with BOM`***