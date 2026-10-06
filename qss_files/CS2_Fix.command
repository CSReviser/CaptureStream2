#!/bin/bash

echo "========================================"
echo "CaptureStream2.app の隔離属性解除 & コード署名"
echo "========================================"

# 隔離属性の解除
echo "1. 隔離属性を解除しています..."
xattr -cr com.apple.quarantine /Applications/CaptureStream2.app

# コード署名
echo "2. コード署名を適用しています..."
codesign --force --deep --sign - /Applications/CaptureStream2.app

echo ""
echo "✅ 処理が完了しました！"
echo "CaptureStream2.app を起動してみてください。"

# 終了を待つ（ウィンドウがすぐ閉じないように）
read -p "Enterキーを押して終了します..."