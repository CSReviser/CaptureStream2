## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【AppleSilicon版ffmpegインストール手順】　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

**AppleSilicon(Mシリーズ)用のffmpegをインストールする手順です。**

### １．[こちらのサイト](http://www.osxexperts.net/)からffmpeg(AppleSilicon)のzipファイルをダウンロードしてffmpegを取り出します。
* **[OSXExperts.NET](http://www.osxexperts.net/)**



### ２．**端末（ターミナル）から以下のコマンドを実行します。**     

```
    cd [ffmpegを展開したフォルダを指定します] 
    xattr -dr com.apple.quarantine ffmpeg 
    xattr -cr ffmpeg
    codesign -s - ffmpeg
    sudo mv ffmpeg /usr/local/bin/ffmpeg
```
* **「/usr/local/bin/」がffmpegの存先フォルダになります。**
* **カスタマイズ　＞　ffmpegパス設定　＞　設定する　で「/usr/local/bin/」を設定します。テスト版を使う場合はこの設定は必要ありません。 [テスト版ダウンロードはこちら](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-MacOS-20241007-1.dmg)**
* **ffmpegパス設定　で設定しない（初期値）の場合は　　カスタマイズ　＞　保存フォルダ設定　で設定したフォルダにffmpegを保存します。テスト版を使う場合は初期値で「/usr/local/bin」のffmpegが使われます。 [テスト版ダウンロードはこちら](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-MacOS-20241007-1.dmg)**

**公式の手順はmacOSのバージョンによって操作方法が異なるので、下記リンクでご使用のバージョンを選択して操作方法を確認して下さい。**  

**[開発元が不明なMacアプリを開く(Apple Macユーザガイド)](https://support.apple.com/ja-jp/guide/mac-help/mh40616/mac)**


**【参考サイト】**
* **[Apple M1でffmpegを入れる](https://zenn.dev/esaka/scraps/bb29de3b30fc13)**
* **[FFmpegのARM（AppleSilicon）版の6（バイナリ）が配布開始されています。](https://bobsmac.com/news/4572.html)**
* **[ffmpeg on apple silicon(windows cudaも) ](https://note.com/jydie5/n/na047e08003a1)**
* **[ARM版CPUのM1 MACにてffmpegのh265ソフトウェアエンコードを高速化する方法](https://qiita.com/username37/items/7adfe9fd22d9fd8b265b)**


####   　
####   　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
-
