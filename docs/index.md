## 語学講座CS2    
## [NHKゴガク](https://www.nhk.jp/g/gogaku/) 　
## [Learn Japanese](https://www3.nhk.or.jp/nhkworld/en/learnjapanese/)

## [ブログ (お知らせ、他)](https://csreviser.github.io/CS2-blog/)  [［X：旧twitter］](https://twitter.com/CSReviser) 
## [［類似アプリ］](./application)                          
* **一部のAI検索サービス（Google AI等）において、[類似アプリ](./application)と『語学講座CS2』を混同する誤情報が拡散しています。各アプリは開発元が異なります。[類似アプリ](./application)については各提供元にお問い合わせください。**        

#### 語学講座CS2は、NHKラジオ語学講座の「らじる★らじる」（聴き逃し）ストリーミング配信を自動録音するためのデスクトップアプリです。録音した語学講座のファイルは、著作権法で認められた範囲内でご利用ください。                
* **2026年度版は2026/04/07版をリリースしました。開発環境はQt6.11を使っています。[QtとOSの対応はこちらで確認できます。](./Qt_vs_OS)**
     
  
***

## ＜目次＞
1. ### **[ドキュメント](./#ドキュメント-1)**
1. ### **[実行ファイル](./#実行ファイル-1)**
1. ### **[開発テスト版](./#開発テスト版-1)**
1. ### [イメージ](./#語学講座cs2-イメージ)
1. ### [既知課題](./#既知課題-1)

***

### ＜ドキュメント＞
* **[初めての方へ](./introduction)**
* **[語学講座CSとの主な違い](./CS_vs_CS2)** 
* **[制限事項](./limitations)** 
* **[必要要件](./requirements)** 
* **[対応OS(QtとOSの対応)](./Qt_vs_OS)**     
* **[ストリーミング公開期間](./Streaming_period)**
* **[対象講座と番組ID一覧](./courses_name)** 
* **[インストール手順](./install)** 
* **[MacOS版について](./macos)** 
* **[アップデート（更新）](./update)**
* **[各種設定手順](./settings)**
* **[Tips(応用・活用例)](./tips)**
* **[FAQ（よくある質問）](./FAQ)**
* **[トラブルシューティング](./troubleshooting)** 
* **[ffmpeg最新版入手サイト](./FFMPEG)**
* **[類似アプリ](./application)**     
* **[関連ツール](./tools)**       
* **[リンク](./link)**
* **[英語多聴・多読関連リンク（参考情報）](./extensive_reading)**

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜実行ファイル＞
**このサイトで提供している実行ファイルにはデジタル署名がないため、OSによって警告が表示される場合があります。悪意のあるコードは含まれておりませんが、不安のある方は使用をお控えください。なお、ソースコードを公開していますので、ご自身で実行ファイルをビルドすることも可能です。ただし、ビルドした場合でもセキュリティ警告が完全に回避される保証はありません。[インストール手順はこちらから使用するOSに合った手順をお選びください。](./install)**      


