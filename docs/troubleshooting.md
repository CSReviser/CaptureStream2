## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【トラブルシューティング】　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
####   　
1. **初めて使おうとして動作しない場合**
   * **[初めての方へ](./introduction)**
   * **[制限事項](./limitations)**
   * **[必要要件](./requirements)**
   * **※上記に該当しない方は、[類似アプリ](./application)を参考にするなど他のアプリをご検討下さい。**
1. **使っていたが動作しなくなった場合**
   * **[実行ファイル](./#%E5%AE%9F%E8%A1%8C%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB-1)に対策が適用された新しいバージョンがあれば更新をお願いします。**
   * **[Discussions](https://github.com/CSReviser/CaptureStream2/discussions)に同様の問題が登録されていないか確認して下さい。**
   * **[既知課題](./#%E6%97%A2%E7%9F%A5%E8%AA%B2%E9%A1%8C-1)に同様の問題が登録されていないか確認して下さい。**
   * **緊急の問題は[［X：旧twitter］](https://twitter.com/CSReviser)や[TOPページ](https://csreviser.github.io/CaptureStream2/)に情報発信される場合があります。**
1. **バージョンアップしたら動作しない場合**
   * **古いOSを使っている方は[必要要件](./requirements)を再度確認下さい。**
   * **設定削除をお試し下さい。「カスタマイズ」＞「設定削除(終了)」、確認窓が開いたら「Yes」をクリックして下さい。**
   * **[Discussions](https://github.com/CSReviser/CaptureStream2/discussions)に同様の問題が登録されていないか確認して下さい。**
   * **バグと思われる場合は[Discussions](https://github.com/CSReviser/CaptureStream2/discussions)に登録して下さい。**

*** 
*** 
**＜不具合現象と対応例＞**

*** 


* **現象：レコーディング失敗となり録音できない。ffmpeg関連のエラーメッセージが表示される。**
* **原因：（1）一時的な不具合が発生している。（推測）（2）ffmpegの動作不具合。**
* **対応：（1）時間をあけて何度かリトライする。（2）環境に合った、動作するffmpegに入れ替える。[ffmpegパス設定](https://csreviser.github.io/CaptureStream2/SETTING_ffmpeg)、[ffmpeg最新版入手サイト](https://csreviser.github.io/CaptureStream2/FFMPEG)をご確認ください。**

*** 

* **現象：「番組ID：XXXX_XXのデータ取得エラー」と表示される。（XXXX_XXはチェックした番組ボタンの番組ID）**
* **原因：チェックしたらじる★らじる番組の情報が取得できない場合に表示されるメッセージです。**
* **対応：インターネットの接続状態を確認してください。[らじる★らじる](https://www.nhk.or.jp/radio/ondemand/index_genre.html?genre=language)が再生できること、[よくあるご質問（らじる★らじる）](https://www.nhk.or.jp/radio/info/faq.html)、[NHK 音声再生確認ページ](https://www.nhk.or.jp/radio/soundcheck/)をご確認ください。NHKのらじる★らじるサービスは日本国内限定で、海外では聴くことが出来ません。**

*** 

* **現象：任意設定の番組ボタンの表示が文字化けする。バージョンアップ／バージョンダウン時に発生する。**
* **原因：Qtのバージョンが変わると文字化けすることがある。（推測）**
* **対応：（1）任意番組設定で再設定する。（2）設定削除で設定を初期化する。**


*** 



####   　
####   　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
-
