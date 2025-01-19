## [語学講座CS2](https://csreviser.github.io/CaptureStream2/)  
## 【MacOSユーザの方へ】     
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
**語学講座CS2の改版者はMacに関する知識が乏しく、またMac実機環境を所有しておりませんが、Macユーザーの有志の方々からいただいた動作報告や情報提供を基に、GitHubを通じてmacOS向けの実行ファイルを提供してまいりました。**
**しかし、近年のmacOSにおけるセキュリティ強化の影響で、Apple App Store以外からインターネット経由で入手したアプリのインストールが警告されたり、阻止されたりするケースが増えているようです。このような状況を踏まえ、Mac実機を使った動作確認が行えないままビルドした実行ファイルをトップページで公開するのは適切ではないと判断し、現在はその掲載を見合わせております。**


**＜概要＞**
  * **動作確認できていない**
    * **Macの実機がない**
  * **OSに警告、実行阻止される（インストール時）**
    * **デジタル署名がない**
    * **署名無しアプリ実行阻止がAppleの方針**
    * **最新OSで実行阻止強化**
    * **Apple Silicon(Mシリーズ)で実行阻止強化**

**＜対応（利用者側）＞**
  * **OS警告回避策が必要**
  * **Rosetta2のインストールが必要（Apple Silicon Mac）**


**＜Apple Macユーザガイド＞**
* **[開発元が不明なMacアプリを開く](https://support.apple.com/ja-jp/guide/mac-help/mh40616/mac)**
* **[アプリがMac App Storeから入手されていない場合](https://support.apple.com/ja-jp/guide/mac-help/mh40620/mac)**     
* **[セキュリティ設定を無効化してアプリを開く](https://support.apple.com/ja-jp/guide/mac-help/mh40617/mac)**
* **[Macでアプリを開けない場合](https://support.apple.com/ja-jp/guide/mac-help/mchlp1519/mac)**
* **[Mac に Rosetta をインストールする必要がある場合](https://support.apple.com/ja-jp/102527)**      


**プログラムのソースコードはGitHubで公開しております。ご利用の環境で実行ファイルをビルドすることが可能ですが、セキュリティ警告を完全に回避できることを保証するものではありません。なお、GitHubの macos-latest 環境でビルド可能であることは確認済みです。**      
**自己解決が可能な方や動作確認にご協力いただける方に限り、自己責任でご利用いただきますようお願い申し上げます。**    
**情報提供いただければ、可能な限り対応いたします。建設的なご意見やご要望については検討いたしますが、単なる不平や苦情はご遠慮ください。**

**情報提供や動作確認にご協力いただいたMacユーザの有志の皆様に感謝します。**

  * **Macユーザ間の情報交換の場として[こちらに【macOS関係の情報交換】](https://github.com/CSReviser/CaptureStream2/discussions/24)を作成しました。**

**尚、[［類似アプリ］](https://csreviser.github.io/CaptureStream2/application)のページにMacで動作するアプリを紹介しています。**




---
#### ＜ユーザ間の互助のお願い＞
#### MacOSユーザ間の互助にご協力をお願いします。

#### ＜MacOS版の仕様相違点＞
#### 語学講座CS2 は、ＯＳの違いに関係なく同一仕様となるようにしていますが、一部ＯＳに依存して仕様を変えています。MacOS版固有の仕様を記載しておきます。
#### １．初回起動時に録音音声ファイルの保存先フォルダを必ずユーザが指定する仕様になっています。
#### ２．設定ファイル(iniファイル)、Style Sheet(qssファイル)、ffmpegの保存先ファルダが異なります。
* #### 設定ファイル(iniファイル)： "~/Library/Preferences"
* #### Style Sheet(qssファイル)： 「stylesheet-mac.qss」を録音音声ファイル保存先フォルダに置くと、そちらが優先して使われます。（削除するとデフォルトに戻ります）
* #### ffmpeg： 下記の優先順位で存在するffmpegが使われます。[ffmpegパス設定](./SETTING_ffmpeg)でパスを設定した場合はそちらが優先されます。           
  * **１：保存フォルダで設定したフォルダにffmpegが存在する場合はそのffmpegが優先して使われます。使いたくない場合はffmpegをフォルダから削除または移動してください。**          
  * **２： "~/Library/Preferences"フォルダにffmpegが存在する場合はそのffmpegが優先して使われます。使いたくない場合はffmpegをフォルダから削除または移動してください。**          
  * **３： "/usr/local/bin"フォルダにffmpegが存在する場合はそのffmpegが優先して使われます。使いたくない場合はffmpegをフォルダから削除または移動してください。初期値で"/usr/local/bin"フォルダにあるffmpegを使う場合はテスト版が必要です。 [テスト版ダウンロードはこちら](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-MacOS-20241007-1.dmg)**
  * **４：語学講座CS2の本体（CaptureStream2）と同じフォルダにあるffmpegが使われます。** 
   * **[Macintosh 64bit版バイナリ](https://evermeet.cx/ffmpeg/)**
   * **[MacOS Apple Silicon版バイナリ](https://www.osxexperts.net/)**
#### 　　


#### ＜MacOS版実行ファイル作成環境＞
#### GitHubのactionsという機能を利用してMacOS用の実行ファイルを作成しています。
   * **macos-14（macos-latest）**
   * **Qt： 6.5LTS**
   * **Universal(Intel/M1両対応)**



#### 　　
#### 　　
#### 語学講座CS2 は、Qtというクロスプラットフォーム環境で開発しています。クロスプラットフォームは同一のソースファイルから異なるＯＳ（Windows/Linux/MacOS等）向けの実行ファイルをビルド（作成）できます。
#### [QtバージョンとmacOS対応](./Qt_vs_OS#macos)
* **[Qt5.15LTS ：](https://doc.qt.io/qt-5/macos.html) macOS 10.13 / 10.14 / 10.15 / 11 / 12 / 13 / 14**
* **[Qt6.2LTS ：](https://doc.qt.io/qt-6.2/macos.html) macOS 10.14 / 10.15 / 11 / 12 / 13 / 14**
* **[Qt6.5LTS ：](https://doc.qt.io/qt-6.5/macos.html) macOS 11 / 12 / 13 / 14**
* **[Qt6.8LTS ：](https://doc.qt.io/qt-6/macos.html) macOS 12 / 13 / 14 / 15**
#### 　　
#### 　　 
**Macユーザーからの報告例（参考）**            
  - **macOS Ventura 13.7.1 M1機**
  - **macOS Sequoia 15.0 M3機**  
  - **macOS Monterey 12.7.4 M1機**           
  - **macOS Sonoma 14.4.1 Intel機**
  - **macOS Sonoma 14.3.1 M1機**


#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
