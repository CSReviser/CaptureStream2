## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【Ubuntu版インストール(WINE)手順】　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]


# Ubuntu に Wine を使って Windows 版 CaptureStream2 を実行する方法

このドキュメントでは、Ubuntu 上で Wine を利用して Windows 版 CaptureStream2 を実行する方法を説明します。  
Ubuntu ネイティブ版で正常に動作しない場合や、Windows 版限定の機能を使用したい場合にご利用ください。

---

## 1. Wine のインストール

### ✅ 推奨手順（WineHQ 公式リポジトリ使用）

以下の手順で、最新の Wine 安定版を WineHQ の公式リポジトリからインストールできます。

```bash
sudo dpkg --add-architecture i386
sudo mkdir -pm755 /etc/apt/keyrings
sudo wget -O /etc/apt/keyrings/winehq-archive.key https://dl.winehq.org/wine-builds/winehq.pub
sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/ubuntu/dists/$(lsb_release -cs)/winehq-$(lsb_release -cs).sources
sudo apt update
sudo apt install --install-recommends winehq-stable

**このサイトで提供しているUbuntu版の実行ファイル（バイナリ）は、ＯＳ環境によって動作しないことがあるようです。ここではUbuntuにWINEをインストールしてWinsdow版を使う手順の例を示します。環境依存が解消しないときは参考にしてお試しください。[【Windows版インストール手順】](./install_win)も参考にしてください。**
**端末から以下の手順でコマンドを実行します。**


## Wine のインストール（推奨手順）

Wine を最新状態で使用するには、WineHQ が提供する公式リポジトリを使用することを推奨します。

```bash
sudo dpkg --add-architecture i386
sudo mkdir -pm755 /etc/apt/keyrings
sudo wget -O /etc/apt/keyrings/winehq-archive.key https://dl.winehq.org/wine-builds/winehq.pub
sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/ubuntu/dists/$(lsb_release -cs)/winehq-$(lsb_release -cs).sources
sudo apt update
sudo apt install --install-recommends winehq-stable

```

## 🔧 簡易手順（Ubuntu標準リポジトリ使用）

簡単に試したい方は以下の簡易手順でもインストールできます。ただし Wine のバージョンが古く、アプリによっては互換性に問題が生じる可能性があります。

sudo dpkg --add-architecture i386
sudo apt update
sudo apt install -y wine64 wine32

```

✅ インストール確認

Wine のバージョンを確認します。


```
wine --version
```

例: wine-9.0 のように表示されれば成功です。


### 2. Wine 初期設定（初回のみ）

Wine を初めて使用する場合は以下を実行して初期設定を行います。

```
winecfg
```

	•	ダイアログが開くまで数分かかることがあります。
	•	「Windows のバージョン」は Windows 10 以上を選択してください。

　　　　　　　

### 3. CaptureStream2 Windows版のダウンロードと展開

ダウンロード

公式サイトから Windows 版（ZIP）をダウンロードしてください：

👉 Windows 版インストール手順

```
    wget --no-check-certificate https://github.com/CSReviser/CaptureStream2/archive/master.tar.gz
    tar xpvf master.tar.gz
    rm master.tar.gz
    cd CaptureStream2-master
```
      



### 6. 日本語フォントの表示対策（任意）

日本語が文字化けする場合、以下で日本語フォントをインストールしてください：
* **3-1. qmakeの場合**
```
sudo apt install -y fonts-noto-cjk
```

     


* **3-2. cmakeの場合**
```
    cmake ./ ./ && make         
```
**※ qt6ではcmakeの利用が推奨されるようになりましたが、qmakeも利用可能です。**
 　　   

* **3-3. qt-cmakeの場合**
```
    /path/qt-cmake . . && make         
```
**※ /path/ は　qt-cmake がインストールされているパスを指定します。**




 
### ４．必要ファイルをコピーする
* **インストール先のフォルダを作成して必要ファイルをコピーします。**
```
mkdir ~/LinCaptureStream2
cp ./CaptureStream2 ~/LinCaptureStream2/
cp /usr/bin/ffmpeg ~/LinCaptureStream2/
cp ./qss_files/stylesheet-ubu.qss ~/LinCaptureStream2/
```
**※ インストール先のフォルダは任意に変更してください。特別な書き込み権限が必要ないフォルダにしてください。**



### ５．ビルドしたファイルを実行する

```
    cd ~/LinCaptureStream2
    ./CaptureStream2
```
**※ ffmpegは実行するCaptureStream2と同じフォルダに置く必要があります。**

####   　
####   　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
-
