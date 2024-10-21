## 語学講座CS2    
## [ブログ (お知らせ、他)](https://csreviser.github.io/CS2-blog/)  [［X：旧twitter］](https://twitter.com/CSReviser) 
## [NHKゴガク](https://www.nhk.or.jp/gogaku/) 　[Learn Japanese](https://www3.nhk.or.jp/nhkworld/en/learnjapanese/)
## [［類似アプリ］](./application)          
#### 語学講座CS2 は、NHKラジオ語学講座の らじる★らじる(聴き逃し)のストリーミング配信の録音を自動化するためのアプリです。録音した語学講座のファイルは著作権法で許されている範囲内でご利用ください。                
* **2024/10/07版をリリースしました。今回の更新は必須ではありませんが、2024/06版以前をお使いの方は更新を推奨します。**
* **ffmpegが存在するフォルダのパスを指定可能にしました。指定しない場合の初期値は従来と同じとなります。環境によって生じるffmpeg関連の不具合対策です。環境にあったffmpegを準備してください。**
* **2024/06版以前から更新する場合は10桁の番組IDに再設定して下さい。任意番組設定で確認ボタンを押すと4桁のIDは10桁のIDに変換されます。自動変換されない場合は手動で変更してください。**
  
***

## ＜目次＞
1. ### **[ドキュメント](./#ドキュメント-1)**
1. ### **[実行ファイル](./#実行ファイル-1)**
1. ### [イメージ](./#語学講座cs2-イメージ)
1. ### [既知課題](./#既知課題-1)
1. ### [参考公開(順次終了)](./#参考公開)


***

### ＜ドキュメント＞
* **[初めての方へ](./introduction)**
* **[従来との主な違い](./CS_vs_CS2)** 
* **[制限事項](./limitations)** 
* **[必要要件](./requirements)** 
* **[ストリーミング公開期間](./Streaming_period)**
* **[インストール手順](./install)** 
* **[MacOS版について](./macos)** 
* **[アップデート（更新）](./update)**
* **[トラブルシューティング](./troubleshooting)** 
* **[カスタマイズメニュー](./menu)** 
* **[対象講座と番組ID一覧](./courses_name)** 
* **[任意らじる聴き逃し番組設定](./SETTING_COURSES)**
* **[欧州語学講座応用編分離設定](./koza_separation)**
* **[拡張子の選択](./SETTING_extension)** 
* **[［前週］チェックボックス](./last_week)**
* **[ファイル名のカスタマイズ設定](./file_name)**
* **[タスクスケジューラの設定方法(Windows)](./scheduler-win)**
* **[スケージュール録音の設定方法(Ubuntu)](./scheduler-linux)**
* **[コマンド・ライン・オプション](./command_line_option)**
* **[ffmpeg最新版入手サイト](./FFMPEG)**
* **[類似アプリ](./application)**     
* **[リンク](./link)**
* **[英語多聴・多読関連リンク（参考情報）](./extensive_reading)**

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜実行ファイル＞
**このサイトから入手できる実行ファイルは、デジタル署名がないのでOSによって警告されます。悪意あるコードは含みませんが信用できない方は使用しないでください。ソースコードを公開していますので、自分で実行ファイルをビルドすることができます。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。他のＯＳでも環境を準備すればビルドできます。**      


### [2024/10/07版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/10/07/)
### Windows用
* ### **[CaptureStream2-Windows-x64-20241007.zip 【64bit版】](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-Windows-x64-20241007.zip)**
  ##### ※Windows用32bit版は[2024/10/07版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/10/07)にリンクがあります。

### Ubuntu用（参考公開）
* ### **[CaptureStream2-Ubuntu22.04-20241007.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-Ubuntu-20241007.zip)**
* ### **[CaptureStream2-Ubuntu24.04-20241007.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-Ubuntu2404-20241007.zip)**
  ##### ※このサイトで提供している実行ファイルが動作しないときはご自身でビルドをお試しください。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。


