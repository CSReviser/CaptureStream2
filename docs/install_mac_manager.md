# CaptureStream2 Manager（CLI版）

`capturestream2-manager.sh` は、macOS 上で CaptureStream2 の Homebrew Cask を手軽に管理できるコマンドライン用スクリプトです。

---

## 特徴

- CaptureStream2 の最新版インストール、アップデート、アンインストールに対応
- 指定バージョン（ロールバック）インストール・アンインストール
- 利用可能なバージョン一覧の取得
- Homebrew Tap 経由で管理可能

---

## 前提条件

- macOS
- Homebrew がインストールされていること  
  → インストール方法: Homebrew をまだインストールしていない場合は、[公式サイト](https://brew.sh/) を参考に、以下のコマンドをターミナルで実行してください：

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
---

## インストール手順

### 1. Homebrew Tap の追加

```bash
brew tap CSReviser/capturestream2
```

### 2. スクリプトのダウンロード
```bash
curl -O https://raw.githubusercontent.com/CSReviser/homebrew-capturestream2/main/capturestream2-manager.sh
chmod +x capturestream2-manager.sh
```

---

使い方

スクリプトを実行すると、CLI形式のメニューが表示されます：
```bash
./capturestream2-manager.sh
```

## メニュー一覧

| 番号 | 処理内容                                                   |
|------|------------------------------------------------------------|
| 1    | 最新版のインストール                                       |
| 2    | 最新版のアンインストール                                   |
| 3    | 最新版の更新（アップデート）                               |
| 4    | 最新版のアップグレード（再インストール）                   |
| 5    | インストール済みキャスクの一覧表示                         |
| 6    | 指定バージョン（ロールバック）のインストール               |
| 7    | 指定バージョン（ロールバック）のアンインストール           |
| 8    | 最新版に戻す（ロールバック解除）                           |
| 9    | 利用可能なバージョン一覧表示                               |
| 10   | 終了                                                       |

---

バージョンの指定方法（ロールバック）

指定バージョンをインストール・アンインストールする場合、バージョン番号（例: 20250324）の入力が求められます。利用可能なバージョンは Tap の中で以下のように表示されます：
```bash
brew search capturestream2
```


---

トラブルシューティング
	•	Homebrew が見つからない場合：
brew: command not found エラーが出たら、brew.sh を参考に Homebrew をインストールしてください。
	•	インストールできない場合：
brew install --cask の出力を確認してください。Tap のバージョンや記述ミスの可能性があります。

---

ライセンス

このスクリプトはオープンソースで公開されています。

