## 語学講座CS2    
## [ブログ (お知らせ、他)](https://csreviser.github.io/CS2-blog/)  [［X：旧twitter］](https://twitter.com/CSReviser) 
## [NHKゴガク](https://www.nhk.jp/g/gogaku/) 　[Learn Japanese](https://www3.nhk.or.jp/nhkworld/en/learnjapanese/)
## [［類似アプリ］](./application)                          
* **一部のAI検索サービス（Google AI等）において、[類似アプリ](./application)と『語学講座CS2』を混同する誤情報が拡散しています。各アプリは開発元が異なります。[類似アプリ](./application)については各提供元にお問い合わせください。**        

#### 語学講座CS2は、NHKラジオ語学講座の「らじる★らじる」（聴き逃し）ストリーミング配信を自動録音するためのデスクトップアプリです。録音した語学講座のファイルは、著作権法で認められた範囲内でご利用ください。                
* **現在の最新版は2025/06/08版です。Linux向け実行ファイルを追加しています。開発環境はQt6.9を使っています。[QtとOSの対応はこちらで確認できます。](./Qt_vs_OS)**
* **コマンドラインで-noguiオプション、番組IDを指定すると前週分のサムネが不正となる不具合を確認しています。GUIではこの問題は発生しません。**
* **GitHubのmacos-26ベータ環境でのビルドテスト版をリリースしました。Mac／macOS関連情報提供を継続お待ちしています。**
  
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


### [2025/06/08版リリースノート（ブログ）](https://csreviser.github.io/CS2-blog/2025/06/08/)
### Windows用
* ### **[CaptureStream2-Windows-x64-20250608.zip 【64bit版】](https://github.com/CSReviser/CaptureStream2/releases/download/20250608/CaptureStream2-Windows-x64-20250608.zip)**
* ### **[CaptureStream2-Windows-x86-20250608.zip 【32bit版】](https://github.com/CSReviser/CaptureStream2/releases/download/20250416/CaptureStream2-Windows-x64-20250608.zip)**
> ⚠️ ご注意：本ソフトウェアはデジタル署名されていないため、Windows 11の「スマート アプリ コントロール（Smart App Control）」が有効な環境では実行できない場合があります。  
> Smart App Controlが有効なPCでは、署名付きのアプリケーションのみが許可されます。詳細はMicrosoftの公式ドキュメントをご参照ください。

### Linux用（参考公開）
* ### **[CaptureStream2-AppImage-x64-20250608.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20250608/CaptureStream2-AppImage-x64-20250608.zip)**
* ### **[CaptureStream2-AppImage-arm64-20250608.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20250608/CaptureStream2-AppImage-arm64-20250608.zip)**
  ##### ※このサイトで提供している実行ファイルが動作しないときはご自身でビルドをお試しください。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。
  ##### **※ Appimage版はfuseなど追加モジュールのinstallが必要な場合があります。**
  ##### **※ Linux OSにWINEをinstallしてWindows版を使うという方法もあります。**

### Ubuntu用（参考公開）
* ### **[CaptureStream2-Ubuntu-20250608.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20250608/CaptureStream2-ubuntu-20250608.zip)**
  ##### ※このサイトで提供している実行ファイルが動作しないときはご自身でビルドをお試しください。Ubuntuでのビルド手順は[こちら](./install_linux)を参考にしてください。

