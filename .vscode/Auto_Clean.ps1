# Auto_Clean.ps1 - 增强版本，强制终止进程
param(
    [string]$SourceFile
)

# 设置窗口标题
$Host.UI.RawUI.WindowTitle = "===TDM-GCC C Compiler==="

# 获取当前工作目录
$workspaceRoot = Get-Location
$sourcePath = Resolve-Path $SourceFile
$dirName = Split-Path $sourcePath -Parent
$baseName = [System.IO.Path]::GetFileNameWithoutExtension($SourceFile)

# 创建临时英文路径
$tempDir = "E:\8_Buffer\C_Compile\TDM-GCC\Temp"
$exePath = Join-Path $tempDir "$baseName.exe"

# 显示信息
Write-Host "=== ====== ====== == TDM-GCC C Compiler == ====== ====== ===`n" -ForegroundColor Cyan
Write-Host "Source: $SourceFile" -ForegroundColor Gray
Write-Host "Executable: $exePath" -ForegroundColor Gray


# ============================================
# 第1步：清理前的准备工作（强制终止进程）
# ============================================
if (Test-Path $tempDir) {
    Write-Host "[Step 1/5] Preparing cleanup..." -ForegroundColor Yellow
    
    # 1. 尝试获取Temp文件夹中所有可能的exe进程
    Write-Host "  - Checking for running processes..." -ForegroundColor Gray
    
    # 获取当前编译的exe进程名（不带扩展名）
    $currentExeName = $baseName
    
    # 获取Temp文件夹中所有exe文件对应的进程名
    $exeFiles = Get-ChildItem -Path $tempDir -Filter "*.exe" -ErrorAction SilentlyContinue
    
    # 如果没有找到exe文件，但文件夹存在，尝试获取所有可能相关的进程
    if ($exeFiles.Count -eq 0) {
        # 如果Temp文件夹存在但没有exe文件，尝试猜测可能的进程名
        $potentialProcesses = Get-Process | Where-Object {
            # 查找可能来自Temp目录的进程
            try {
                $procPath = $_.Path
                if ($procPath -and $procPath -like "*Temp*") {
                    return $true
                }
            }
            catch {
                # 忽略无法访问的进程
            }
            return $false
        }
        
        if ($potentialProcesses.Count -gt 0) {
            Write-Host "  - Found potential processes from Temp folder" -ForegroundColor Gray
            foreach ($proc in $potentialProcesses) {
                Write-Host "    * $($proc.ProcessName)" -ForegroundColor DarkGray
            }
        }
    }
    else {
        # 列出所有找到的exe文件
        Write-Host "  - Found $($exeFiles.Count) executable(s) in Temp folder:" -ForegroundColor Gray
        foreach ($exe in $exeFiles) {
            Write-Host "    * $($exe.BaseName)" -ForegroundColor DarkGray
        }
    }
    
    # 2. 强制终止这些进程
    Write-Host "  - Terminating processes..." -ForegroundColor Gray
    
    # 方法1：先尝试友好地终止当前编译的exe进程
    try {
        Get-Process -Name $currentExeName -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
        Write-Host "    * Stopped process: $currentExeName" -ForegroundColor DarkGreen
    }
    catch {
        # 忽略错误
    }
    
    # 方法2：终止所有Temp文件夹中的exe进程
    foreach ($exeFile in $exeFiles) {
        $procName = $exeFile.BaseName
        if ($procName -ne $currentExeName) {  # 避免重复处理
            try {
                Get-Process -Name $procName -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
                Write-Host "    * Stopped process: $procName" -ForegroundColor DarkGreen
            }
            catch {
                # 忽略错误
            }
        }
    }
    
    # 方法3：使用更强大的方式终止进程（使用taskkill）
    Write-Host "  - Force-killing processes using taskkill..." -ForegroundColor Gray
    
    # 尝试终止可能锁住Temp文件夹的进程
    $taskkillCmds = @(
        "taskkill /F /IM `"$currentExeName.exe`"",
        "taskkill /F /FI `"IMAGENAME eq $currentExeName.exe`""
    )
    
    foreach ($cmd in $taskkillCmds) {
        try {
            cmd /c "$cmd >nul 2>nul"
        }
        catch {
            # 忽略错误
        }
    }
    
    # 等待进程完全终止
    Write-Host "  - Waiting for processes to terminate..." -ForegroundColor Gray
    Start-Sleep -Milliseconds 500
    
    # 再次检查并强制终止
    $stillRunning = Get-Process -Name $currentExeName -ErrorAction SilentlyContinue
    if ($stillRunning) {
        Write-Host "  - Process still running, using more aggressive method..." -ForegroundColor Yellow
        
        # 使用wmic命令强制终止
        try {
            $wmicResult = wmic process where "name='$currentExeName.exe'" delete
            if ($wmicResult -like "*Deleting instance*") {
                Write-Host "    * Force-killed via WMIC" -ForegroundColor DarkGreen
            }
        }
        catch {
            # 忽略错误
        }
        
        # 再次等待
        Start-Sleep -Milliseconds 500
    }
}

