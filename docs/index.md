## 語学講座CS2    
## [ブログ (お知らせ、他)](https://csreviser.github.io/CS2-blog/)  [［X：旧twitter］](https://twitter.com/CSReviser) 
## [NHKゴガク](https://www.nhk.or.jp/gogaku/) 　[Learn Japanese](https://www3.nhk.or.jp/nhkworld/en/learnjapanese/)
## [［類似アプリ］](./application)          
#### 語学講座CS2 は、NHKラジオ語学講座の らじる★らじる(聴き逃し)のストリーミング配信の録音を自動化するためのアプリです。録音した語学講座のファイルは著作権法で許されている範囲内でご利用ください。                
* **2024/08のらじる★らじる聴き逃しの仕様変更に対応した2024/08/10版をリリースしました。**
* **macOS版で動作しない不具合報告を頂きましたが、Windows版では不具合を確認できていません。情報提供にご協力お願いします。**
  
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


### [2024/08/10版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/08/10/)
### Windows用
* ### **[CaptureStream2-Windows-x64-20240810.zip 【64bit版】](https://github.com/CSReviser/CaptureStream2/releases/download/20240810/CaptureStream2-Windows-x64-20240810.zip)**
##### 　※Windows用32bit版は[2024/08/10版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/08/10/)にリンクがあります。

### Ubuntu用
* ### **[CaptureStream2-Ubuntu-20240810.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20240810/CaptureStream2-Ubuntu-20240810.zip)**
##### 　※このサイトで提供している実行ファイルが動作しないときはご自身でビルドをお試しください。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。


### MacOS用 [※動作未確認](https://csreviser.github.io/CaptureStream2/macos)
* ### **[CaptureStream2-MacOS-20240810.dmg](https://github.com/CSReviser/CaptureStream2/releases/download/20240810/CaptureStream2-MacOS-20240810.dmg)**
   

### ※バグ報告などは[こちら](https://github.com/CSReviser/CaptureStream2/discussions/17)に投稿してください。
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
**※ 2024/08/10版をリリースしました。**


### 2024/08/10版更新内容：
* **2024年8月らじる★らじる聴き逃し仕様変更対応**
* **macOS版メニューバー表示問題(暫定)**
* **メニュー追加**
  * **番組一覧表示**
  * **語学講座CS2サイト表示**
* **コマンドラインオプション追加**

### 2024年10月：
* **Qt6.8対応検討**

### 2024年12月末：
* **macos-12廃止(github)**

### 2025年1月：
* **macos-13/14/15(github)テスト**

### 2025年2月：
* **2025年度講座情報収集**

### 2025年3月末：
* **参考公開版更新終了**

### 日程未定：
* **[前週］機能削除**
* **qt4/qt5依存コード削減/削除**
* **Ubuntu24.04LTS対応/移行**
* **エラーチェック強化（見直)**
* **32bit版(Windows版)終了検討**
* **ノッチありMac対応検討**
* **MacOS版バイナリ作成終了(github環境M1化の為)**
* **Apple silicon用バイナリ(MacOS版)作成(キャンセル)**

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
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
