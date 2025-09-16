## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
### スケジュール録音の設定方法(macOS版：launchd)　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
#### 　　　　　
#### **launchdを使ったmacOSむけスケジュール録音の設定方法です。**
#### **「launchd」はmacOSネイティブのタスクスケジューラー「launchd」でAppleはcrontabの代替として使用を推奨しています。**
#### 　　　　　

#### 📁 1. 実行したいアプリやスクリプトを準備

例：CaptureStream2をGUIなしで起動する


```sh
/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui
```


📝 2. 設定ファイル（*.plist）を作成

以下の内容を `com.example.capturestream2.plist` という名前で保存します。

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"
  "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
  <dict>
    <key>Label</key>
    <string>com.example.capturestream2</string>

    <key>ProgramArguments</key>
    <array>
      <string>/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2</string>
      <string>-nogui</string>
    </array>

    <key>RunAtLoad</key>
    <true/>

    <key>StartInterval</key>
    <integer>3600</integer> <!-- 例: 1時間ごとに実行 -->
  </dict>
</plist>


🧠 補足：

• `RunAtLoad`: Mac起動時やログイン時に実行
• `StartInterval`: 秒単位で繰り返し実行（例：3600秒＝1時間）
• `StartCalendarInterval`: 特定の時刻に実行したい場合はこちらを使う


---

📂 3. 設定ファイルを配置

mkdir -p ~/Library/LaunchAgents
cp com.example.capturestream2.plist ~/Library/LaunchAgents/


---

🔐 4. 権限を確認・修正（必要に応じて）

chmod 644 ~/Library/LaunchAgents/com.example.capturestream2.plist


---

🚀 5. launchdに登録して起動

launchctl load ~/Library/LaunchAgents/com.example.capturestream2.plist


📌 登録済みか確認：

launchctl list | grep capturestream2


---

🛑 6. 停止・削除したい場合

launchctl unload ~/Library/LaunchAgents/com.example.capturestream2.plist







1. cronにFull Disk Access権限を付与（必須）
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

* **これでデフォルトのエディタ（通常vi）が開きます。空のファイルが表示される場合があります。**


#### ４. エディタは『vi』を使用します。最終行にカーソルを移動し、例えば下記のように入力します。
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
