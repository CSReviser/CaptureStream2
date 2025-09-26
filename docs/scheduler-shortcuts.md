## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
### スケジュール録音の設定方法(macOS版：Automator＋カレンダー)　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
#### 　　　　　
#### **Automator＋カレンダーを使ったmacOS向けスケジュール録音の設定方法**
#### **GUIで簡単にスケジュール設定が可能**
#### 　　　　　

🧭 macOS 26以降：ShortcutsでCaptureStream2をスケジュール実行する手順

✅ 前提条件

• macOS 26 “Tahoe” 以降
• CaptureStream2.app が `/Applications` にインストール済み
• Shortcutsアプリがインストール済み（標準搭載）
• Gatekeeper制限を回避済み（署名済み or 初回起動済み）


---

🛠️ ステップ 1：ショートカットの作成

1. Shortcutsアプリを起動
2. 左側の「マイショートカット」から「＋」をクリックして新規作成
3. 名前を「CaptureStream2 スケジュール起動」などに設定
4. アクションを追加：• 検索バーに「シェルスクリプトを実行」と入力
• 「シェルスクリプトを実行」を選択

5. スクリプト欄に以下を入力：/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui

6. （任意）通知やログ保存などのアクションを追加可能


---

🕒 ステップ 2：パーソナルオートメーションの設定

1. Shortcutsアプリの左側メニューから「オートメーション」を選択
2. 「＋」をクリック → 「個人用オートメーションを作成」
3. トリガーを選択：• 「時刻」を選択
• 例：毎日 7:00 に実行
• 「繰り返し」→ 毎日／平日などを選択

4. 「次へ」をクリック
5. 「アクションを追加」→ 「ショートカットを実行」を選択
6. 先ほど作成した「CaptureStream2 スケジュール起動」を選択
7. 「次へ」→ 「実行前に尋ねる」をオフにする（自動実行のため）
8. 「完了」をクリック


---

✅ 動作確認と補足

• 設定した時刻になると、CaptureStream2がバックグラウンドで起動します。
• GUIを使わないため、ユーザーにはウィンドウ表示はされません。
• 初回実行時にGatekeeper警告が出る場合は、手動で一度起動して許可してください。


---



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

  **例1：基本的な実行（GUIなし）**

```sh
/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui
```

  **例2：保存先フォルダを指定（ミュージックアプリに自動同期）**
  * **＜ユーザー名＞は各自のユーザー名に変更してください**
  * **ミュージックappに自動同期します**
```sh
/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui -o "/Users/＜ユーザー名＞/Music/Music/Media.localized/Automatically Add to Music.localized"
```
  **※パスは語学講座CS2の実行ファイルの場所に応じて調整してください。Finderでアプリを右クリック→「パッケージの内容を表示」で確認できます。**

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