### MacOS用 [【MacOSユーザの方へ】](https://csreviser.github.io/CaptureStream2/macos)
* **Mac版は実行ファイルのトップページ掲載を見合わせています。[【MacOSユーザの方へ】](https://csreviser.github.io/CaptureStream2/macos)および[【必要要件】](./requirements)をご確認下さい。プログラムのソースコードはGitHubで公開しています。ご利用環境でご自身でビルドすることでご使用可能と思います。**  
  * **Macユーザー間の情報交換の場として[こちらに【macOS関係の情報交換】](https://github.com/CSReviser/CaptureStream2/discussions/24)を作成しました。**

### ※バグ報告などは[こちら](https://github.com/CSReviser/CaptureStream2/discussions/23)に投稿してください。
#### 　　　　　　
#### 　　　　　　
#### 　　　　　　

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜語学講座CS2 イメージ＞
#### ［Windows版］
<img src="https://github.com/CSReviser/CaptureStream/assets/46049273/630baada-27f1-4984-a6ce-3f2bc6349be4" width="350"> 

#### ［Ubuntu版］
<img src="https://user-images.githubusercontent.com/46049273/204998600-0588a130-0c18-48c9-a07d-af87f2f15a4f.png" width="350"> 

#### ［macOS版］
<img src="https://github.com/CSReviser/CaptureStream/assets/46049273/a27f1c9e-9a01-4fd6-baa7-d52d907525d2" width="350"> 

##### **※macOS版のイメージ写真はyarakaoriさんから提供いただきました。**

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜既知課題＞         
**※ 2024/10/06現在、不具合は確認していません。**

### 次回更新時適用予定：
* **「/usr/local/bin/」にあるffmpegを使う(macOS)**

### 2025年1月：
* **macos-15(github)テスト**

### 2025年2月：
* **2025年度講座情報収集**

### 2025年3月末：
* **参考公開版更新終了**

### 2025年4月：
* **2025年度講座対応**

### 2025年10月：
* **Windows10サポート終了**
* **Windows 32bit版終了**
* **NHKネット配信「必須業務化」**

### 2026年03月末:
* **NHK AM放送波一本化**


### 日程未定：
* **全OS共通**
  * **Qt6.8移行検討**
  * **ffmpeg同梱中止検討**
  * **ID自動変換(4to10)機能削除**
  * **[前週］機能削除**
  * **qt4/qt5依存コード削減/削除**
  * **エラーチェック強化（見直)**
  * **Qtバージョン変更時文字化け対策（制限事項）**
* **Windows関係**
  * **32bit版(Windows版)終了検討**
* **ubuntu関係**
  * **Ubuntu24.04LTS対応/移行**
  * **日本語入力(番組名での任意番組設定)**
* **macOS関係**
  * **実行ファイル公開見合わせ中**
  * **ノッチありMac対応検討(暫定対応済)**
  * **バイナリ作成終了**
  * **Apple Silicon用バイナリ作成(再検討)**

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
##### ※ 録音した語学講座のファイルは著作権法で許されている範囲内でご利用ください。                     
***
### ＜参考公開＞
* **[語学講座ＣＳ２-Clasic- （参考公開）](https://csreviser.github.io/CaptureStream2-Classic/)**     
* **[語学講座ＣＳ２【extra】（参考公開）](https://csreviser.github.io/CaptureStream2-extra/)**                    
* **[語学講座ＣＳ２【Lite】（参考公開）](https://csreviser.github.io/CaptureStream2-Lite/)**                    
* **[語学講座ＣＳ２【ラジ】（参考公開）](https://csreviser.github.io/CaptureStream2-Rad/)**                     
* **[語学講座ＣＳ （参考公開）](https://csreviser.github.io/CaptureStream2/old/)**                     


#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***

 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <link rel="shortcut icon" type="image/x-icon" href="https://raw.githubusercontent.com/CSReviser/CaptureStream2/master/icon.ico">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