# ============================================
# 第2步：清理临时文件夹
# ============================================
Write-Host "`n[Step 2/5] Cleaning temporary folder..." -ForegroundColor Yellow

# 尝试删除整个Temp文件夹（如果存在）
$folderDeleted = $false
if (Test-Path $tempDir) {
    # 方法1：直接删除整个文件夹
    try {
        Remove-Item $tempDir -Recurse -Force -ErrorAction Stop
        Write-Host "  - Temp folder deleted successfully" -ForegroundColor Green
        $folderDeleted = $true
    }
    catch {
        Write-Host "  - Cannot delete entire folder, trying alternative methods..." -ForegroundColor Yellow
        
        # 方法2：先删除文件夹内的所有文件，再删除文件夹
        try {
            # 尝试删除所有文件
            Get-ChildItem -Path $tempDir -Recurse -Force -ErrorAction SilentlyContinue | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue
            
            # 然后删除空文件夹
            Start-Sleep -Milliseconds 300
            Remove-Item $tempDir -Force -ErrorAction Stop
            Write-Host "  - Temp folder deleted (alternative method)" -ForegroundColor Green
            $folderDeleted = $true
        }
        catch {
            Write-Host "  - Still cannot delete folder, trying file-by-file deletion..." -ForegroundColor Yellow
            
            # 方法3：逐个文件删除
            try {
                # 删除所有文件
                Get-ChildItem -Path $tempDir -File -Recurse -Force -ErrorAction SilentlyContinue | ForEach-Object {
                    try {
                        Remove-Item $_.FullName -Force -ErrorAction SilentlyContinue
                    }
                    catch {
                        # 忽略单个文件删除失败
                    }
                }
                
                # 删除所有子文件夹
                Get-ChildItem -Path $tempDir -Directory -Recurse -Force -ErrorAction SilentlyContinue | ForEach-Object {
                    try {
                        Remove-Item $_.FullName -Force -Recurse -ErrorAction SilentlyContinue
                    }
                    catch {
                        # 忽略子文件夹删除失败
                    }
                }
                
                # 最后删除主文件夹
                Start-Sleep -Milliseconds 500
                Remove-Item $tempDir -Force -ErrorAction SilentlyContinue
                
                Write-Host "  - Temp folder cleaned file-by-file" -ForegroundColor Green
                $folderDeleted = $true
            }
            catch {
                Write-Host "  - WARNING: Could not fully clean temp folder" -ForegroundColor Red
                Write-Host "    You may need to manually close programs using the folder." -ForegroundColor DarkYellow
            }
        }
    }
}
else {
    Write-Host "  - Temp folder does not exist" -ForegroundColor Gray
    $folderDeleted = $true
}

# ============================================
# 第3步：重新创建临时文件夹
# ============================================
if ($folderDeleted) {
    Write-Host "`n[Step 3/5] Creating new temp folder..." -ForegroundColor Yellow
    try {
        New-Item -ItemType Directory -Path $tempDir -Force | Out-Null
        Write-Host "  - Temp folder created" -ForegroundColor Green
    }
    catch {
        Write-Host "  - ERROR: Cannot create temp folder" -ForegroundColor Red
        Write-Host "    $_" -ForegroundColor DarkRed
        exit 1
    }
}
else {
    Write-Host "  - Using existing temp folder (cleanup incomplete)" -ForegroundColor Yellow
}

