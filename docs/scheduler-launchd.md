## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
### スケジュール録音の設定方法(macOS版：launchd)　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
#### 　　　　　
#### **launchdを使ったmacOS向けスケジュール録音の設定方法です。**
#### **「launchd」はmacOSネイティブのタスクスケジューラーで、Appleはcrontabの代替として使用を推奨しています。**
#### 　　　　　

#### 📁 1. 実行したいアプリやスクリプトを準備

**例：CaptureStream2をGUIなしで起動する**


```sh
/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui
```

---
#### 📝 2. 設定ファイル（*.plist）を作成

**以下の内容を `com.example.capturestream2.plist` という名前で保存します。**

```sh
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
```


🧠 **補足：**

* **`RunAtLoad`: Mac起動時やログイン時に実行**  
* **`StartInterval`: 秒単位で繰り返し実行（例：3600秒＝1時間）**  
* **`StartCalendarInterval`: 特定の時刻に実行したい場合はこちらを使う**  


---

#### 📂 3. 設定ファイルを配置

```sh
mkdir -p ~/Library/LaunchAgents
cp com.example.capturestream2.plist ~/Library/LaunchAgents/
```

---

#### 🔐 4. 権限を確認・修正（必要に応じて）

```sh
chmod 644 ~/Library/LaunchAgents/com.example.capturestream2.plist
```

---

#### 🚀 5. launchdに登録して起動

```sh
launchctl load ~/Library/LaunchAgents/com.example.capturestream2.plist
```


📌 **登録済みか確認：**

```sh
launchctl list | grep capturestream2
```

---

#### 🛑 6. 停止・削除したい場合

```sh
launchctl unload ~/Library/LaunchAgents/com.example.capturestream2.plist
```

---

* **録音対象講座などは、あらかじめGUIで設定が必要です。**




#### 　　　　　
#### 　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
