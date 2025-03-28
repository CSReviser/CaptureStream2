## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## Mac版インストール手順
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
####  macOS版のインストール手順です。Macユーザーの[Twitterの投稿](https://twitter.com/Miiaaenglish/status/1515131329112858626?s=20&t=fKw38ZN5fkIG9q911hDAFw)の情報に基づいて作成しています。        
####  ※ 図内の「CS-English」と記載の部分は「CaptureStream2」と読み替えてください。             
####  [Windows版インストール手順はこちら](https://csreviser.github.io/CaptureStream2/install_win)


### 1. システム環境設定の調整
* **1. Appleメニューから「システム設定」 を開く。**
* **2. 「プライバシーとセキュリティ」を選択し、**  
   **「ダウンロードしたアプリケーションの実行許可」を**
   **「App Storeと確認済みの開発元からのアプリケーションを許可」に設定する。**           
   <img src="https://user-images.githubusercontent.com/46049273/169676247-6b198f17-0936-4c05-8d60-fa20df507929.png" width="350"> 


### 2. 語学講座CS２のMac版をダウンロード                    
* **1. [こちらのリリースノート（ブログ）](./#実行ファイル-1)からMacOS版をダウンロードする。**
   **現在トップページへの実行ファイルの掲載を見合わせ中。[【MacOSユーザの方へ】](./macos)、[FAQ](./FAQ#macos)および[こちら](https://github.com/CSReviser/CaptureStream2/discussions/24#discussioncomment-10994101)も参照。**


### 3. ダウンロードしたファイルの展開
* **1. ダウンロードした `.dmg`ファイルをダブルクリックしてマウントする。**           
   <img src="https://github.com/user-attachments/assets/d78b566e-c92c-4dd9-8cac-a7c9b2d243a8" width="350"> 


* **2. マウントされたディスクイメージ内の 「MacCaptureStream2」 フォルダを開く。**           
   <img src="https://github.com/user-attachments/assets/2bbc63d8-ef93-49b7-9d3f-10505eecfe7c" width="350"> 




### 4. アプリケーションの配置
* **1.「MacCaptureStream2」 フォルダ内の 「CaptureStream2.app」を**  
   **「アプリケーション」フォルダ にドラッグ＆ドロップしてコピーする。**

### 5. 初回起動とセキュリティ設定
* **1. 「アプリケーション」フォルダ 内の 「CaptureStream2.app」を**  
   **右クリック（または Controlキー + クリック）し 「開く」を選択する。**
* **2. 警告ダイアログが表示された場合、「開く」をクリックする。**
* **3. 必要に応じて、「システム設定」 → 「プライバシーとセキュリティ」にある** 
   **「ブロックされたアプリを開く」で 「このまま開く」 を選択する。**

   <img src="https://github.com/user-attachments/assets/1e92a517-6da8-4ed5-bba1-9fce0a45cb9b" width="200"> 

   <img src="https://github.com/user-attachments/assets/8e1abdff-030a-44ae-b9b8-8a9b2b3db59e" width="200"> 

* **macOSのバージョンによって操作方法が異なるので、下記リンクでご使用のバージョンを選択して操作方法を確認して下さい。**
* **[開発元が不明なMacアプリを開く(Apple Macユーザガイド)](https://support.apple.com/ja-jp/guide/mac-help/mh40616/mac)**
* **[アプリがMac App Storeから入手されていない場合(Apple Macユーザガイド)](https://support.apple.com/ja-jp/guide/mac-help/mh40620/mac)**        
* **[Macでインターネットまたはディスクからアプリをインストールする/アンインストールする(Apple Macユーザガイド)](https://support.apple.com/ja-jp/guide/mac-help/mh35835/mac)**
              


### 6. 保存フォルダの設定
* **1. 初回起動時に、音声ファイルの **保存先フォルダ** を選択するダイアログが表示されるので、**  
  **任意のフォルダを選択する。**
* **2. この設定は、アプリケーション内の 「カスタマイズ」メニューから後で変更可能**。

* **3. 録音したい講座にチェックを入れて右下のレコーディングボタンを押す。**         
   <img src="https://github.com/CSReviser/CaptureStream/assets/46049273/a27f1c9e-9a01-4fd6-baa7-d52d907525d2" width="200"> 
              


### 7. ffmpeg の設定（必要に応じて）
* **語学講座2 の録音機能には `ffmpeg` が必要です。インストールされていない場合、以下の手順で導入してください。**

* **1. 以下のいずれかのサイトから `ffmpeg` をダウンロードする。**
   - **[Macintosh 64bit版バイナリ](https://evermeet.cx/ffmpeg/)**
   - **[MacOS Apple Silicon版バイナリ](https://www.osxexperts.net/)**
* **2. ダウンロードした `ffmpeg` ファイルを、手順6で設定した保存フォルダに配置する。**
* **3. 配置後、`ffmpeg` ファイルを右クリックし「開く」を選択して実行許可を与える。**

   * **[Homebrew版ffmpegインストール手順](https://csreviser.github.io/CaptureStream2/install_mac_ffmpeg_homebrew)**
   * **[AppleSilicon版ffmpegインストール手順](./install_mac_ffmpeg)**

---

#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
