## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## Rosetta2 をインストールする手順
### Apple Silicon Mac用
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

**Apple Silicon（M1/M2/M3）搭載のMacでは、Intel向けのアプリを動作させるために Rosetta2 が必要です。**  
**標準ではインストールされていないため、以下の手順でインストールしてください。**

## 1. Rosetta 2 が必要なケース

**以下のような場合、Rosetta 2 のインストールが必要になります。**

- **Intel 向けに開発されたアプリ（x86_64バイナリ）を実行する場合**  
  - **例：Intel版の ffmpeg など***
  - **語学講座CS2（macOS版）に同梱されているのは Intel版の ffmpeg です。**
- **Universal アプリに含まれるコンポーネントの一部が Intel 版のみの場合**  
  - **例：語学講座CS2（macOS版）本体は Universal ですが、同梱の ffmpeg は Intel 版 のため、Apple Silicon Macでそのまま実行すると Rosetta2 が必要になります。**

### ✅ **解決策**
- **Rosetta 2 をインストールして Intel 版 ffmpeg を動かす**
- **Apple Silicon（ARM）版の ffmpeg を別途インストールする（Rosetta なしで実行可能）**

---

## 2. Rosetta 2 のインストール手順

### **方法 1：Intel アプリを開いたときに自動インストール**
**Intel 版のアプリを初めて開くと、以下のようなポップアップが表示されます。**

> **"Rosetta をインストールしますか？"**

**このダイアログで **「インストール」** をクリックすると、Rosetta 2 が自動的にインストールされます。**

### **方法 2：ターミナルから手動インストール**
**ターミナルを開き、以下のコマンドを実行すると、Rosetta 2 を手動でインストールできます。**

```sh
softwareupdate --install-rosetta --agree-to-license
```
**--agree-to-license を省略すると、インストール時にライセンス確認が求められます。**

---

### 3. Rosetta 2 を使って Intel 版アプリを実行する

**(1) ターミナルで Intel バイナリを実行**

**Intel 版の ffmpeg や他の x86_64 アプリを Rosetta 2 経由で実行するには、以下のように arch -x86_64 を付けて実行します。**
```sh
arch -x86_64 ffmpeg
```
**または、Intel 版のターミナルを開いて、その環境内で実行することもできます。**
```sh
arch -x86_64 /System/Applications/Utilities/Terminal.app/Contents/MacOS/Terminal
```

**この方法で開いたターミナルでは、すべてのコマンドが Rosetta 2 を介して Intel 版として動作します。**

**(2) Finder から Intel モードでアプリを開く**
**1. Finder で Intel 版アプリ を探す**
**2. アプリのアイコンを右クリック（または Control + クリック）**
**3.「情報を見る」 を選択**
**4.「Rosetta を使用して開く」 にチェックを入れる（このオプションがある場合）**
**5. アプリを再起動 して適用**

---

### 4. Apple Silicon 版 ffmpeg をインストールする方法（Rosetta なし）

**Rosetta2 を使わずに Apple Silicon ネイティブ版の ffmpeg を使いたい場合は、brew でインストールするのが簡単です。**

**Homebrew を使って Apple Silicon 版 ffmpeg をインストール**
**1. Homebrew をインストール（未インストールの場合）**
* **ターミナルで以下のコマンドを実行**
```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

**2. Apple Silicon 版 ffmpeg をインストール**
```sh
brew install ffmpeg
```

**3. 正しく Apple Silicon 版がインストールされたか確認**
```sh
file $(which ffmpeg)
```
**出力例（arm64 になっていればOK）**
```sh
/opt/homebrew/bin/ffmpeg: Mach-O 64-bit executable arm64
```


**メリット: Apple Silicon 版の ffmpeg は Rosetta 2 を使わずにネイティブで動作するため、高速でバッテリー消費も抑えられます。**

---

**まとめ**
* **CaptureStream2 本体は Universal 版 なので Rosetta 2 は不要**
* **同梱の ffmpeg は Intel 版 なので、そのまま実行するには Rosetta 2 が必要**
* **Rosetta 2 をインストールする方法**
* **Intel 版アプリを初めて開くと自動でインストール**
* **手動でターミナルから softwareupdate --install-rosetta を実行**
* **Apple Silicon 版 ffmpeg をインストールすれば Rosetta 2 なしで動作可能（brew install ffmpeg）**

**結論: Apple Silicon Mac で ffmpeg を使うなら、 ① Rosetta 2 をインストールする か、② Apple Silicon 版 ffmpeg を入れる のどちらかを選ぶのがベストです。**

---

#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">

