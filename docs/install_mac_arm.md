## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## Mac版インストール手順
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

## 🔹 Apple silicon向けGatekeeper 回避インストール手順

**CaptureStream2.app は dmgファイル（CaptureStream2-MacOS-arm-YYYYMMDD.dmg）内の「MacCaptureStream2」フォルダに格納 されています。**
**この手順では、dmgファイルからアプリを取り出し、Gatekeeper の警告を回避してインストールする方法 を説明します。**

**⚠️ CaptureStream2-MacOS-arm-YYYYMMDD.dmg の YYYYMMDD の部分はバージョンごとに異なるため、実際のファイル名に置き換えてください。**

**⚠️ アプリのインストール先（/Applications など）も環境に応じて適宜変更してください。**

---

## 🟢 手順

### ① dmg ファイルをマウント

**まず、ダウンロードフォルダにある CaptureStream2-MacOS-arm-YYYYMMDD.dmg をマウントします。**
```sh
hdiutil attach ~/Downloads/CaptureStream2-MacOS-arm-YYYYMMDD.dmg
```
**✅ ⚠️ YYYYMMDD の部分は、実際の dmg ファイルのバージョンに置き換えてください。**

**✅ これにより、dmg 内のファイルが Finder に 「MacCaptureStream2」 というボリューム名でマウントされます。**

---

### ② CaptureStream2.app を取り出してインストール

**📌 例: /Applications にインストールする場合（管理者権限が必要）**
```sh
sudo cp -R /Volumes/MacCaptureStream2/CaptureStream2.app /Applications/
```

**📌 例: ユーザー専用の ~/Applications/ にインストールする場合（sudo 不要）**
```sh
cp -R /Volumes/MacCaptureStream2/CaptureStream2.app ~/Applications/
```
**✅ ⚠️ /Applications の部分はインストール先に応じて変更してください。**

---

### ③ dmg ファイルをアンマウント
```sh
hdiutil detach /Volumes/MacCaptureStream2
```
**✅ これで dmg ファイル内のデータは不要になり、安全にアンマウントできます。**

---

### ④ Gatekeeper の隔離属性を削除
```sh
sudo xattr -dr com.apple.quarantine /Applications/CaptureStream2.app
```
**📌 /Applications の部分はインストール先に応じて変更してください。**

**✅ これにより、アプリがダウンロード済みの警告を受けなくなります。**

---

### ⑤ 実行権限を付与
```sh
sudo chmod -R +x /Applications/CaptureStream2.app
```

**📌 /Applications の部分はインストール先に応じて変更してください。**

**✅ .app 内のバイナリが適切に実行できるようになります。**

---

### ⑥ Gatekeeper のブロックを解除
```sh
sudo spctl --add --label "CaptureStream2" /Applications/CaptureStream2.app
sudo spctl --enable --label "CaptureStream2"
```
**📌 /Applications の部分はインストール先に応じて変更してください。**

**✅ Gatekeeper に「このアプリは安全」と登録し、実行を許可します。**

---

### ⑦（必要なら）自己署名

**もし spctl の設定後もアプリが開けない場合、以下のコマンドで自己署名を適用してください：**
```sh
sudo codesign --force --deep --sign - /Applications/CaptureStream2.app
```
**📌 /Applications の部分はインストール先に応じて変更してください。**

**✅ これにより、Gatekeeper が「署名済みアプリ」と認識し、制限を回避できます。**

---

### 🔹 まとめ
#### 手順一覧
<style>
.tablelines table, .tablelines td, .tablelines th {
        border: 1px solid black;
        }
</style>
| **手順** | **コマンド（インストール先に応じて変更）** |
|---|---|
| **1. dmg ファイルをマウント** | `hdiutil attach ~/Downloads/CaptureStream2-MacOS-arm-YYYYMMDD.dmg` |
| **2. アプリをインストール** | `sudo cp -R /Volumes/MacCaptureStream2/CaptureStream2.app /Applications/` |
| **3. dmg ファイルをアンマウント** | `hdiutil detach /Volumes/MacCaptureStream2` |
| **4. 隔離属性を削除** | `sudo xattr -dr com.apple.quarantine /Applications/CaptureStream2.app` |
| **5. 実行権限を付与** | `sudo chmod -R +x /Applications/CaptureStream2.app` |
| **6. Gatekeeper の例外登録** | `sudo spctl --add --label "CaptureStream2" /Applications/CaptureStream2.app` |
| **7. （必要なら）自己署名** | `sudo codesign --force --deep --sign - /Applications/CaptureStream2.app` |
{: .tablelines}

#### 注意事項

- **`YYYYMMDD` はバージョンごとに異なるため、実際の dmg ファイル名に置き換えてください。**
- **`/Applications` の部分は、インストール先に応じて変更してください。**
- **語学講座CS2は悪意あるコードを含みませんが、信頼できるアプリであることを確認したうえで実行してください。**


---

**⚠️ Gatekeeper 警告を回避するリスクについて**

**Gatekeeper は、Apple が未確認のアプリの実行を防ぐことで マルウェアや悪意のあるソフトウェアのリスクを低減する仕組み です。これを手動で回避することには、以下のような リスク が伴います。**

**🔸 1. マルウェア感染のリスク**
	• **未署名のアプリは Apple の審査を受けていないため、悪意のあるコードが含まれる可能性があります。**
	• **公式サイトや信頼できるソースからアプリをダウンロードしているか 慎重に確認 してください。**

**🔸 2. システムの安全性低下**
	• **xattr や spctl コマンドを実行することで Apple のセキュリティ対策を一部無効化 することになります。**
	• **これは 信頼できるアプリ にのみ適用し、むやみに実行しないようにしてください。**

**🔸 3. 自動アップデートの問題**
	• **署名なしのアプリは、自動アップデート機能が 正しく動作しない可能性 があります。**
	• **手動でのアップデートが必要になる場合があります。**

**🔸 4. macOS アップデート後に再設定が必要**
	• **macOS のメジャーアップデート後、Gatekeeper の設定がリセットされることがあり、再度 spctl や codesign の設定が必要になる可能性 があります。**

---

**🟠 安全に Gatekeeper を回避するためのポイント**

**✅ 1. アプリのダウンロード元を確認**
	•	**公式サイト、信頼できる開発元から入手することを徹底。**


**✅ 2. 必要最小限の変更を行う**
	•	**xattr のみで解決するなら spctl や codesign は実行しない。**
	•	**spctl の例外設定をする前に、Finder の「右クリック → 開く」で試す のも安全な方法。**

**✅ 3. 影響を最小限にするため、できるだけ ~/Applications/ を使う**
	•	**~/Applications/ にインストールすれば sudo 不要 で、システム全体の設定変更を避けられる。**

---

**✅ この手順を実行する前に、リスクを理解し、信頼できるアプリであることを確認してください。**


---

#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">

