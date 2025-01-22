## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【Mac版インストール手順】　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
####  macOS版のインストール手順です。Macユーザーの[Twitterの投稿](https://twitter.com/Miiaaenglish/status/1515131329112858626?s=20&t=fKw38ZN5fkIG9q911hDAFw)の情報に基づいて作成しています。        
####  ※ 図内の「CS-English」と記載の部分は「CaptureStream2」と読み替えてください。             
####  [Windows版インストール手順はこちら](https://csreviser.github.io/CaptureStream2/install_win)


### 1. Macのシステム環境 > セキュリティとプライバシー > 一般タブの”ダウンロードしたアプリケーションの実行許可”を「App Storeと確認済みの…」に変更する                       
####    ![image](https://user-images.githubusercontent.com/46049273/169676247-6b198f17-0936-4c05-8d60-fa20df507929.png)

### 2. 語学講座CS２のMac版をダウンロード                    
####     [こちらのリリースノート（ブログ）](./#実行ファイル-1)からMacOS版をダウンロードしてください。2024/09/01現在トップページへの実行ファイルの掲載を見合わせています。[【MacOSユーザの方へ】](./macos)、[FAQ](./FAQ#macos)および[こちら](https://github.com/CSReviser/CaptureStream2/discussions/24#discussioncomment-10994101)も参照下さい。

### 3. ダウンロードしたdmgファイルをダブルクリック。           
   <img src="https://user-images.githubusercontent.com/46049273/169676318-0ee0598c-659b-4366-a58a-57693b4a2146.png" width="350"> 


####  開いたフォルダの中の「MacCaptureStream2」フォルダを更に開く
   <img src="https://user-images.githubusercontent.com/46049273/169676337-0d28d1db-df47-406d-ac20-60bffac6b152.png" width="350"> 


### 4. 「MacCaptureStream2」フォルダ中に「CaptureStream2.app」があるので、それを「~/Downloads」フォルダにコピー(移動)します。ターミナルアプリを開いて下記コマンドを入力します。「CaptureStream2.app」の部分は手入力に代えてマウスで「CaptureStream2.app」をターミナルアプリにドロップするとパスを含めて入力されます。

```
    cd ~/Downloads
    xattr -dr com.apple.quarantine CaptureStream2.app
    xattr -cr CaptureStream2.app
    codesign -s - CaptureStream2.app
```

###   「~/Downloads」内の「CaptureStream2.app」をアプリケーションフォルダにコピー(移動)する

### 5. アプリケーションフォルダに置いた「CaptureStream2.app」を開く。普通にクリックすると「開けません」と表示が出てしまうので、⌘押しながら右クリックから開くを選択する。          
### Sequoia(macOS15)では、設定>プライバシーとセキュリティのセキュリティに、ブロックされたアプリを開く項目が出現しているので「このまま開く」をクリックすることでインストールできるようになる。
### macOSのバージョンによって操作方法が異なるので、下記リンクでご使用のバージョンを選択して操作方法を確認して下さい。
* **[開発元が不明なMacアプリを開く(Apple Macユーザガイド)](https://support.apple.com/ja-jp/guide/mac-help/mh40616/mac)**
* **[アプリがMac App Storeから入手されていない場合(Apple Macユーザガイド)](https://support.apple.com/ja-jp/guide/mac-help/mh40620/mac)**        

              


   <img src="https://user-images.githubusercontent.com/46049273/169676481-8707c1b7-9fa1-45f6-a8ef-dc74b529cd01.png" width="350"> 

   <img src="https://user-images.githubusercontent.com/46049273/169676487-7c828631-34d1-4fae-913d-cbdca381f031.png" width="350"> 

### 6.アプリの初回起動時に保存フォルダを選択する画面が開きますので、自分が音声を保存したい書き込み可能なフォルダを指定する。保存フォルダは、カスタマイズ > 保存フォルダ設定から変更することができる。
   <img src="https://user-images.githubusercontent.com/46049273/169676522-675d76f5-df5e-4fe2-b8f7-14d9dbad39b1.png" width="350"> 

####  録音したい講座にチェックを入れて右下のレコーディングボタンを押す。          
   <img src="https://github.com/CSReviser/CaptureStream/assets/46049273/a27f1c9e-9a01-4fd6-baa7-d52d907525d2" width="350"> 
   
   <img src="https://user-images.githubusercontent.com/46049273/169676549-d258eee2-9442-4205-901f-1b8ede103708.png" width="350"> 


### ７．ffmpeg起動エラーが発生する場合は環境にあったffmpegを上記６で設定した保存フォルダに置くと改善される可能性があります。
   * **[【AppleSilicon版ffmpegインストール手順】](./install_mac_ffmpeg)**
   * **[Macintosh 64bit版バイナリ](https://evermeet.cx/ffmpeg/)**
   * **[MacOS Apple Silicon版バイナリ](https://www.osxexperts.net/)**
   * **ダウンロードしたファイルを展開して取り出したffmpegを「そのまま開く」には、次の手順に従います。**
   * **デスクトップ左上のアップルメニューから「システム環境設定」をクリックします。**
   * **「セキュリティとプライバシー」をクリックします。**
   * **画面下にある「ダウンロードしたアプリケーションの実行許可」から「そのまま開く」をクリックします。**


#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
