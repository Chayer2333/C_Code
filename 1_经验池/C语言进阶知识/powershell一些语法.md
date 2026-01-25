# *Auto_Clean.ps1 PowerShell* 脚本语法详解
*这个文档详细介绍了脚本中使用到的 PowerShell 语法和特性，可以作为学习和参考的指南。*

<br>

## 1. 脚本参数定义

### param 块

```powershell
param(
    [string]$SourceFile
)
```

* `param`：定义脚本参数，允许从命令行传递参数到脚本

* `[string]`：类型约束，确保 $SourceFile 是字符串类型

* `$SourceFile`：参数变量，存储要编译的源文件路径

<br>

## 2. 变量与数据类型

### 变量定义

```powershell
$compiler = "C:\TDM-GCC-64\bin\gcc.exe"
$standard = "c17"
$language = "C"
```

* `$`：变量标识符，所有变量以 $ 开头

* 变量类型：*PowerShell* 是动态类型语言，但可以显式指定类型

### 常用数据类型

```powershell
[string]    # 字符串
[int]       # 整数
[bool]      # 布尔值
[array]     # 数组
[hashtable] # 哈希表
[System.IO.Path] # 路径处理类
```

<br>

## 3. 控制流语句

### 条件语句 ( *if-else* )

```powershell
if (Test-Path $tempDir) {
    # 路径存在时执行
} else {
    # 路径不存在时执行
}
```

* `Test-Path`：检查路径是否存在

* 花括号 `{}`：代码块界定符

### *switch* 语句

```powershell
switch ($fileExtension) {
    ".c"   { # 处理C文件 }
    ".cpp" { # 处理C++文件 }
    default { # 默认处理 }
}
```

* `switch`：多分支选择

* `$fileExtension`：匹配变量

* `default`：默认分支

### 循环语句

```powershell
foreach ($exeFile in $exeFiles) {
    # 处理每个exe文件
}

while ($attempts -lt $maxAttempts) {
    # 条件循环
    $attempts++
}
```

<br>

## 4. 函数和命令调用

### 调用外部程序

```powershell
& $gcc $compileArgs
```

* `&`：调用操作符，执行命令或可执行文件
* `$compileArgs`：参数数组

### 管道操作

```powershell
Get-Process -Name $procName | Stop-Process -Force
```

* |：管道操作符，将前一个命令的输出作为后一个命令的输入

<br>

## 5. 错误处理

### try-catch 块

```powershell
try {
    # 可能出错的代码
    Remove-Item $tempDir -Recurse -Force -ErrorAction Stop
} catch {
    # 错误处理代码
    Write-Host "错误: $_" -ForegroundColor Red
}
```

* `-ErrorAction Stop`：遇到错误时抛出异常

* `$_`：错误对象变量

### 错误静默

```powershell
Remove-Item $exePath -Force -ErrorAction SilentlyContinue
```

* `-ErrorAction SilentlyContinue`：静默忽略错误

<br>

## 6. 数组和哈希表

### 数组定义

```powershell
$compileArgs = @(
    "-fdiagnostics-color=always",
    "-std=c17",
    "-g"
)
```

* `@()`：数组构造器

* 逗号分隔：数组元素

### 哈希表定义

```powershell
$config = {
    "compiler" = "gcc.exe"
    "standard" = "c17"
    "language" = "C"
}
```

<br>

## 7. 字符串操作

### 字符串插值

```powershell
Write-Host "编译命令: $gcc $compileArgs"
```

* `$variable`：变量插值

* `$()`：表达式插值

### 连接字符串

```powershell
$exePath = Join-Path $tempDir "$baseName.exe"
```

* `Join-Path`：路径连接函数

### 字符串乘法

```powershell
$divider = "-" * 100
```

* `*` ：字符串重复操作符

<br>

## 8. 路径和文件操作

### 路径处理

```powershell
$baseName = [System.IO.Path]::GetFileNameWithoutExtension($SourceFile)
$fileExtension = [System.IO.Path]::GetExtension($SourceFile).ToLower()
```

* 静态方法调用：使用 [类名]::方法名() 语法

### 文件系统命令

```powershell
Test-Path        # 检查路径是否存在
Resolve-Path     # 解析路径为绝对路径
Split-Path       # 分割路径
Get-ChildItem    # 获取目录内容
Remove-Item      # 删除文件或目录
New-Item         # 创建新项目

# 常用参数：
-Recurse     # 递归操作
-Force       # 强制操作
-Path        # 指定路径
-Filter      # 过滤器
```

<br>

## 9. 进程管理

### 进程操作命令

```powershell
Get-Process      # 获取进程信息
Stop-Process     # 停止进程
Start-Process    # 启动进程

# 常用参数：
-Name        # 按进程名筛选
-NoNewWindow # 不创建新窗口
-Wait        # 等待进程结束
-PassThru    # 返回进程对象
```

