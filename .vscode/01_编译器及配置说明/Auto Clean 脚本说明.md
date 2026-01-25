# *Auto_Clean.ps1* 脚本技术实现文档

*该脚本可以作为 PowerShell 脚本编写的良好范例，展示了如何编写生产级别的自动化脚本。*

<br>

## 1. 脚本整体架构

### 1.1 模块化设计

脚本采用模块化设计，按照功能划分为以下部分：

1. **参数解析与初始化**：处理输入参数，初始化变量

1. **语言检测与配置**：根据文件扩展名确定编译器和标准

1. **进程清理**：终止可能影响编译的正在运行的进程

1. **目录清理**：清理临时目录

1. **编译过程**：调用编译器编译源文件

1. **程序运行**：执行编译后的程序

1. **后期清理**：清理临时文件

1. **结果报告**：输出编译和执行结果

### 1.2 执行流程图

```text
开始 → 参数解析 → 语言检测 → 进程清理 → 目录清理
 ↓                                      ↓
结果报告  ←  后期清理  ←  程序运行  ←  编译过程
```

<br>

## 2. 核心功能实现

### 2.1 多语言编译支持

```powershell
# 文件扩展名检测与配置
$fileExtension = [System.IO.Path]::GetExtension($SourceFile).ToLower()

switch ($fileExtension) {
    ".c" {
        $compiler = "C:\TDM-GCC-64\bin\gcc.exe"
        $standard = "c17"
        $language = "C"
        $compilerName = "GCC"
    }
    ".cpp" {
        $compiler = "C:\TDM-GCC-64\bin\g++.exe"
        $standard = "c++17"
        $language = "C++"
        $compilerName = "G++"
    }
    # ... 其他扩展名支持
}
```

### 设计要点 **:**

* 使用 `switch` 语句实现多分支选择

* 支持多种 C++ 文件扩展名 ( `.cpp` , `.cxx` , `.cc` , `.c++` )

* 统一的变量命名，便于后续处理

### 2.2 进程强制终止机制

```powershell
# 三层进程终止策略
try {
    # 第一层：友好终止
    Get-Process -Name $currentExeName -ErrorAction SilentlyContinue | 
        Stop-Process -Force -ErrorAction SilentlyContinue
    
    # 第二层：taskkill 强制终止
    cmd /c "taskkill /F /IM `"$currentExeName.exe`" >nul 2>nul"
    
    # 第三层：wmic 强制终止
    $wmicResult = wmic process where "name='$currentExeName.exe'" delete
}
```

### 设计要点 **:**

* 渐进式终止策略，从友好到强制

* 多种终止方法，提高成功率

* 错误静默处理，避免脚本中断

### 2.3 目录清理策略

```powershell
# 三级目录清理策略
$folderDeleted = $false

# 第一级：直接删除整个目录
try {
    Remove-Item $tempDir -Recurse -Force -ErrorAction Stop
    $folderDeleted = $true
}
catch {
    # 第二级：先删除内容，再删除目录
    try {
        Get-ChildItem -Path $tempDir -Recurse -Force | Remove-Item -Recurse -Force
        Start-Sleep -Milliseconds 300
        Remove-Item $tempDir -Force -ErrorAction Stop
        $folderDeleted = $true
    }
    catch {
        # 第三级：逐个文件删除
        try {
            Get-ChildItem -Path $tempDir -File -Recurse -Force | ForEach-Object {
                Remove-Item $_.FullName -Force -ErrorAction SilentlyContinue
            }
            # ... 删除子目录
        }
        catch { }
    }
}
```

### 设计要点 **:**

* 三级回退策略，提高清理成功率

* 延迟等待确保文件锁释放

* 详细的错误报告，便于问题诊断

<br>

## 3. 编译参数构建

### 3.1 参数数组构建

```powershell
$compileArgs = @(
    "-fdiagnostics-color=always",  # 彩色诊断输出
    "-std=$standard",               # 语言标准
    "-g",                           # 调试信息
    "-Wall",                        # 所有警告
    "-Wextra",                      # 额外警告
    "-static-libgcc",              # 静态链接库
    "`"$sourcePath`"",             # 源文件路径（引号包裹）
    "-o",                          # 输出参数
    "`"$exePath`""                 # 输出路径（引号包裹）
)
```

### 设计要点 **：**

* 使用数组存储参数，便于管理和修改

* 路径用引号包裹，处理包含空格的路径

* 参数顺序符合编译器要求

### 3.2 编译器调用

```powershell
# 显示编译命令（调试信息）
Write-Host "  - Command: $compiler $compileArgs" -ForegroundColor DarkGray

# 执行编译
& $compiler $compileArgs

