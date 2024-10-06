## [語学講座CS2](https://csreviser.github.io/CaptureStream2/)  
## 【MacOSユーザの方へ】     
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
**語学講座ＣＳ２の改版者はMac関連の知識を持っていず、実機環境も所有していませんが、Macユーザの有志の方からの動作報告などの情報提供を頂いて、GitHubで作成したmacOS向け実行ファイルを提供してきました。しかし、昨今のmacOSのセキュリティ強化等によりApple App Store以外のインターネット経由で入手したアプリのインストールが警告、阻止されるようになっているようです。そのような状況で動作確認を行うMac実機を持たずにビルドした実行ファイルをトップページに掲載することは不適切と判断し、掲載を見合わせています。**

**情報提供や動作確認にご協力いただいたMacユーザの有志の皆様に感謝します。**

**尚、[［類似アプリ］](https://csreviser.github.io/CaptureStream2/application)のページにMacで動作するアプリを紹介しています。**

**また以下の内容は古いですが、情報として残しておきます。**
**プログラムのソースファイルはgithubで公開しています。ご利用の環境で実行ファイルをビルドする事により、セキュリティ警告無しに実行可能と思います。githubのmacos-latestでビルド出来ることは確認しています。**



---
#### 語学講座ＣＳ２の改版者はMac関連の知識を持っていず、実機環境も所有していません。そのため、MacOS版はリリース前の動作が確認できていません。Macユーザの有志の方からの動作報告などの情報提供を頂いて、可能な範囲で対応しております。新規のMacユーザの方はMacで動作確認された他のアプリの採用をお勧めします。[［類似アプリ］](https://csreviser.github.io/CaptureStream2/application)のページにMacで動作するアプリを紹介しています。
#### ＜ユーザ間の互助のお願い＞
#### MacOSユーザ間の互助にご協力をお願いします。

#### ＜MacOS版の仕様相違点＞
#### 語学講座CS2 は、ＯＳの違いに関係なく同一仕様となるようにしていますが、一部ＯＳに依存して仕様を変えています。MacOS版固有の仕様を記載しておきます。
#### １．初回起動時に録音音声ファイルの保存先フォルダを必ずユーザが指定する仕様になっています。
#### ２．設定ファイル(iniファイル)、Style Sheet(qssファイル)、ffmpegの保存先ファルダが異なります。
* #### 設定ファイル(iniファイル)： "~/Library/Preferences"
* #### Style Sheet(qssファイル)： 「stylesheet-mac.qss」を録音音声ファイル保存先フォルダに置くと、そちらが優先して使われます。（削除するとデフォルトに戻ります）
* #### ffmpeg： 「ffmpeg」を録音音声ファイル保存先フォルダに置くと、そちらが優先して使われます。（削除するとデフォルトに戻ります）
   * **[Macintosh 64bit版バイナリ](https://evermeet.cx/ffmpeg/)**
   * **[MacOS Apple Silicon版バイナリ](https://www.osxexperts.net/)**
#### 　　


#### ＜MacOS版実行ファイル作成環境＞
#### githubのactionsという機能を利用してMacOS用の実行ファイルを作成しています。
   * **macos-14**
   * **Qt： 6.5LTS**
   * **Universal(Intel/M1両対応)**



#### 　　
#### 　　
#### 語学講座CS2 は、Qtというクロスプラットフォーム環境で開発しています。クロスプラットフォームは同一のソースファイルから異なるＯＳ（Windows/Linux/MacOS等）向けの実行ファイルを作れることが期待されます。
#### QtバージョンとmacOS対応
#### [Qt5.15LTS ：](https://doc.qt.io/qt-5/macos.html) macOS 10.13 / 10.14 / 10.15 / 11 / 12 / 13 / 14
#### [Qt6.2LTS ：](https://doc.qt.io/qt-6.2/macos.html) macOS 10.14 / 10.15 / 11 / 12 / 13 / 14
#### [Qt6.5LTS ：](https://doc.qt.io/qt-6.5/macos.html) macOS 11 / 12 / 13 / 14
#### [Qt6.7 ：](https://doc.qt.io/qt-6.7/macos.html) macOS 11 / 12 / 13 / 14
#### 　　
#### 　　 
**Macユーザーからの報告例（参考）**            
  - **macOS Monterey 12.7.4 M1機**           
  - **macOS Sonoma 14.4.1 Intel機**
  - **macOS Sonoma 14.3.1 M1機**


#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
