# RenameSensitiveFiles.ps1
# 用于批量重命名 Git 历史中的敏感文件（路径不变，只改文件名）

# ---------- 编码设置 ----------
chcp 65001 > $null
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
$OutputEncoding = [Console]::OutputEncoding
# ------------------------------

# 检查当前目录是否为 Git 仓库
if (-not (Test-Path ".git")) {
    Write-Host "错误：当前目录不是 Git 仓库的根目录（缺少 .git 文件夹）。" -ForegroundColor Red
    exit 1
}

# 检查 git filter-repo 是否可用
if (-not (Get-Command "git-filter-repo" -ErrorAction SilentlyContinue)) {
    Write-Host "错误：未找到 git-filter-repo，请先安装（例如：pip install git-filter-repo）。" -ForegroundColor Red
    exit 1
}

Write-Host "开始重命名 Git 历史中的敏感文件（路径不变，只改文件名）" -ForegroundColor Cyan
Write-Host "输入旧路径（例如：1_经验池/0_程序设计/数据结构/999952.cpp），输入 Quit[] 退出循环。`n" -ForegroundColor Yellow

while ($true) {
    # 1. 获取旧路径
    $oldPath = Read-Host "`n请输入旧文件路径 (或 Quit[] 结束)"
    if ($oldPath -eq "Quit[]") {
        Write-Host "退出输入循环。" -ForegroundColor Yellow
        break
    }
    $oldPath = $oldPath.Trim()
    if ([string]::IsNullOrEmpty($oldPath)) {
        Write-Host "路径不能为空，请重新输入。" -ForegroundColor Red
        continue
    }

    # 2. 获取新文件名
    $newName = Read-Host "请输入新文件名 (例如：6666.cpp)"
    $newName = $newName.Trim()
    if ([string]::IsNullOrEmpty($newName)) {
        Write-Host "新文件名不能为空，请重新输入。" -ForegroundColor Red
        continue
    }

    # 3. 将旧路径中的反斜杠替换为正斜杠
    $oldPath = $oldPath -replace '\\', '/'

    # 提取目录部分（假设路径包含文件名，去掉最后一部分即为目录）
    # 使用 Split-Path 可能受 PS 版本影响，直接用字符串操作
    $lastSlashIndex = $oldPath.LastIndexOf('/')
    if ($lastSlashIndex -eq -1) {
        # 如果路径中没有斜杠，说明文件就在根目录下
        $directory = ""
    } else {
        $directory = $oldPath.Substring(0, $lastSlashIndex + 1)  # 包含最后的斜杠
    }

    # 构造新路径
    $newPath = $directory + $newName

    # 4. 构造映射字符串（用单引号括起来）
    $renameMapping = "'$oldPath`:$newPath'"   # 注意冒号前加反引号转义？不，在单引号内不需要转义冒号，但为了安全我们直接拼接字符串
    # 实际上在单引号内，冒号无需转义。我们直接构造字符串，然后在命令中嵌入单引号。
    # 更好的方式：生成参数时直接使用单引号包围，避免 PowerShell 解析。
    # 但 filter-repo 接收的参数应该不带外层引号，由 PowerShell 传递时保留内部引号。

    # 5. 执行 git filter-repo 命令
    Write-Host "处理重命名: $oldPath -> $newPath" -ForegroundColor Green
    # 使用 --% 停止解析，或者直接传递带单引号的字符串。
    # 这里采用将整个参数用双引号包围，内部用单引号的方法，但之前用户反馈单引号整体括起来有效，
    # 所以我们构造的字符串是 '旧路径:新路径'，但要注意 PowerShell 参数传递时引号的处理。
    # 最可靠的方式：将映射字符串作为变量，然后用 --% 停止解析，但 --% 后不能使用变量。
    # 所以我们采用：用单引号包围映射字符串，然后作为参数传递。这样 PowerShell 会将内部单引号保留。
    $arg = "--path-rename='$oldPath`:$newPath'"
    # 但上述写法在 PowerShell 中可能被解析错误，因为单引号内不能再包含单引号。
    # 实际上我们可以这样：直接传递 --path-rename 参数，值用单引号括起来。
    # 我们使用 Invoke-Expression 来构造命令字符串，但有一定风险。推荐使用 Start-Process 或直接调用。
    
    # 简单有效的方式：使用 --% 停止解析，但后面只能跟字面字符串，不能使用变量。
    # 既然我们已经有了 $oldPath 和 $newPath，可以在命令中直接插入值，但需要注意空格。
    # 因为路径可能包含空格，所以必须用引号括起来。我们构造完整的命令字符串，然后使用 Invoke-Expression。
    
    # 构造命令字符串，注意内部使用单引号包围映射字符串
    $cmd = "git filter-repo --path-rename '$oldPath`:$newPath' --force"
    Write-Host "执行命令: $cmd" -ForegroundColor DarkGray
    Invoke-Expression $cmd
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "执行失败，请检查路径是否正确。" -ForegroundColor Red
        $continue = Read-Host "是否继续处理其他文件？(y/n)"
        if ($continue -ne 'y') { break }
    } else {
        Write-Host "成功处理: $oldPath -> $newPath" -ForegroundColor Green
    }
}

Write-Host "`n所有文件处理完毕。" -ForegroundColor Cyan
$remoteUrl = Read-Host "请输入远程仓库 URL (例如 https://github.com/用户名/仓库.git)"

if ([string]::IsNullOrEmpty($remoteUrl)) {
    Write-Host "未输入 URL，跳过推送步骤。" -ForegroundColor Yellow
    exit 0
}

Write-Host "添加远程仓库: $remoteUrl" -ForegroundColor Yellow
git remote add origin $remoteUrl

Write-Host "正在强制推送到远程仓库..." -ForegroundColor Yellow
git push origin --force --all
git push origin --force --tags

if ($LASTEXITCODE -eq 0) {
    Write-Host "推送成功！远程仓库历史已更新。" -ForegroundColor Green
} else {
    Write-Host "推送失败，请检查网络或远程仓库权限。" -ForegroundColor Red
}

Write-Host "脚本执行完毕。" -ForegroundColor Cyan