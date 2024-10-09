## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【AppleSilicon版ffmpegインストール手順】　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

**AppleSilicon(Mシリーズ)用のffmpegをインストールする手順です。**

### １．[こちらのサイト](http://www.osxexperts.net/)からffmpeg(AppleSilicon)をインストール(初回のみ)   
* **[OSXExperts.NET](http://www.osxexperts.net/)**



### ２．**端末（ターミナル）から以下のコマンドを実行します。**     

```
    xattr -dr com.apple.quarantine ffmpeg 
    xattr -cr ffmpeg
    codesign -s - ffmpeg
    sudo mv ffmpeg /usr/local/bin/ffmpeg
```
* **「[/usr/local/bin/」がffmpegのご存先フォルダになります。**


**【参考サイト】**
* **[Apple M1でffmpegを入れる](https://zenn.dev/esaka/scraps/bb29de3b30fc13)**
* **[FFmpegのARM（AppleSilicon）版の6（バイナリ）が配布開始されています。](https://bobsmac.com/news/4572.html)**
* **[ffmpeg on apple silicon(windows cudaも) ](https://note.com/jydie5/n/na047e08003a1)**



####   　
####   　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
-