<br>

## 10. 控制台输出

### *Write-Host* 命令

```powershell
Write-Host "消息" -ForegroundColor Red -BackgroundColor White
```

* `-ForegroundColor`：前景色（文本颜色）

* `-BackgroundColor`：背景色

### 颜色常量

| | | | |
| :---: | :---: | :---: | :---: |
| Black | DarkBlue | DarkGreen | DarkCyan |
| DarkRed | DarkMagenta | DarkYellow | Gray |
| DarkGray | Blue | Green | Cyan |
| Red | Magenta | Yellow | White |
| | | | |

<br>

## 11. 特殊变量

### 预定义变量

```powershell
$_              # 当前管道对象
$PSHOME         # PowerShell 安装目录
$PWD            # 当前工作目录
$LASTEXITCODE   # 上一个外部程序的退出代码
$null           # 空值
$true, $false   # 布尔值
```

<br>

## 12. 操作符

### 比较操作符

```powershell
-eq    # 等于
-ne    # 不等于
-gt    # 大于
-lt    # 小于
-ge    # 大于等于
-le    # 小于等于
-like  # 通配符匹配
-match # 正则表达式匹配
```

### 逻辑操作符

```powershell
-and   # 与
-or    # 或
-not   # 非
!      # 非（简写）
```

<br>

## 13. 脚本执行控制

### 退出脚本

```powershell
exit 0     # 正常退出（成功）
exit 1     # 错误退出（失败）
```

### 暂停等待

```powershell
Start-Sleep -Seconds 1        # 等待1秒
Start-Sleep -Milliseconds 500 # 等待500毫秒
```

### 等待用户输入

```powershell
$null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')
```

* `NoEcho`：不显示按键

* `IncludeKeyDown`：包含按键按下事件

<br>

## 14. 数组操作

### 数组方法

```powershell
$array.Count          # 获取数组元素数量
$array += "新元素"    # 添加元素
$array -join ","      # 用逗号连接数组元素
$array | Sort-Object  # 排序数组
```

<br>

## 15. 字符串方法
常用字符串方法
```powershell
$string.ToLower()      # 转换为小写
$string.ToUpper()      # 转换为大写
$string.Contains()     # 检查是否包含子串
$string.Replace()      # 替换子串
$string.Split()        # 分割字符串
$string.Substring()    # 截取子串
$string.Trim()         # 去除两端空白
```

<br>

## 16. 日期和时间

### 获取当前时间

```powershell
Get-Date                      # 当前日期时间
Get-Date -Format "yyyyMMdd"   # 格式化日期
(Get-Date).ToString("HH:mm:ss") # 格式化时间
```

<br>

## 17. 环境变量

### 访问环境变量
```powershell
$env:COMPUTERNAME      # 计算机名
$env:USERNAME          # 用户名
$env:TEMP              # 临时目录
$env:PATH              # 系统路径
```

<br>

## 18. 注释语法

```powershell
# 单行注释

<#
  多行注释
  可以跨越多行
#>

function Get-Data {
    <#
    .SYNOPSIS
    函数的简要说明
    
    .DESCRIPTION
    函数的详细说明
    
    .PARAMETER Name
    参数说明
    #>
    param($Name)
    # 函数体
}
```

<br>

## 19. 函数定义

### 简单函数

```powershell
function Get-FileInfo {
    param($FilePath)
    Get-Item $FilePath | Select-Object Name, Length, LastWriteTime
}

# 调用函数
Get-FileInfo -FilePath "C:\test.txt"
```

<br>

## 20. 模块和点源

### 导入模块

```powershell
Import-Module ModuleName
```

### 点源执行脚本

```powershell
. .\Script.ps1  # 在当前作用域执行脚本
```

<br>

## 21. 作用域

### 作用域修饰符

```powershell
$local:variable   # 本地作用域（默认）
$global:variable  # 全局作用域
$script:variable  # 脚本作用域
$private:variable # 私有作用域
```

<br>

## 22. 高级特性
### 属性访问

```powershell
$process.ExitCode          # 访问对象属性
$process | Get-Member      # 查看对象成员
```

### 方法调用
```powershell
$process.Kill()            # 调用对象方法
[System.IO.Path]::Combine("path1", "path2") # 静态方法
```

### 类型转换

```powershell
[int]"123"                 # 字符串转整数
[string]123                # 整数转字符串
[System.Text.Encoding]::UTF8 # 获取编码对象
```

<br>

---

*文档版本：1.0*\
*最后更新：2026.01.25*\
*适用对象：powershell*\
*注意事项：本文档中的代码示例需要根据实际情况调整*
