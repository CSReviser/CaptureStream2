## 語学講座CS2    
## [ブログ (お知らせ、他)](https://csreviser.github.io/CS2-blog/)  [［X：旧twitter］](https://twitter.com/CSReviser) 
## [NHKゴガク](https://www.nhk.or.jp/gogaku/) 　[Learn Japanese](https://www3.nhk.or.jp/nhkworld/en/learnjapanese/)
## [［類似アプリ］](./application)          
#### 語学講座CS2 は、NHKラジオ語学講座の らじる★らじる(聴き逃し)のストリーミング配信の録音を自動化するためのアプリです。           
#### このサイトから入手できる実行ファイルは、デジタル署名がないのでOSによって警告されます。悪意あるコードは含みませんが信用できない方は使用しないでください。ソースコードを公開していますので、自分で実行ファイルをビルドすることができます。
    
* #### 2024年度版（2024/04/13版）をリリースしました。現在不具合がない方は更新必須ではありませんが、2023年度版を使用されている場合は更新をお願いします。何らかの理由で更新できない場合は [［類似アプリ］](./application) も参考にして、他のツールへの移行をご検討ください。2024年度欧州系の「応用編」語学講座の番組IDが廃止され「まいにちXXX語」の言語ごとに１つの番組IDとなりました。2023年度版から更新の場合は「らじる番組」ボタンを再設定してください。

***

## ＜目次＞
1. ### [ドキュメント](./#ドキュメント-1)
1. ### [実行ファイル](./#実行ファイル-1)
1. ### [イメージ](./#語学講座cs2-イメージ)
1. ### [既知課題](./#既知課題-1)
1. ### [参考公開](./#参考公開-1)


***

### ＜ドキュメント＞
* #### [初めての方へ](./introduction)
* #### [従来との主な違い](./CS_vs_CS2) 
* #### [制限事項](./limitations) 
* #### [必要要件](./requirements) 
* #### [ストリーミング公開期間](./Streaming_period) 
* #### [Windows版インストール手順](./install_win) 
* #### [MacOS版インストール手順](./install_mac)
* #### [MacOS版について](./macos) 
* #### [アップデート（更新）](./update) 
* #### [対象講座と番組ID一覧](./courses_name) 
* #### [任意らじる聴き逃し番組設定](./SETTING_COURSES)
* #### [拡張子の選択](./SETTING_extension) 
* #### [［前週］チェックボックス](./last_week)
* #### [ファイル名のカスタマイズ設定](./file_name)
* #### [タスクスケジューラの設定方法(Windows)](./scheduler-win)
* #### [スケージュール録音の設定方法(Ubuntu)](./scheduler-linux)
* #### [コマンド・ライン・オプション](./command_line_option)
* #### [ffmpeg最新版入手サイト](./FFMPEG)
* #### [類似アプリ](./application)     
* #### [リンク](./link)

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜実行ファイル＞
### [2024/04/13版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/04/13/)
### Windows用
### [CaptureStream2-Windows-x64-20240413.zip 【64bit版】](https://github.com/CSReviser/CaptureStream2/releases/download/20240413/CaptureStream2-Windows-x64-20240413.zip)
##### 　※Windows用32bit版は[2024/04/13版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/04/13/)にリンクがあります。
### Ubuntu用
### [CaptureStream2-Ubuntu-20240413.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20240413/CaptureStream2-Ubuntu-20240413.zip)
### MacOS用 ※動作未確認
### [CaptureStream2-MacOS-20240414４.dmg](https://github.com/CSReviser/CaptureStream2/releases/download/20240414/CaptureStream2-MacOS-20240414.dmg)
        
### ※バグ報告などは[こちら](https://github.com/CSReviser/CaptureStream2/discussions/12)に投稿してください。
#### 　　　　　　
#### 　　　　　　
#### 　　　　　　

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜語学講座CS2 イメージ＞
## ［Windows版］
<img src="https://github-production-user-asset-6210df.s3.amazonaws.com/46049273/280167555-13a1fac3-f2c7-41c0-be36-d7cd68dfc26b.png" width="350"> 

## ［Ubuntu版］
<img src="https://user-images.githubusercontent.com/46049273/204998600-0588a130-0c18-48c9-a07d-af87f2f15a4f.png" width="350"> 

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜既知課題＞
**※ 2024/04/07現在、不具合は確認していません。**

### 2024年04月第二週：[4/13リリース](https://csreviser.github.io/CS2-blog/2024/04/13/)
* #### 2024年度版
* #### コマンドラインオプション追加

### 2024年4月末〜5月：
* #### Ubuntu24.04LST対応検討

### 2024年06〜07月：
* #### [「ゴガクアプリ」アップデート対応](https://www.nhk.or.jp/gogaku/topics2.html)


### 日程未定：
* #### ［前週］機能削除
* #### qt4/qt5依存コード削減/削除
* #### Ubuntu24.04LST対応/移行
* #### エラーチェック強化（見直）
* #### cmake対応(残：Windows版)
* #### 32bit版(Windows版)終了検討
* #### MacOS版バイナリ作成終了(github環境M1化の為)
* #### Apple silicon用バイナリ(MacOS版)作成(キャンセル中止)

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


#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***

 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
