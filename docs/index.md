## 語学講座CS2    
## [ブログ (お知らせ、他)](https://csreviser.github.io/CS2-blog/)  [［X：旧twitter］](https://twitter.com/CSReviser) 
## [NHKゴガク](https://www.nhk.or.jp/gogaku/) 　[Learn Japanese](https://www3.nhk.or.jp/nhkworld/en/learnjapanese/)
## [［類似アプリ］](./application)          
#### 語学講座CS2 は、NHKラジオ語学講座の らじる★らじる(聴き逃し)のストリーミング配信の録音を自動化するためのアプリです。録音した語学講座のファイルは著作権法で許されている範囲内でご利用ください。                
**このサイトから入手できる実行ファイルは、デジタル署名がないのでOSによって警告されます。悪意あるコードは含みませんが信用できない方は使用しないでください。ソースコードを公開していますので、自分で実行ファイルをビルドすることができます。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。他のＯＳでも環境を準備すればビルドできます。**
* **2024/06/04版をリリースしました。全てのユーザに更新を推奨します。**
* **macOS版で環境によってレコーディングボタンが正常に表示されない場合は[Menubar版](https://github.com/CSReviser/CaptureStream2/releases/download/20240604/CaptureStream2-MacOS-menubar-20240604-1.dmg)をお試しください。ノッチありMacで正常に表示されない可能性があると推測します。[［X：旧twitter］](https://twitter.com/CSReviser) または、[こちら](https://github.com/CSReviser/CaptureStream2/discussions/15)に情報提供をお願いします。**
* **2024/06仕様変更で一時しのぎでご利用の方は、多くのアプリで対応版が提供されています。使われていた元のアプリの更新をご確認下さい。[初めての方へ](./introduction)もご確認下さい。**
  
***

## ＜目次＞
1. ### **[ドキュメント](./#ドキュメント-1)**
1. ### **[実行ファイル](./#実行ファイル-1)**
1. ### [イメージ](./#語学講座cs2-イメージ)
1. ### [既知課題](./#既知課題-1)
1. ### [参考公開](./#参考公開-1)


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
### [2024/06/04版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/06/04/)
### Windows用
* ### **[CaptureStream2-Windows-x64-20240604.zip 【64bit版】](https://github.com/CSReviser/CaptureStream2/releases/download/20240604/CaptureStream2-Windows-x64-20240604.zip)**
##### 　※Windows用32bit版は[2024/06/04版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/06/04/)にリンクがあります。

### Ubuntu用
* ### **[CaptureStream2-Ubuntu-20240604.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20240604/CaptureStream2-Ubuntu-20240604.zip)**
##### 　※このサイトで提供している実行ファイルが動作しないときはご自身でビルドをお試しください。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。


### MacOS用 ※動作未確認
* ### **[CaptureStream2-MacOS-20240604.dmg](https://github.com/CSReviser/CaptureStream2/releases/download/20240604/CaptureStream2-MacOS-20240604.dmg)**
* ### **[CaptureStream2-MacOS-menubar-20240604-1.dmg](https://github.com/CSReviser/CaptureStream2/releases/download/20240604/CaptureStream2-MacOS-menubar-20240604-1.dmg)　※ MacOS版で縦方向の表示の調整を意図した版です。レコーディングボタンが正常に表示されない場合にお試しください。ノッチありMacの方はこちらの方が良いかもしれません。**      

### ※バグ報告などは[こちら](https://github.com/CSReviser/CaptureStream2/discussions/15)に投稿してください。
#### 　　　　　　
#### 　　　　　　
#### 　　　　　　

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜語学講座CS2 イメージ＞
## ［Windows版］
<img src="https://github.com/CSReviser/CaptureStream/assets/46049273/630baada-27f1-4984-a6ce-3f2bc6349be4" width="350"> 

## ［Ubuntu版］
<img src="https://user-images.githubusercontent.com/46049273/204998600-0588a130-0c18-48c9-a07d-af87f2f15a4f.png" width="350"> 

## ［macOS版］
<img src="https://github.com/CSReviser/CaptureStream/assets/46049273/a27f1c9e-9a01-4fd6-baa7-d52d907525d2" width="350"> 


#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜既知課題＞
**※ 2024/06/15現在、不具合は確認しておりません。2024/04/19 Ubuntu版で不具合報告を頂きましたが、現象を確認できていません。情報提供にご協力お願いします。**

### 2024年06〜07月：
* **[「ゴガクアプリ」アップデート対応](https://www.nhk.or.jp/gogaku/topics2.html)**
* **[前週]機能削除検討（ゴガクアプリ仕様変更）**
* **macOS版メニューバー表示問題(暫定)**
* **番組一覧表示メニュー化**
  
### 2024年8〜9月：
* **Ubuntu24.04.1LTS対応検討**

### 2024年12月末：
* **macos-12廃止(github)**

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
* **Apple silicon用バイナリ(MacOS版)作成(キャンセル中止)**

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
##### ※ 録音した語学講座のファイルは著作権法で許されている範囲内でご利用ください。                     
***
### ＜参考公開＞
### [＜Classic UI版 （参考公開）＞](https://csreviser.github.io/CaptureStream2-Classic/)     

<img src="https://user-images.githubusercontent.com/46049273/215409469-60aa60a4-3057-4dcc-a838-bc416ce18d6c.png" width="100" height="95" border="1"><img src="https://user-images.githubusercontent.com/46049273/217703729-a7ae416f-f6d3-4a5c-bc55-1689e7d81ea9.png" width="100" height="95" border="1"><img src="https://user-images.githubusercontent.com/46049273/217985608-3667070b-f8e2-4aea-8782-480ffe6f2b12.png" width="100" height="95" border="1">

***
### [＜extra版 （参考公開）＞](https://csreviser.github.io/CaptureStream2-extra/)                     
<img src="https://user-images.githubusercontent.com/46049273/219273475-d5a3ec0b-d1ae-4523-a50e-3ab0fc1dec92.png" width="150" height="95" border="1"><img src="https://user-images.githubusercontent.com/46049273/219273859-02f739d2-3ce0-4e2d-b4fc-70ed6c1cc340.png" width="150" height="95" border="1">


***
### [＜Lite版 （参考公開）＞](https://csreviser.github.io/CaptureStream2-Lite/)                     
<img src="https://github-production-user-asset-6210df.s3.amazonaws.com/46049273/277073263-322d09d0-b332-4bfc-a05e-a1bdafd430b2.png" width="100" height="98" border="1"><img src="https://github-production-user-asset-6210df.s3.amazonaws.com/46049273/277073637-c0b449fb-30a1-4b3c-87a7-58ca83a1b07e.png" width="100" height="98" border="1">


***
### [＜ラジ版 （参考公開）＞](https://csreviser.github.io/CaptureStream2-Rad/)                     
<img src="https://github-production-user-asset-6210df.s3.amazonaws.com/46049273/278784620-bf19a62f-7230-451d-9043-e94bc837d1c4.png" width="200">



***
### [＜語学講座ＣＳ （参考公開）＞](https://csreviser.github.io/CaptureStream2/old/)                     
<img src="https://github.com/CSReviser/CaptureStream/assets/46049273/def5712d-7744-45fc-92ed-b3d8cc42f645" width="100">



#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***

 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
