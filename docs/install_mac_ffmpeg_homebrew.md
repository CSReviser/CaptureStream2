## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## Homebrew版ffmpegインストール手順　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

**Homebrewを使ったmacOS用のffmpegをインストールする手順です。**



-----------
🚀 Homebrew を使った macOS 用 ffmpeg のインストール手順

**語学講座 CS2 の動作には ffmpeg が必要です。以下の手順でインストールしてください。**

-----------
### 1️⃣ Homebrew をインストール（未導入の場合）

**Homebrew がインストールされていない場合は、次のコマンドを実行してください。**
```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
-----------

**✅ Apple Silicon (M1/M2) の場合**

**Apple Silicon (M1/M2) の Mac では、Homebrew のインストール先が /opt/homebrew になります。正しく動作するように、以下を実行してください。**
```sh
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
eval "$(/opt/homebrew/bin/brew shellenv)"
```
**✅ Intel Mac の場合**

**Intel Mac の場合、Homebrew は /usr/local にインストールされます。以下を実行してください。**
```sh
echo 'eval "$(/usr/local/bin/brew shellenv)"' >> ~/.zshrc
eval "$(/usr/local/bin/brew shellenv)"
```
-----------

### 2️⃣ ffmpeg のインストール

**以下のコマンドで ffmpeg をインストールしてください。**
```sh
brew install ffmpeg
```

**⚠️ CPU による ffmpeg のインストール先の違い**

| Mac の種類         | Homebrew のインストール先 | ffmpeg のインストール先       |
|------------------|------------------|--------------------------|
| **Apple Silicon (M1/M2)** | `/opt/homebrew` | `/opt/homebrew/bin/ffmpeg` |
| **Intel Mac**    | `/usr/local`     | `/usr/local/bin/ffmpeg`     |

-----------

### 3️⃣ インストール確認

**以下のコマンドで ffmpeg が正しくインストールされているか確認できます。**
```sh
ffmpeg -version
```

**Apple Silicon の場合、/opt/homebrew/bin にパスが通っていないと ffmpeg が見つからないことがあります。以下のコマンドでパスを確認してください。**
```sh
which ffmpeg
```

**/opt/homebrew/bin/ffmpeg または /usr/local/bin/ffmpeg が表示されれば、正しくインストールされています。**

-----------
## 🛠 トラブルシューティング

**Q. ffmpeg が見つからない場合は？**
**以下のコマンドを試してください。**
```sh
export PATH="/opt/homebrew/bin:$PATH"   # Apple Silicon の場合
export PATH="/usr/local/bin:$PATH"      # Intel Mac の場合
```
**または、永続的に設定する場合は ~/.zshrc または ~/.zprofile に追加してください。**
```sh
echo 'export PATH="/opt/homebrew/bin:$PATH"' >> ~/.zprofile   # Apple Silicon の場合
echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.zshrc         # Intel Mac の場合
```
-----------

**これで ffmpeg のインストールは完了です！🎉**

## 🚀 インストール方法

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



####   　
####   　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
-