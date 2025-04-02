## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## macOS版インストール手順
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
####   　

**Homebrewを使って語学講座CS2をインストールする手順です。**

## 🚀 インストール方法

### 🛠 方法 1: 手動でインストール

### 1. Homebrew をインストール（未導入の場合）

**Homebrew がインストールされていない場合は、次のコマンドを実行してください。**

```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
**Apple Silicon (M1/M2) の場合**

**Apple Silicon の Mac では、Homebrew のインストール先が異なります。以下のコマンドでパスを確認してください。**
```sh
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
eval "$(/opt/homebrew/bin/brew shellenv)"
```

**Intel Mac の場合**
```sh
echo 'eval "$(/usr/local/bin/brew shellenv)"' >> ~/.zshrc
eval "$(/usr/local/bin/brew shellenv)"
```

### 2. ffmpeg のインストール

**語学講座CS2 の動作には ffmpeg が必要です。以下のコマンドでインストールしてください。**

```sh
brew install ffmpeg
```

**インストール後、以下のコマンドで ffmpeg が正しくインストールされているか確認できます。**

```sh
ffmpeg -version
```

### 3. 語学講座CS2 のインストール

**Homebrew Tap を追加し、語学講座CS2 をインストールします。**



```sh
brew tap csreviser/capturestream2
brew install --cask capturestream2
```
**インストール完了後、/Applications/CaptureStream2.app にアプリが追加されます。**

## ⚠️ Gatekeeper の警告を回避する方法

**語学講座CS2 は Apple の公証（Notarization）を受けていないため、初回起動時に Gatekeeper の警告が表示される可能性があります。その場合、以下の手順で回避できます。**

**方法 1: セキュリティ設定から許可**

**1. CaptureStream2.app を開こうとする**

**2.「開発元が未確認のため開けません」という警告が表示される**

**3.「システム設定」 → 「プライバシーとセキュリティ」 に移動**

**4.　CaptureStream2 に対して「このまま開く」を選択**

**方法 2: ターミナルで Gatekeeper を無効化**

**以下のコマンドを実行すると、Gatekeeper の警告を回避できます。**

```sh
xattr -r -d com.apple.quarantine /Applications/CaptureStream2.app
```


## ⚠️ 既に `~/Applications` に手動インストール済みの場合の問題と対処法

### (1) 問題点
**すでに `~/Applications/CaptureStream2.app` に手動インストールしている場合、Homebrew の `brew install --cask capturestream2` を実行すると、インストールが競合し、正しく動作しない可能性があります。**

#### **具体的な問題:**
1. **Homebrew で `/Applications` にインストールされるが、`~/Applications` の手動インストール版が優先される可能性がある**
   - 既存の `~/Applications/CaptureStream2.app` が起動され、Homebrew でインストールした `/Applications/CaptureStream2.app` が使用されない。

2. **Homebrew の `brew upgrade` による更新が適用されない**
   - `~/Applications` の手動インストール版が優先されると、Homebrew の管理対象外となり、更新が適用されない。

---

### (2) 対処方法

#### ✅ **既存の `~/Applications` の CaptureStream2.app を削除する**
以下のコマンドを実行し、`~/Applications` にある手動インストール版を削除してください。

```sh
rm -rf ~/Applications/CaptureStream2.app
```

**その後、再度 Homebrew でインストールしてください。**
```sh
brew install --cask capturestream2
```


#### ✅ ~/Applications ではなく、Homebrew 版を優先的に利用する

**手動インストール版を削除せずに Homebrew 版を優先して使用したい場合、アプリの起動時に明示的に /Applications にあるバージョンを指定することで回避可能です。**
```sh
open /Applications/CaptureStream2.app
```
**または、Finder で /Applications/CaptureStream2.app を直接開く。**

⸻

### (3) まとめ
**推奨: ~/Applications に手動インストールしたことがある場合は、削除してから Homebrew でインストール すると競合を防げます。**

---
### 🛠 方法 2: install.sh を使う（推奨）

**以下のスクリプトを使用すると、Homebrew のセットアップ → CaptureStream2 のインストール → 必要なツール（ffmpeg）のインストール をすべて自動で実行できます。**

**1️⃣ スクリプトをダウンロード**

**ターミナルで以下のコマンドを実行してください。**
```sh
mkdir -p ~/CaptureStream2Installer
cd ~/CaptureStream2Installer
curl -O https://raw.githubusercontent.com/CSReviser/homebrew-capturestream2/main/install.sh
chmod +x install.sh
```

**2️⃣ インストールを実行**

**以下のコマンドを実行すると、CaptureStream2 のインストールが開始されます。**
```sh
　~/CaptureStream2Installer/install.sh
```

---
## 🔹 アップデート手順

### 🛠 方法 1: 手動アップデート

**Homebrew を使って、最新バージョンへアップデートするには、以下のコマンドを実行してください。**
```sh
brew update
brew upgrade ffmpeg
brew upgrade --cask capturestream2
```
**⚠️ 注意:**
**アップデート後、Gatekeeper（macOS のセキュリティ機能）がアプリをブロックする 場合があります。**
**その場合は、以下のコマンドで制限を解除してください。**
```sh
xattr -r -d com.apple.quarantine /Applications/CaptureStream2.app
```
**または、「システム設定」 → 「プライバシーとセキュリティ」 から手動で許可してください。**

### 🚀 方法 2: アップデート用スクリプトを使う（推奨）

**アップデート作業を自動化するスクリプトを用意しました。**
**このスクリプトを使うことで、Homebrew の更新 → アプリのアップデート → Gatekeeper の制限解除 を一括で実行できます。**

**1️⃣ スクリプトをダウンロード**

**以下のコマンドを実行し、スクリプトを取得します。**
```sh
mkdir -p ~/CaptureStream2Updater
cd ~/CaptureStream2Updater
curl -O https://raw.githubusercontent.com/CSReviser/homebrew-capturestream2/main/update_apps.sh
curl -O https://raw.githubusercontent.com/CSReviser/homebrew-capturestream2/main/update_apps.command
chmod +x update_apps.sh update_apps.command
```

**2️⃣ ターミナルで実行**

**以下のコマンドを実行すると、CaptureStream2 のアップデートが開始されます。**
```sh
~/CaptureStream2Updater/update_apps.sh
```

**3️⃣ ダブルクリックで実行**

**update_apps.command を ダブルクリック するだけで、アップデートが自動実行されます。**

---
## 🚀 アンインストール

**語学講座CS2 を削除するには、以下のコマンドを実行してください。**
```sh
brew uninstall --cask capturestream2
```
**また、Homebrew Tap を削除する場合は以下のコマンドを実行します。**

```sh
brew untap csreviser/capturestream2
```


* **[MacOS版について](./macos)** 


####   　
####   　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
-