## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【非公式ＱＴ(aqt)インストール＆ビルド手順】　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

**Another Qt installer(aqt)、非公式ＱＴインストール(aqt)手順です。このサイトで提供しているUbuntu版の実行ファイル（バイナリ）は、ＯＳ環境によって動作しないことがあるようです。ここでは環境に合うように、ご自身でビルドして頂く手順の例を示します。ビルドする際に参考にしてお試しください。[【Ubuntu版 qt6インストール手順】](./qt_install)も参考にしてください。**

**[aqtinstall manual](https://aqtinstall.readthedocs.io/ja/stable/index.html)**

**[Another Qt installer(aqt) - GitHub](https://github.com/miurahr/aqtinstall)**

* **Python(version: 3.8.1以上)がインストールされている必要があります。**


**端末から以下の手順でコマンドを実行します。**

### １．pipコマンドによるインストール     

```
    python3 -m pip install aqtinstall (--break-system-packages)
```
* **「python3 -m」は環境によって入力不要な場合があります。**
* **「--break-system-packages」はpython3 のバージョンによって必要となる場合があります。**

### 2．Qtをインストールする     

```
    mkdir ~/qt
    python3 -m aqt install-qt --outputdir ~/qt linux desktop 6.5.3 gcc_64 -m qtcharts
```
* **「python3 -m」は環境によって入力不要な場合があります。**
* **「~/qt」はQTのインストール先フォルダを指定します。**
* **「linux」はUbuntuも他、Linux系OSでの指定です。OSによって「windows」「mac」を指定します。**
* **「desktop」は変更しないでください。語学講座CS2では「desktop」以外を想定していません。**
* **「6.5.3」はQTのバージョンです。利用可能なQtのバージョンを調べるには、 aqt list-qt command を使うことができます。**
```
    python3 -m aqt list-qt linux desktop
```
* **「gcc_64」はアーキテクチャで利用可能なアーキテクチャは、 aqt list-qt command に　--arch　オプションを指定して調べることができます。**
```
    python3 -m aqt list-qt linux desktop --arch 6.5.3
```

### ３．語学講座CS2のソースファイルの入手と展開

```
    wget --no-check-certificate https://github.com/CSReviser/CaptureStream2/archive/master.tar.gz
    tar xpvf master.tar.gz
    rm master.tar.gz
    cd CaptureStream2-master
```

### ４．ビルドする
* **４-1. qmakeの場合**
```
    ~/qt/6.5.3/gcc_64/bin/qmake6 && make          
```

* **４-2. qt-cmakeの場合**
```
    ~/qt/6.5.3/gcc_64/bin/qt-cmake . . && make         
```
**※ qt6ではcmakeの利用が推奨されるようになりましたが、qmakeも利用可能です。**



 
### ５．必要ファイルをコピーする
* **インストール先のフォルダを作成して必要ファイルをコピーします。**
```
mkdir ~/LinCaptureStream2
cp ./CaptureStream2 ~/LinCaptureStream2/
cp /usr/bin/ffmpeg ~/LinCaptureStream2/
cp ./qss_files/stylesheet-ubu.qss ~/LinCaptureStream2/
```
**※ インストール先のフォルダは任意に変更してください。特別な書き込み権限が必要ないフォルダにしてください。**

### ６．クリーン

```
    make clean
```
**※ cmakeを使った場合は「CMakeCache.txt」を削除してください。**

### 7．ビルドしたファイルを実行する

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
