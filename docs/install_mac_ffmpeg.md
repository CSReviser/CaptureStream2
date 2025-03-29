## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## AppleSilicon版ffmpegインストール手順　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

### 🚀 Apple Silicon (M シリーズ) 用 ffmpeg を手動インストールする方法

**語学講座 CS2 の動作には `ffmpeg` が必要です。**
**同梱の ffmpeg はApple Silicon機では Rosetta2 のインストールが必要です。Rosetta2 をインストールしない場合には**
**以下の手順で `ffmpeg` を手動インストールしてください。**
**この手順は Homebrew を使わない手順です。Homebrewを使う場合は [Homebrew の手順](./install_mac_ffmpeg_homebrew)を参照してください。**

---

## **1️⃣ ffmpeg をダウンロード**  
**以下のサイトから Apple Silicon (M1/M2) 用の `ffmpeg` バイナリ (ZIP ファイル) をダウンロードしてください。**

🔗 **[OSXExperts.NET](http://www.osxexperts.net/)**  

---

## **2️⃣ ZIP ファイルを展開**  

**ダウンロードした ZIP ファイルを Finder で開いて展開してください。**
**または、以下のコマンドでターミナルから展開できます。**

```sh
unzip ~/Downloads/ffmpeg.zip -d ~/Downloads/
```

---

## **3️⃣ Gatekeeper の制限を解除**

**macOS はインターネットからダウンロードしたアプリを制限するため、以下のコマンドを実行して Gatekeeper の制限を解除してください。**
```sh
cd ~/Downloads
xattr -dr com.apple.quarantine ffmpeg
codesign -s - ffmpeg
```

---

## **4️⃣ ffmpeg を適切なフォルダに移動**

**ディレクトリ /usr/local/bin を作成し、そこに ffmpeg を配置します。**
```sh
sudo mkdir -p /usr/local/bin
sudo mv ffmpeg /usr/local/bin/ffmpeg
sudo chmod +x /usr/local/bin/ffmpeg
```
**Apple Silicon (M1/M2) の Mac では、Homebrew が /opt/homebrew/bin/ を使用するため、Homebrewと同じ場所に配置する場合は以下のようにします。**
```sh
sudo mv ffmpeg /opt/homebrew/bin/ffmpeg
sudo chmod +x /opt/homebrew/bin/ffmpeg
```

**また、ffmpeg を PATH に追加するため、以下のコマンドを実行してください。**
```sh
echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

---

## **5️⃣ ffmpeg のインストール確認**

**以下のコマンドで ffmpeg が正しくインストールされているか確認できます。**
```sh
ffmpeg -version
```

**ffmpeg のバージョン情報が表示されれば、インストール成功です。**

---

### **🔧 ffmpeg のパス設定**

## **✅ CaptureStream2 の設定方法**

*　**「/usr/local/bin/」に ffmpeg をインストールした場合:**
* **カスタマイズ > ffmpegパス設定 > 設定する で 「/usr/local/bin/」 を指定してください。**
* **最新版の語学講座CS2を使用する場合、この設定は不要です。**
* **ffmpegパス設定を行わない（初期値）場合:**
* **カスタマイズ > 保存フォルダ設定 で設定したフォルダに ffmpeg を保存すると、そちらが優先して使われます。**

---

### 📌 公式の手順について

**macOS のバージョンによってセキュリティ設定が異なるため、公式の手順も参考にしてください。**

🔗 **[開発元が不明な Mac アプリを開く（Apple Mac ユーザガイド）](https://support.apple.com/ja-jp/guide/mac-help/mh40616/mac)**

---

### **✅ これで ffmpeg のインストールは完了です！🎉**





**【参考サイト】**
* **[Apple M1でffmpegを入れる](https://zenn.dev/esaka/scraps/bb29de3b30fc13)**
* **[FFmpegのARM（AppleSilicon）版の6（バイナリ）が配布開始されています。](https://bobsmac.com/news/4572.html)**
* **[ffmpeg on apple silicon(windows cudaも) ](https://note.com/jydie5/n/na047e08003a1)**
* **[ARM版CPUのM1 MACにてffmpegのh265ソフトウェアエンコードを高速化する方法](https://qiita.com/username37/items/7adfe9fd22d9fd8b265b)**


####   　
####   　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
-
