$release = Get-ItemPropertyValue `
-LiteralPath 'HKLM:SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Full' `
-Name Release

switch ($release) {
{$_ -ge 533320} { $version = '4.8.1 或更高'; break }
{$_ -ge 528040} { $version = '4.8'; break }
{$_ -ge 461808} { $version = '4.7.2'; break }
default { $version = '未知或低于 4.5'; break }
}
Write-Host ".NET Framework 版本: $version"


# 运行方式：./"Show_NET framework runtime.ps1"