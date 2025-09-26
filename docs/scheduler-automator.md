## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
### スケジュール録音の設定方法(macOS版：Automator＋カレンダー)　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
#### 　　　　　
#### **Automator＋カレンダーを使ったmacOS向けスケジュール録音の設定方法**
#### **GUIで簡単にスケジュール設定が可能**
#### 　　　　　


#### 🛠 Automator＋カレンダーで語学講座CS2を定期実行する手順

✅ 前提条件

* **語学講座CS2(CaptureStream2)がインストール済み**
* **macOS上でAutomatorとカレンダーが利用可能**


---

#### 🧩 ステップ①：Automatorで実行アプリを作成

**1. Automatorを起動**   
  * **Launchpad → Automator を開く**
  * **または、Spotlight検索（⌘ + スペース）で「Automator」と入力して起動**


**2. 新規書類を作成**   
  * **  「新規書類」をクリックし、書類の種類として「アプリケーション」を選択して「選択」をクリック**.   


**3. 「シェルスクリプトを実行」アクションを追加**   
  * **左側の「ライブラリ」→「ユーティリティ」→「シェルスクリプトを実行」をダブルクリック**
 
**4. 以下のようなコマンドを入力（例）**  
  * **以下のコマンドを入力して、CaptureStream2をGUIなしで実行**

  **例：基本的な実行（GUIなし）**

```sh
/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui
```

**5. ファイルを保存**
  * **⌘+Sで保存。名前は「CaptureStream2自動実行」などわかりやすく。保存場所は「アプリケーション」フォルダがおすすめ。**


---

#### 📅 ステップ②：カレンダーで定期実行を設定

**1. カレンダーを起動**
  * **Launchpad → カレンダー を開く**
  * **または、Spotlight検索（⌘ + スペース）で「カレンダー」と入力して起動**

**2. 新しいイベントを作成**
  * **実行したい日時にダブルクリック → イベント名を「CaptureStream2実行」などに変更**

**3. 「通知」を設定**
  * **「通知」→「カスタム」→「ファイルを開く」→先ほど保存したAutomatorアプリを選択**

**4. 繰り返し設定**
  * **「繰り返し」→「毎日」「毎週」「毎月」など、希望の頻度を選択**


---

#### 🎯 実行確認と注意点

* **イベントの時間になると、Automatorアプリが起動し、CaptureStream2が-noguiオプションで実行されます。**
* **GUIが起動しないため、バックグラウンドで動作します。**

---

* **録音対象講座などは、あらかじめGUIで設定が必要です。**




#### 　　　　　
#### 　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
