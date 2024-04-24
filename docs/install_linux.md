## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【Ubuntu版インストール(ビルド)手順】　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

**UbuntuはOSの環境に合わせたバイナリでないと動作しない可能性があるようで、このサイトで提供している実行ファイル（バイナリ）が動作しないことがあるようです。ここでは環境に合うように、ご自身でビルドして頂く手順の例を示します。ビルドする際に参考にしてお試しください。**
**端末から以下の手順でコマンドを実行します。**

### ０．wgetとffmpegのインストール(初回のみ)     
>
>　**sudo apt install wget ffmpeg**
>


### １．ワークフォルダの作成
>
>　　　　　　        
>　**mkdir work**          
>　**cd work**
>
>　　　　　　　

### ２．ソースファイルの入手と展開
>
>　　　　　　　         
>　**wget --no-check-certificate https://github.com/CSReviser/CaptureStream2/archive/master.tar.gz**          
>　**tar xpvf master.tar.gz**          
>　**rm master.tar.gz**          
>　**cd CaptureStream2-master**
>
>　　　　　　　


### ３．ビルドする
####    3-1. qmakeの場合。
>
>　　　　　　　         
>　**qmake6 && make**          
>
>　　　　　　　
####    3-2. cmakeの場合。
>
>　　　　　　　         
>　**qt-cmake && make**          
>
>　　　　　　　
 　　
 
### ４．必要ファイルをコピーする
>
>　　　　　　　         
>　**mkdir ~/LinCaptureStream2**         
>　**cp ./CaptureStream2 ~/LinCaptureStream2/**          
>　**cp /usr/bin/ffmpeg ~/LinCaptureStream2/**          
>　**cp ./qss_files/stylesheet-ubu.qss ~/LinCaptureStream2/**
>
>　　　　　　　

### ５．ビルドしたファイルを実行する
>
>　　　　　　　         
>　**cd ~/LinCaptureStream2**         
>　**./CaptureStream2**          
>
>　　　　　　　

**※ffmpegは実行するCaptureStream2と同じフォルダに置く必要があります。**

####   　
####   　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
-