### MacOS用 [【MacOSユーザの方へ】](https://csreviser.github.io/CaptureStream2/macos)
* **[【MacOSユーザの方へ】](./macos)、[FAQ](./FAQ#macos)および[【必要要件】](./requirements)をご確認頂き、リスクをご理解の上で自己解決できる方、動作確認にご協力頂ける方はご利用ください。**
* ### **[CaptureStream2-MacOS-20250608.dmg](https://github.com/CSReviser/CaptureStream2/releases/download/20250608/CaptureStream2-MacOS-20250608.dmg)**
  * **Macユーザー間の情報交換の場として[こちらに【macOS関係の情報交換】](https://github.com/CSReviser/CaptureStream2/discussions/24)を作成しました。**

### ※バグ報告などは[こちら](https://github.com/CSReviser/CaptureStream2/discussions/32)に投稿してください。
#### 　　　　　　

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 
***
### ＜style sheet＞
* **[stylesheet変更例(講座ボタン色変更)](./stylesheet)**


### Windows用
* ### **[stylesheet-win.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20250608/stylesheet-win.zip)**


### Linux / Ubuntu用
* ### **[stylesheet-ubu.zip](https://github.com/CSReviser/CaptureStream2/releases/download/20250608/stylesheet-ubu.zip)**



#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜開発テスト版＞
* **[2025/06/08(macos-15、26)テスト版](./test_release)**


#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜語学講座CS2 イメージ＞
#### ［Windows版］
<img src="https://github.com/user-attachments/assets/09853647-953d-4a62-a3b2-18838afb51ad" width="350"> 

#### ［Ubuntu版］
<img src="https://github.com/user-attachments/assets/c6497566-8d98-401f-894a-47bbafc17703" width="350"> 

#### ［macOS版］
<img src="https://github.com/CSReviser/CaptureStream/assets/46049273/a27f1c9e-9a01-4fd6-baa7-d52d907525d2" width="350"> 

##### **※macOS版のイメージ写真はyarakaoriさんから提供いただきました。**

#### ［　[ＴＯＰ](./)　**｜**　[目次](./#目次)　] 

***
### ＜既知課題＞         
**※ 2025/10/04現在、-noguiで番組IDを指定すると前週分のサムネが不正となる不具合を確認しています。**

### 次回リリース時適用予定：
* **Qt6.10対応**
* **macos-15、26テスト版ビルド**
* **-nogui,-z,番組IDでサムネ不正修正**
* **高校講座関連修正**

### 2026年度情報：
* **[2026年度放送番組編成計画](https://www.nhk.or.jp/info/pr/hensei/assets/pdf/2026_kokunai.pdf)**
* **[2026年度前半期 放送番組時刻表](https://www.nhk.or.jp/info/pr/hensei/assets/pdf/2026_jikokuhyo-kokunai.pdf)** 
* **[2026年度ラジオ語学番組表](https://www.nhk.jp/g/gogaku/blog/l7_dfp1vm4y/)**     
* **[2026年春〜NHKラジオが変わります](https://www.nhk.or.jp/radio/saihen/)**      
### 終了番組：
* **アラビア語講座**
* **やさしい日本語**
* **Living in Japan**
* **Asian View(HPへ)**
* **○○○語ニュース**


### 2026年02月中旬：
* **[NHK出版 春の企画説明](https://shoten-pr.nhk-book.co.jp)**
* **[2026年度放送番組編成計画](https://www.nhk.or.jp/info/pr/hensei/)**
* **[Qt6.10.2環境構築](https://wiki.qt.io/Qt_6.10_Release)** 

### 2026年02月下旬：
* **Qt6.10.2テスト版リリース**      

### 2026年03月中旬：
* **[Qt6.10.3リリース予定](https://wiki.qt.io/Qt_6.10_Release)**
* **[Qt6.11リリース予定](https://wiki.qt.io/Qt_6.11_Release)**

### 2026年03月20日：
* **[特番:ラジオ英会話　英語のお悩み解決！　春スペシャル　２０２６](https://www.nhk.jp/p/rs/PMMJ59J6N2/blog/bl/py8k1qdJV3/bp/pABKkJg1BV/)**

### 2026年03月30日：
* **2026年度ラジオ語学講座開始(FM放送)**
* **NHK AM放送波一波化**

### 2026年10月13日：
* **[Windows10個人向けESU終了](https://www.microsoft.com/ja-jp/windows/extended-security-updates)**

### 2028年10月：
* **Windows10のESU（拡張セキュリティ更新）終了**


### 日程未定：
* **全OS共通**
  * **Qt6.10環境構築**
  * **高校講座関連修正**
  * **低ビットレートmp3の2ch化検討**
  * **ffmpeg同梱中止検討**
  * **[前週］機能削除**
  * **エラーチェック強化（見直)**
  * **GUI/CUI分離検討**
  * **GitHub actionsでのテスト環境構築**
  * **Qt5実行ファイル作成終了**
* **Windows関係**
  * **32bit版(Windows版)終了検討**
* **Linux関係**
  * **install手順(Appimage版)作成**
  * **WINEを使うinstall手順作成**
  * **docker image作成検討**
  * **Wayland環境対応検討**
  * **日本語入力(番組名での任意番組設定)**
  * **systemd利用自動実行手順作成**
* **ubuntu関係**
  * **Ubuntu24.04LTS移行**
* **macOS関係**
  * **macos-15又は26移行**
  * **Homebrew tap試行中**
  * **実行ファイルTopページ掲載再検討**
  * **ノッチありMac暫定対策削除(Qt対応済)**
  * **Intelサポート終了(Apple)対応**
  * **バイナリ作成終了**
* **ドキュメント整備関係**
  * **Tipsページ充実**
  * **Smart App Control回避策**
  * **gatekeeper回避策**
  * **2025年度対応見直・修正**
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
