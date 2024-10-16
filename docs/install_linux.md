## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【Ubuntu版インストール(ビルド)手順】　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

**このサイトで提供しているUbuntu版の実行ファイル（バイナリ）は、ＯＳ環境によって動作しないことがあるようです。ここでは環境に合うように、ご自身でビルドして頂く手順の例を示します。ビルドする際に参考にしてお試しください。[【Ubuntu版 qt6インストール手順】](./qt_install)も参考にしてください。**
**端末から以下の手順でコマンドを実行します。**

### ０．wgetとffmpegのインストール(初回のみ)     

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