# ============================================
# 第4步：编译
# ============================================
Write-Host "`n[Step 4/5] Compiling..." -ForegroundColor Yellow

$gcc = "C:\TDM-GCC-64\bin\gcc.exe"

# 构建编译参数
$compileArgs = @(
    "-fdiagnostics-color=always",
    "-std=c17",
    "-g",
    "-Wall",
    "-Wextra",
    "-static-libgcc",
    "`"$sourcePath`"",
    "-o",
    "`"$exePath`""
)

# 显示编译命令
Write-Host "  - Command: $gcc $compileArgs" -ForegroundColor DarkGray

# 执行编译
& $gcc $compileArgs

if ($LASTEXITCODE -ne 0) {
    Write-Host "  - ERROR: Compilation failed!" -ForegroundColor Red
    Write-Host "    Check the error messages above." -ForegroundColor DarkYellow
    exit 1
}

Write-Host "  `n- Compilation successful!" -ForegroundColor Green

# ============================================
# 第5步：运行程序
# ============================================
Write-Host "`n[Step 5/5] Running program..." -ForegroundColor Yellow
$test = "-" * 100
Write-Host $test -ForegroundColor Gray

# 运行程序
$process = $null
try {
    $process = Start-Process -FilePath $exePath -NoNewWindow -Wait -PassThru -ErrorAction Stop
}
catch {
    Write-Host "  - ERROR: Cannot run program" -ForegroundColor Red
    Write-Host "    $_" -ForegroundColor DarkRed
}

Write-Host $test -ForegroundColor Gray

if ($process) {
    Write-Host "  - Program exit code: $($process.ExitCode)" -ForegroundColor Cyan
}

# ============================================
# 第6步：程序运行后清理（可选）
# ============================================
Write-Host "`n[Cleanup] Removing executable..." -ForegroundColor Yellow

# 等待程序完全退出
Start-Sleep -Milliseconds 300

# 尝试删除exe文件
$exeDeleted = $false
if (Test-Path $exePath) {
    try {
        # 先检查进程是否仍在运行
        $procName = [System.IO.Path]::GetFileNameWithoutExtension($exePath)
        $running = Get-Process -Name $procName -ErrorAction SilentlyContinue
        
        if ($running) {
            Write-Host "  - Program still running, stopping it..." -ForegroundColor Yellow
            $running | Stop-Process -Force -ErrorAction SilentlyContinue
            Start-Sleep -Milliseconds 300
        }
        
        # 删除文件
        Remove-Item $exePath -Force -ErrorAction Stop
        Write-Host "  - Executable removed" -ForegroundColor Green
        $exeDeleted = $true
    }
    catch {
        Write-Host "  - WARNING: Could not remove executable" -ForegroundColor Red
        Write-Host "    It may still be in use. Path: $exePath" -ForegroundColor DarkYellow
    }
}
else {
    Write-Host "  - Executable not found (may have been deleted)" -ForegroundColor Gray
    $exeDeleted = $true
}

# 如果exe已删除且Temp文件夹为空，删除Temp文件夹
if ($exeDeleted -and (Test-Path $tempDir)) {
    try {
        $items = Get-ChildItem $tempDir -Force -ErrorAction SilentlyContinue
        if ($items.Count -eq 0) {
            Remove-Item $tempDir -Force -ErrorAction SilentlyContinue
            Write-Host "  - Temp folder removed (empty)" -ForegroundColor Green
        }
        else {
            Write-Host "  - Temp folder not empty, keeping it" -ForegroundColor Yellow
            Write-Host "    Files remaining: $($items.Count)" -ForegroundColor DarkGray
        }
    }
    catch {
        Write-Host "  - Could not remove temp folder" -ForegroundColor DarkYellow
    }
}

# 完成
Write-Host "`n=== ==== === Compilation and execution complete === ==== ===" -ForegroundColor Cyan
Write-Host "Press any key to exit..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')