# CleanSensitiveFiles.ps1
# 用于批量清理 Git 历史中的敏感文件

# 设置控制台编码为 UTF-8，避免中文乱码
$OutputEncoding = [Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
chcp 65001 > $null

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

Write-Host "开始清理敏感文件历史，输入文件路径（支持空格和反斜杠），输入 Quit[] 退出循环。" -ForegroundColor Cyan

while ($true) {
    # 提示用户输入
    $inputPath = Read-Host "`n请输入文件路径 (或 Quit[] 结束)"
    
    # 检查退出条件（忽略大小写）
    if ($inputPath -eq "Quit[]") {
        Write-Host "退出输入循环。" -ForegroundColor Yellow
        break
    }
    
    # 去除首尾空格
    $inputPath = $inputPath.Trim()
    if ([string]::IsNullOrEmpty($inputPath)) {
        Write-Host "路径不能为空，请重新输入。" -ForegroundColor Red
        continue
    }
    
    # 将反斜杠替换为正斜杠（Git 内部使用正斜杠）
    $gitPath = $inputPath -replace '\\', '/'
    
    Write-Host "处理路径: $gitPath" -ForegroundColor Green
    
    # 执行 git filter-repo 命令
    # 注意：路径用双引号括起来，确保空格被正确处理
    & git filter-repo --path "$gitPath" --invert-paths --force
    
    # 检查命令是否执行成功
    if ($LASTEXITCODE -ne 0) {
        Write-Host "执行失败，请检查路径是否正确。" -ForegroundColor Red
        # 可选择是否继续
        $continue = Read-Host "是否继续处理其他文件？(y/n)"
        if ($continue -ne 'y') { break }
    } else {
        Write-Host "成功处理: $gitPath" -ForegroundColor Green
    }
}

# 循环结束，提示输入远程仓库 URL
Write-Host "`n所有文件处理完毕。" -ForegroundColor Cyan
$remoteUrl = Read-Host "请输入远程仓库 URL (例如 https://github.com/用户名/仓库.git)"

if ([string]::IsNullOrEmpty($remoteUrl)) {
    Write-Host "未输入 URL，跳过推送步骤。" -ForegroundColor Yellow
    exit 0
}

# 重新关联远程仓库（filter-repo 会移除原有 remote）
Write-Host "添加远程仓库: $remoteUrl" -ForegroundColor Yellow
git remote add origin $remoteUrl

# 强制推送所有分支和标签
Write-Host "正在强制推送到远程仓库..." -ForegroundColor Yellow
git push origin --force --all
git push origin --force --tags

if ($LASTEXITCODE -eq 0) {
    Write-Host "推送成功！远程仓库历史已更新。" -ForegroundColor Green
} else {
    Write-Host "推送失败，请检查网络或远程仓库权限。" -ForegroundColor Red
}

Write-Host "脚本执行完毕。" -ForegroundColor Cyan