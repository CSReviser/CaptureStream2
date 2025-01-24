## 語学講座CS2    
## [ブログ (お知らせ、他)](https://csreviser.github.io/CS2-blog/)  [［X：旧twitter］](https://twitter.com/CSReviser) 
## [NHKゴガク](https://www.nhk.or.jp/gogaku/) 　[Learn Japanese](https://www3.nhk.or.jp/nhkworld/en/learnjapanese/)
## [［類似アプリ］](./application)          
#### 語学講座CS2は、NHKラジオ語学講座の「らじる★らじる」（聴き逃し）ストリーミング配信を自動録音するためのアプリです。録音した語学講座のファイルは、著作権法で認められた範囲内でご利用ください。                
* **2024/11/26以降4桁の番組IDが使用できなくなりました。最新版に更新して任意番組ボタンの再設定をして下さい。[任意らじる聴き逃し番組設定の手順はこちら](./SETTING_COURSES)**
  
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
* **[対象講座と番組ID一覧](./courses_name)** 
* **[インストール手順](./install)** 
* **[MacOS版について](./macos)** 
* **[アップデート（更新）](./update)**
* **[各種設定手順](./settings)**
* **[FAQ（よくある質問）](./FAQ)**
* **[トラブルシューティング](./troubleshooting)** 
* **[ffmpeg最新版入手サイト](./FFMPEG)**
* **[類似アプリ](./application)**     
* **[リンク](./link)**
* **[英語多聴・多読関連リンク（参考情報）](./extensive_reading)**

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜実行ファイル＞
**このサイトで提供している実行ファイルにはデジタル署名がないため、OSによって警告が表示される場合があります。悪意のあるコードは含まれておりませんが、不安のある方は使用をお控えください。なお、ソースコードを公開していますので、ご自身で実行ファイルをビルドすることも可能です。ただし、ビルドした場合でもセキュリティ警告が完全に回避される保証はありません。[インストール手順はこちらから使用するOSに合った手順をお選びください。](./install)**      


### [2024/10/07版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/10/07/)
### Windows用
* ### **[CaptureStream2-Windows-x64-20241007.zip 【64bit版】](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-Windows-x64-20241007.zip)**
  ##### ※Windows用32bit版は[2024/10/07版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2024/10/07)にリンクがあります。

### Ubuntu用（参考公開）
* ### **[CaptureStream2-Ubuntu22.04-20241007.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-Ubuntu-20241007.zip)**
* ### **[CaptureStream2-Ubuntu24.04-20241007.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-Ubuntu2404-20241007.zip)**
  ##### ※このサイトで提供している実行ファイルが動作しないときはご自身でビルドをお試しください。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。


### MacOS用 [【MacOSユーザの方へ】](https://csreviser.github.io/CaptureStream2/macos)
* **Mac版は実行ファイルのトップページ掲載を見合わせています。[【MacOSユーザの方へ】](./macos)、[FAQ](./FAQ#macos)および[【必要要件】](./requirements)をご確認頂き、リスクをご理解の上、自己責任で自己解決出来る方のみご利用ください。**  
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
**※ 2025/01/24現在、不具合は確認していません。**

### 次回更新時適用予定：
* **「/usr/local/bin/」にあるffmpegを使う(macOS)  [テスト版ダウンロードはこちら](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-MacOS-20241007-1.dmg)**
* **ID自動変換(4to10)機能削除**
* **サムネイル対象番組拡大**
* **番組設定プリセット修正**

### 2025年2月：
* **2025年度講座情報収集**
  * **[『ＮＨＫ語学テキスト音声』発売](https://news.nhk-book.co.jp/archives/28185)**
  * **[2025年度「きそナビ」チラシ](https://shoten-pr.nhk-book.co.jp/files/2025年度「きそナビ」（基礎英語シリーズ他）(1).pdf)**

### 2025年2月上旬：
* **NHK出版春の企画説明（書店向け）**

### 2025年2月上旬〜中旬：
* **[2025年度放送番組編成計画](https://www.nhk.or.jp/info/pr/hensei/)**

### 2025年3月31日：
* **2025年度語学講座放送開始予定**
* **参考公開版更新終了**

### 2025年4月：
* **2024年度最終週対応**
* **2025年度講座対応**
  * **削除：中高生の基礎英語inEnglish**
* **「必要要件」からWindows10除外**
* **macos-15(github)テスト**

### 2025年10月：
* **Windows10サポート終了**
* **Windows 32bit版終了**
* **NHKネット配信「必須業務化」**

### 2026年03月末:
* **NHK AM放送波一波化**


### 日程未定：
* **全OS共通**
  * **サムネ付コマンドラインOP追加**
  * **Qt6.8移行検討**
  * **ffmpeg同梱中止検討**
  * **[前週］機能削除**
  * **qt4/qt5依存コード削減/削除**
  * **エラーチェック強化（見直)**
  * **Qtバージョン変更時文字化け対策（制限事項）**
  * **GitHub copilot試用**
* **Windows関係**
  * **32bit版(Windows版)終了検討**
* **ubuntu関係**
  * **Ubuntu24.04LTS対応/移行**
  * **日本語入力(番組名での任意番組設定)**
  * **systemd利用自動実行手順作成**
* **macOS関係**
  * **セキュリティ警告回避策**
  * **実行ファイルTopページ掲載見合わせ中**
  * **ノッチありMac対応検討(暫定対応済)**
  * **Intelサポート終了(Apple)対応**
  * **バイナリ作成終了**
* **ドキュメント整備関係**
  * **FAQページの充実、修正**
  * **エラーメッセージ一覧作成**

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
