## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
### スケジュール録音の設定方法(macOS版：crontab)　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
#### 　　　　　
#### **crontabを使ったスケジュール録音の設定方法です。macOSはUNIXなのでLinuxと同様にcrontabが使えます。**
#### **Appleはcrontabの使用を推奨しておらず、代替としてmacOSネイティブのタスクスケジューラー「launchd」の使用が推奨されています。このcrontabの手順を参考にlaunchdを使った設定をしてください。**
#### 　　　　　

#### 1. cronにFull Disk Access権限を付与（必須）
**macOSのセキュリティでcronが制限されるため、以下の手順で権限を有効化。**

* **システム設定を開く: Appleメニュー > システム設定（旧: システム環境設定）。**
* **プライバシーとセキュリティへ移動: 左サイドバーから「プライバシーとセキュリティ」を選択。**
* **Full Disk Accessを選択: 左側のリストから「Full Disk Access」をクリック（鍵アイコンをクリックして管理者パスワード入力）。**
* **cronバイナリを追加:**
* **右下の「+」ボタンをクリック。**
* **Finderで /usr/sbin/cron を選択（/usr/sbin は通常表示されないため、Command + Shift + . で隠しファイルを表示）。**
* **cronがリストに追加されたら、チェックボックスをオンに。**
* **再起動またはログアウト: 変更を適用するため、Macを再起動するかログアウト/ログイン。**


　　
#### ２. ターミナルを開きます。
* **ターミナルを開く: Command + Space でSpotlightを起動し、「ターミナル」と入力してEnter。**
#### ３. ターミナルが開いたら『crontab -e』と入力し、Enterキーを押します。
* **初回はエディタ選択画面が表示される場合があります**

```sh
$ crontab -e
```

#### ４. エディタは『vi』を使用します。最終行にカーソルを移動し、例えば下記のように入力します。

* **これでデフォルトのエディタ（通常vi）が開きます。空のファイルが表示される場合があります。**
* **例: 毎分テストスクリプトを実行する場合、以下の行を追加（iキーで挿入モード、Escで終了、:wqで保存、Esc → :wq → Enter で保存して終了）。**


```sh
* * * * * /Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui
```

* **保存後、crontab -l で内容を確認。**
```sh
$ crontab -l
```

```sh
5 10 * * * /Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui
```

#### 　　この例では毎日10時5分に実行されます。 
 　　

* **録音対象講座などは、あらかじめGUIで設定が必要です。**
* **crontabの設定方法は Linuxの手順も参考にしてください。**
* **crontabはmacOSでは制限が多いため、安定したスケジュール実行にはlaunchdの使用を推奨します。**　　　　
#### 　　　　　
#### 　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
