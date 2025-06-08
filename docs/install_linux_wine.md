## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【Ubuntu版インストール(WINE)手順】　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

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
    sudo apt install wget ffmpeg
```
### ０-1．Qtのビルド環境インストール(初回のみ)     

```
    sudo apt-get install build-essential libgl1-mesa-dev
```

### １．ワークフォルダの作成

```
    mkdir work
    cd work
```

　　　　　　　

### ２．ソースファイルの入手と展開

```
    wget --no-check-certificate https://github.com/CSReviser/CaptureStream2/archive/master.tar.gz
    tar xpvf master.tar.gz
    rm master.tar.gz
    cd CaptureStream2-master
```
      



### ３．ビルドする
* **3-1. qmakeの場合**
```
    qmake6 && make          
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
