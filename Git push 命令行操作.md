# ***push 使用说明***

## *powershell & Git bash*
*用于Git命令行 push 的指令*

    git add .

    git commit -m " 提交说明 "

    git push origin main

* *origin main 是仓库名*

## *如果链接报错*
*使用 powershell 运行命令测试链接*

#### 1. 测试是否能解析GitHub域名
    nslookup github.com

#### 2. 测试是否能连接到GitHub的SSH端口（22端口）
    Test-NetConnection github.com -Port 22

#### 3. 测试是否能连接到GitHub的HTTPS端口（443端口）
    Test-NetConnection github.com -Port 443

* *主要是443端口* 

    $22：ssh \ ,\  443:https$

## *解决方案*

### 临时为所有 ***Git*** 操作禁用 ***SSL*** 验证
*此操作会降低安全性，使你的 Git 连接容易受到中间人攻击*

    git config --global http.sslVerify false

* 再次尝试 git fetch 或 git pull

**< *warning!* 必须重启 http.sslVerify ! >**

    git config --global http.sslVerify true