### [2026/04/07版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2026/04/07/)
### MacOS用 
* **[【MacOSユーザの方へ】](./macos)、[FAQ](./FAQ#macos)および[【必要要件】](./requirements)をご確認頂き、リスクをご理解の上で自己解決できる方、動作確認にご協力頂ける方はご利用ください。**
* ### **[CaptureStream2-MacOS-20260407.dmg](https://github.com/CSReviser/CaptureStream2/releases/download/20260407/CaptureStream2-MacOS-20260407.dmg)**
  * **Macユーザー間の情報交換の場として[こちらに【macOS関係の情報交換】](https://github.com/CSReviser/CaptureStream2/discussions/24)を作成しました。**

### Windows用
* ### **[CaptureStream2-Windows-x64-20260407.zip 【64bit版】](https://github.com/CSReviser/CaptureStream2/releases/download/20260407/CaptureStream2-Windows-x64-20260407.zip)**
* ### **[CaptureStream2-Windows-x86-20260407.zip 【32bit版】](https://github.com/CSReviser/CaptureStream2/releases/download/20260407/CaptureStream2-Windows-x86-20260407.zip)**
> ⚠️ ご注意：本ソフトウェアはデジタル署名されていないため、Windows 11の「スマート アプリ コントロール（Smart App Control）」が有効な環境では実行できない場合があります。  
> Smart App Controlが有効なPCでは、署名付きのアプリケーションのみが許可されます。詳細はMicrosoftの公式ドキュメントをご参照ください。

### Linux用（参考公開）
* ### **[CaptureStream2-AppImage-x64-20260407.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20260407/CaptureStream2-AppImage-x64-20260407.zip)**
* ### **[CaptureStream2-AppImage-arm64-20260407.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20260407/CaptureStream2-AppImage-arm64-20260407.zip)**
  ##### ※このサイトで提供している実行ファイルが動作しないときはご自身でビルドをお試しください。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。
  ##### **※ Appimage版はfuseなど追加モジュールのinstallが必要な場合があります。**
  ##### **※ Linux OSにWINEをinstallしてWindows版を使うという方法もあります。**

### Ubuntu用（参考公開）
* ### **[CaptureStream2-Ubuntu-20260407.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20260407/CaptureStream2-ubuntu-20260407.zip)**
  ##### ※このサイトで提供している実行ファイルが動作しないときはご自身でビルドをお試しください。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。


### ※バグ報告などは[こちら](https://github.com/CSReviser/CaptureStream2/discussions/34)に投稿してください。
#### 　　　　　　

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 
***
### ＜style sheet＞
* **[stylesheet変更例(講座ボタン色変更)](./stylesheet)**


### Mac用
* ### **[stylesheet-mac.zip](https://github.com/CSReviser/cs2-builder/releases/download/20260406/stylesheet-mac.zip)**


### Windows用
* ### **[stylesheet-win.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20250608/stylesheet-win.zip)**


### Linux / Ubuntu用
* ### **[stylesheet-ubu.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20250608/stylesheet-ubu.zip)**



#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜開発テスト版＞
* **[2026/04/07テスト版(AppleSilicon専用バイナリーテスト)](./test_release)**


#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜語学講座CS2 イメージ＞
#### ［Windows版］
<img src="https://github.com/user-attachments/assets/09853647-953d-4a62-a3b2-18838afb51ad" width="350"> 

#### ［Ubuntu版］
<img src="https://github.com/user-attachments/assets/c6497566-8d98-401f-894a-47bbafc17703" width="350"> 

#### ［macOS版］
<img src="https://github.com/user-attachments/assets/890fab4f-7f26-4d96-95c1-ff547e3a90e3" width="350"> 


#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜既知課題＞         
**※ 2026/04/07版　2026年度版をリリースしました。**

### 次回リリース時適用予定：
* **AppleSilicon専用バイナリ併用**


### 2026年05月05日：
* **[特番『深く知りたい!英語でニュースを読み解くと』放送予定](https://www.nhk.jp/p/rs/5LVVPXXKVK/)**

### 2026年05月08日：
* **[Qt6.11.1リリース予定](https://wiki.qt.io/Qt_6.11_Release)**

### 2026年05月上旬：
* **ubuntu 24.04テスト版**

### 2026年06月11日：
* **[Qt6.11.2リリース予定](https://wiki.qt.io/Qt_6.11_Release)**

### 2026年08月31日：
* **[Qt6.11.3リリース予定](https://wiki.qt.io/Qt_6.11_Release)**

### 2026年10月13日：
* **[Windows10個人向けESU終了](https://www.microsoft.com/ja-jp/windows/extended-security-updates)**

### 2026年10月〜11月頃：
* **macos-27 universal build可否確認**    
* **Apple Silicon専用/Universal併用**

### 2027年04〜05月頃：
* **ubuntu22.04LTSサポート終了**

### 2028年10月：
* **Windows10のESU（拡張セキュリティ更新）終了**


### 日程未定：
* **全OS共通**
  * **開発環境Mac試行**
  * **ffmpeg同梱中止検討**
  * **[前週］機能削除**
  * **GitHub actionsでのテスト環境構築**
* **macOS関係**
  * **NFD/NFC文字コード問題対応検討**
  * **AppleSilicon専用バイナリ**
  * **style sheet見直・修正**
  * **Homebrew tap試行中**
  * **Intelサポート終了(Apple)対応**
  * **バイナリ作成終了**
* **Windows関係**
  * **32bit版(Windows版)終了検討**
* **Linux関係**
  * **Appimage-builder環境構築**
  * **install手順(Appimage版)作成**
  * **WINEを使うinstall手順作成**
  * **docker image作成検討**
  * **Wayland環境対応検討**
  * **日本語入力(番組名での任意番組設定)**
  * **systemd利用自動実行手順作成**
* **ubuntu関係**
  * **Ubuntu24.04LTS移行**
  * **Ubuntu26.04LTS環境構築**
* **ドキュメント整備関係**
  * **Tipsページ充実**
  * **2026年度対応見直・修正**
  * **FAQページの充実、修正**
  * **エラーメッセージ一覧作成**

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
**※ 録音した語学講座のファイルは著作権法で許されている範囲内でご利用ください。**                 
***

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***

 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <link rel="shortcut icon" type="image/x-icon" href="https://raw.githubusercontent.com/CSReviser/CaptureStream2/master/icon.ico">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