# 检查编译结果
if ($LASTEXITCODE -ne 0) {
    Write-Host "  - ERROR: Compilation failed!" -ForegroundColor Red
    exit 1
}
```

### 设计要点 **：**

* 显示实际执行的命令，便于调试

* 使用 `&` 操作符调用外部程序

* 检查 `$LASTEXITCODE` 判断编译结果

<br>

## 4. 错误处理机制

### 4.1 结构化错误处理

```powershell
try {
    # 可能失败的操作
    $process = Start-Process -FilePath $exePath -NoNewWindow -Wait -PassThru -ErrorAction Stop
}
catch {
    # 错误处理
    Write-Host "  - ERROR: Cannot run program" -ForegroundColor Red
    Write-Host "    $_" -ForegroundColor DarkRed
    # 不退出脚本，继续执行清理
}
```

### 设计要点 **：**

* `try-catch` 块保护关键操作

* `-ErrorAction Stop` 将错误转换为异常

* 错误信息显示，便于问题定位

### 4.2 错误静默处理

```powershell
# 静默处理非关键错误
Remove-Item $tempDir -Recurse -Force -ErrorAction SilentlyContinue
```

### 设计要点 **：**

* 对非关键操作使用静默处理

* 避免脚本因非致命错误而中断

* 保持脚本的健壮性

<br>

## 5. 用户界面设计

### 5.1 彩色输出

```powershell
# 使用不同的颜色表示不同的信息类型
Write-Host "=== TDM-GCC $language Compiler ===" -ForegroundColor Cyan         # 标题
Write-Host "[Step 1/5] Preparing cleanup..." -ForegroundColor Yellow          # 步骤
Write-Host "  - Compilation successful!" -ForegroundColor Green               # 成功
Write-Host "  - ERROR: Compilation failed!" -ForegroundColor Red              # 错误
Write-Host "  - WARNING: Could not remove executable" -ForegroundColor Yellow # 警告
```

### 设计要点 **：**

* 颜色编码提高可读性

* 统一的颜色方案

* 状态信息清晰可见

<br>

## 5.2 进度指示

```powershell
# 步骤编号
Write-Host "[Step 1/5] Preparing cleanup..." -ForegroundColor Yellow
Write-Host "[Step 2/5] Cleaning temporary folder..." -ForegroundColor Yellow
# ...
Write-Host "[Step 5/5] Running program..." -ForegroundColor Yellow
```

### 设计要点 **：**

* 明确的进度指示

* 用户了解当前执行阶段

* 便于问题定位

<br>

## 6. 路径处理策略

### 6.1 路径解析

```powershell
$sourcePath = Resolve-Path $SourceFile
$baseName = [System.IO.Path]::GetFileNameWithoutExtension($SourceFile)
$tempDir = "E:\8_Buffer\C_Compile\TDM-GCC\Temp"
$exePath = Join-Path $tempDir "$baseName.exe"
```

### 设计要点 **：**

* Resolve-Path 确保绝对路径

* Join-Path 安全连接路径

* 避免路径拼接错误

<br>

## 6.2 临时目录管理

```powershell
# 使用固定的英文路径避免中文问题
$tempDir = "E:\8_Buffer\C_Compile\TDM-GCC\Temp"
```

### 设计要点 **：**

* 固定英文路径，避免编码问题

* 独立于源文件目录

* 便于统一管理

<br>

## 7. 进程执行与控制

### 7.1 程序执行

```powershell
$process = Start-Process -FilePath $exePath -NoNewWindow -Wait -PassThru
```

### 参数说明：

* `-FilePath`：要执行的程序路径

* `-NoNewWindow`：在当前窗口执行

* `-Wait`：等待程序结束

* `-PassThru`：返回进程对象，便于获取退出码

### 7.2 退出码处理

```powershell
if ($process) {
    Write-Host "  - Program exit code: $($process.ExitCode)" -ForegroundColor Cyan
}
```

### 设计要点 **：**

* 显示程序退出码，便于调试

* 检查 `$process` 是否成功创建

<br>

## 8. 资源清理策略

### 8.1 延迟清理

```powershell
# 等待程序完全退出
Start-Sleep -Milliseconds 300

