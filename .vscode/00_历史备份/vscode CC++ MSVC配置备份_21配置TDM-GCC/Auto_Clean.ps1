# Auto_Clean.ps1
param(
    [string]$SourceFile
)

# 获取当前工作目录
$workspaceRoot = Get-Location
$sourcePath = Resolve-Path $SourceFile
$dirName = Split-Path $sourcePath -Parent
$baseName = [System.IO.Path]::GetFileNameWithoutExtension($SourceFile)

# 创建临时英文路径
$tempDir = "E:\8_Buffer\C_Compile\TDM-GCC\Temp"
if (Test-Path $tempDir) {
    # 删除整个Temp文件夹
    Remove-Item $tempDir -Recurse -Force
}

# 重新创建临时文件夹
New-Item -ItemType Directory -Path $tempDir -Force

# 编译路径
$exePath = Join-Path $tempDir "$baseName.exe"

# 编译
$gcc = "C:\TDM-GCC-64\bin\gcc.exe"
Write-Host "`nCompiling..." -ForegroundColor Yellow
& $gcc -fdiagnostics-color=always `
       -std=c17 `
       -g `
       -Wall `
       -Wextra `
       -static-libgcc `
       $sourcePath `
       -o $exePath

if ($LASTEXITCODE -ne 0) {
    Write-Host "`n[ERROR] Compilation failed!" -ForegroundColor Red
    # 如果编译失败，也清理临时文件夹（可选）
    Remove-Item $tempDir -Recurse -Force -ErrorAction SilentlyContinue
    exit 1
}

Write-Host "`n[OK] Compilation successful!" -ForegroundColor Green

# 运行程序
Write-Host "Running program...`n" -ForegroundColor Green
Start-Process -FilePath $exePath -NoNewWindow -Wait

# 清理
if (Test-Path $tempDir) {
    Remove-Item $tempDir -Recurse -Force
}
Write-Host "`nCleaning up..." -ForegroundColor Yellow

Write-Host "Please Exit..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')