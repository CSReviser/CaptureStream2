## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
### スケジュール録音の設定方法(macOS版：crontab)　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
#### 　　　　　
#### **crontabを使ったスケジュール録音の設定方法です。**
#### **Appleはcrontabを非推奨（deprecated）としており、代わりにlaunchd（macOSのネイティブなタスクスケジューラー）を使用することを推奨しています。このcrontabの手順を参考にlaunchdを使った設定をしてください。**
####

#### 1. cronにFull Disk Access権限を付与（必須）
macOSのセキュリティでcronが制限されるため、以下の手順で権限を有効化。
	* **システム設定を開く: Appleメニュー > システム設定（旧: システム環境設定）。**
	* **プライバシーとセキュリティへ移動: 左サイドバーから「プライバシーとセキュリティ」を選択。**
	* **Full Disk Accessを選択: 左側のリストから「Full Disk Access」をクリック（鍵アイコンをクリックして管理者パスワード入力）。**
	* **cronを追加:**
	* **右下の「+」ボタンをクリック。**
	* **Finderで /usr/sbin/cron を選択（隠しファイル表示が必要ならCommand + Shift + .）。**
	* **cronがリストに追加されたら、チェックボックスをオンに。**
	* **再起動またはログアウト: 変更を適用するため、Macを再起動するかログアウト/ログイン。**


　　
#### 1. ターミナルを開きます。
   •  ターミナルを開く: Command + Space でSpotlightを起動し、「ターミナル」と入力してEnter。
#### ２. ターミナルが開いたら『crontab -e』と入力し、Enterキーを押します。
crontab -e

　　　![image](https://user-images.githubusercontent.com/46049273/210122453-56e2a086-2bc7-4a40-92a4-1f6cbfa023f0.png)
#### 3. エディタは『vi』を使用します。最終行にカーソルを移動し、例えば下記のように入力します。

	•  これでデフォルトのエディタ（通常vi）が開きます。空のファイルが表示される場合があります。
	•  例: 毎分テストスクリプトを実行する場合、以下の行を追加（iキーで挿入モード、Escで終了、:wqで保存）。

* * * * * /path/to/your/script.sh

	•  保存後、crontab -l で内容を確認。

　　　![image](https://user-images.githubusercontent.com/46049273/210123561-cc898d06-60aa-4122-ac9b-1df1b8d3f78b.png)
#### 　　この例では毎日10時5分に実行されます。   　　
#### 　　　　
#### ＜起動時に実行させる例＞   
　　　![image](https://user-images.githubusercontent.com/46049273/210123642-a3dc7da6-30aa-4c16-a432-a91f7b48e290.png)
#### 　　　　
#### ＜Wineを使ったWindows版の例＞   
　　　![image](https://user-images.githubusercontent.com/46049273/210123585-00434e2f-592a-4fe0-a458-a244a7d4127a.png)
#### 　　　　
#### ＜Wineを使ったWindows版を起動時に実行させる例＞   
　　　![image](https://user-images.githubusercontent.com/46049273/210123678-40b661b8-2c1b-4c00-831f-6b8d2ea3488d.png)
   
#### 4. 変更内容を保存します。『Ctrl+O』と入力後、Enterキーを押します。  
![image](https://user-images.githubusercontent.com/46049273/210122479-eb459b72-f6e8-4e95-9457-18a17516a870.png)

#### 4. nanoを終了します。『Ctrl+X』と入力します。
#### 　　　　　
#### 　　　　　
#### 　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