# 再次检查进程
$running = Get-Process -Name $procName -ErrorAction SilentlyContinue
if ($running) {
    $running | Stop-Process -Force -ErrorAction SilentlyContinue
    Start-Sleep -Milliseconds 300
}
```

### 设计要点 **：**

* 延迟等待确保资源释放

* 多次检查提高清理成功率

* 避免文件锁定问题

### 8.2 条件清理

```powershell
if ($exeDeleted -and (Test-Path $tempDir)) {
    $items = Get-ChildItem $tempDir -Force -ErrorAction SilentlyContinue
    if ($items.Count -eq 0) {
        Remove-Item $tempDir -Force -ErrorAction SilentlyContinue
    }
}
```

### 设计要点 **：**

* 只在文件已删除且目录为空时删除目录

* 避免误删其他文件

* 条件检查确保安全

<br>

## 9. 健壮性设计

### 9.1 边界条件处理

```powershell
if (-not (Test-Path $SourceFile)) {
    Write-Host "错误: 文件不存在: $SourceFile" -ForegroundColor Red
    exit 1
}
```

### 设计要点 **：**

* 检查输入文件是否存在

* 早期失败，避免后续错误

<br>

## 9.2 默认值处理

```powershell
switch ($fileExtension) {
    # ... 各种扩展名处理
    default {
        Write-Host "ERROR: Unsupported file type: $fileExtension" -ForegroundColor Red
        exit 1
    }
}
```

### 设计要点 **：**

* 处理未知文件类型

* 明确的错误信息

* 优雅退出

<br>

## 10. 性能优化

### 10.1 减少不必要的操作

```powershell
if (Test-Path $tempDir) {
    # 只有当目录存在时才执行清理
    # ...
}
```

### 设计要点 **：**

* 条件执行，避免不必要操作

* 提高脚本执行效率

<br>

## 10.2 并行处理考虑

```powershell
# 可以使用后台作业实现并行处理（当前版本未使用）
# Start-Job -ScriptBlock { # 清理操作 } -Name "CleanupJob"
```

### 扩展性：

* 预留了并行处理的可能性

* 可以扩展为多线程清理

<br>

## 11. 可维护性设计

### 11.1 模块化结构

```powershell
# 脚本按照功能模块组织
# 1. 初始化和参数解析
# 2. 语言检测
# 3. 清理准备
# 4. 编译执行
# 5. 后期处理
```

### 设计要点 **：**

* 清晰的代码结构

* 便于修改和维护

* 功能模块独立

<br>

## 11.2 可配置参数

```powershell
# 关键参数集中在脚本开头
$tempDir = "E:\8_Buffer\C_Compile\TDM-GCC\Temp"
$compilerPath = "C:\TDM-GCC-64\bin"
```

### 设计要点 **：**

* 参数集中管理

* 便于配置修改

* 减少代码重复

<br>

## 12. 安全考虑

### 12.1 路径验证

```powershell
$sourcePath = Resolve-Path $SourceFile
```

### 设计要点 **：**

* 验证路径合法性

* 防止路径遍历攻击

### 12.2 权限检查

```powershell
try {
    New-Item -ItemType Directory -Path $tempDir -Force | Out-Null
}
catch {
    Write-Host "  - ERROR: Cannot create temp folder" -ForegroundColor Red
    exit 1
}
```

### 设计要点 **：**

* 检查文件系统权限

* 明确的权限错误提示

* 优雅处理权限不足

<br>

## 13. 扩展性设计

### 13.1 添加新语言支持

```powershell
# 添加新的文件扩展名支持只需要在 switch 中添加分支
".asm" {
    $compiler = "C:\NASM\nasm.exe"
    $standard = ""
    $language = "Assembly"
    $compilerName = "NASM"
}
```

### 扩展方法 **：**

* 修改 `switch` 语句

* 添加相应的编译器配置

* 保持现有结构不变

### 13.2 添加编译选项

```powershell
# 可以扩展为接收额外的编译参数
param(
    [string]$SourceFile,
    [string[]]$AdditionalArgs = @()
)

# 在编译参数中合并
$compileArgs = @(
    # 基本参数...
) + $AdditionalArgs + @(
    # 源文件和输出参数...
)
```

### 扩展方法：

* 扩展参数列表

* 合并额外的编译参数

* 保持向后兼容

<br>

## 14. 调试支持

### 14.1 详细输出

```powershell
Write-Host "  - Command: $compiler $compileArgs" -ForegroundColor DarkGray
```

### 设计要点 **：**

* 显示实际执行的命令

* 便于调试和验证

<br>

## 14.2 状态检查

```powershell
if ($LASTEXITCODE -ne 0) {
    Write-Host "  - ERROR: Compilation failed!" -ForegroundColor Red
    exit 1
}
```

### 设计要点 **：**

* 检查每个步骤的结果

* 早期发现和报告问题

<br>

## 15. 用户交互设计

### 15.1 键盘输入处理

```powershell
$null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')
```

### 设计要点 **：**

* 等待用户按键

* 不显示按键字符（隐私保护）

* 包含所有按键事件

### 15.2 窗口标题设置

```powershell
$Host.UI.RawUI.WindowTitle = "=== TDM-GCC C/C++ Compiler ==="
```

### 设计要点 **：**

* 设置窗口标题，便于识别

* 提供上下文信息

* 提升用户体验

<br>

## 总结

Auto_Clean.ps1 脚本是一个功能完善、健壮可靠的编译工具脚本，具有以下特点：

1. 模块化设计：代码结构清晰，便于维护

1. 健壮性：多层错误处理，确保脚本稳定运行

1. 用户友好：彩色输出、进度指示、详细错误信息

1. 可扩展：易于添加新功能和新语言支持

1. 安全可靠：路径验证、权限检查、安全清理

1. 性能优化：条件执行、延迟等待、减少不必要操作

<br>

---

*文档版本：1.0*\
*最后更新：2026.01.25*\
*适用对象：powershell*\
*注意事项：本文档中的代码示例需要根据实际情况调整*