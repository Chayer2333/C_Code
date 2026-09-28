#!/bin/bash

# 定义变量
VNC_BIN="/opt/TurboVNC/bin/vncserver"
DISPLAY_NUM=":2"
VNC_PORT="5902"
VNC_GEOMETRY="1600x900"
VNC_DEPTH="24"
VNC_ARGS="-localhost -geometry $VNC_GEOMETRY -depth $VNC_DEPTH -securitytypes none"

echo "=========================================="
echo "      TurboVNC 一键启动脚本"
echo "=========================================="

# 1. 检查并终止现有的 VNC 会话
echo "[1] 检查是否存在 VNC 会话 $DISPLAY_NUM ..."
if $VNC_BIN -list 2>/dev/null | grep -q "$DISPLAY_NUM"; then
    echo "发现已有 VNC 会话 $DISPLAY_NUM，正在停止..."
    $VNC_BIN -kill $DISPLAY_NUM
    if [ $? -eq 0 ]; then
        echo "已停止旧会话。"
    else
        echo "警告：停止旧会话失败，尝试强制清理锁文件..."
        rm -f /tmp/.X${DISPLAY_NUM:1}-lock /tmp/.X11-unix/X${DISPLAY_NUM:1}
    fi
else
    echo "未发现 VNC 会话 $DISPLAY_NUM。"
fi

# 2. 删除可能残留的锁文件（确保干净启动）
rm -f /tmp/.X${DISPLAY_NUM:1}-lock /tmp/.X11-unix/X${DISPLAY_NUM:1}

# 3. 启动 VNC 服务
echo "[2] 正在启动 VNC 服务 $DISPLAY_NUM (无加密模式) ..."
$VNC_BIN $DISPLAY_NUM $VNC_ARGS
if [ $? -ne 0 ]; then
    echo "错误：启动 VNC 服务失败！请检查日志。"
    exit 1
fi

# 4. 等待片刻，让服务完全启动
sleep 2

# 5. 检查端口是否监听
echo "[3] 检查 VNC 端口 $VNC_PORT 是否正常监听..."
if timeout 1 bash -c "echo > /dev/tcp/127.0.0.1/$VNC_PORT" 2>/dev/null; then
    echo "✓ VNC 服务已成功启动并监听端口 $VNC_PORT。"
else
    echo "✗ 警告：端口 $VNC_PORT 未响应，可能启动失败。请检查日志。"
fi

# 6. 获取进程 PID
PID=$(ps aux | grep -E "Xvnc.*$DISPLAY_NUM" | grep -v grep | awk '{print $2}')
if [ -n "$PID" ]; then
    echo "   VNC 进程 PID: $PID"
else
    echo "   无法获取 VNC 进程 PID。"
fi

# 7. 显示日志文件路径
LOG_FILE="/root/.vnc/$(hostname)${DISPLAY_NUM}.log"
if [ -f "$LOG_FILE" ]; then
    echo "   日志文件: $LOG_FILE"
else
    echo "   日志文件未找到（可能位置不同）。"
fi

echo "=========================================="
echo "✓ VNC 服务已就绪！"
echo ""
echo "下一步（在本地 Windows 上执行）："
echo "  ssh -N -L 15901:127.0.0.1:$VNC_PORT -p <用户名>@<服务器IP>"
echo ""
echo "然后使用 VNC 客户端连接："
echo "  localhost:15901"
echo "（密码为之前设置的 VNC 密码，若无密码请先运行 /opt/TurboVNC/bin/vncpasswd 设置）"
echo "=========================================="