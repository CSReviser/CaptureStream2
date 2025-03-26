## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## Homebrew版ffmpegインストール手順　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

**Homebrewを使ったmacOS用のffmpegをインストールする手順です。**


## 🚀 インストール方法

### 1. Homebrew をインストール（未導入の場合）

**Homebrew がインストールされていない場合は、次のコマンドを実行してください。**

```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
**Apple Silicon (M1/M2) の場合

Apple Silicon の Mac では、Homebrew のインストール先が異なります。以下のコマンドでパスを確認してください。**
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