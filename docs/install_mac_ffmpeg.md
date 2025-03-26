## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
## 【AppleSilicon版ffmpegインストール手順】　　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

# 🚀 Homebrew を使わずに Apple Silicon (M シリーズ) 用 ffmpeg を手動インストールする方法

語学講座 CS2 の動作には `ffmpeg` が必要です。以下の手順で `ffmpeg` を手動インストールしてください。

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

cd ~/Downloads
xattr -dr com.apple.quarantine ffmpeg
codesign -s - ffmpeg


---

## **4️⃣ ffmpeg を適切なフォルダに移動**

**Homebrew とは無関係な独立したディレクトリ /usr/local/bin/ffmpeg を作成し、そこに ffmpeg を配置します。**

sudo mkdir -p /usr/local/bin
sudo mv ffmpeg /usr/local/bin/ffmpeg
sudo chmod +x /usr/local/bin/ffmpeg

**また、ffmpeg を PATH に追加するため、以下のコマンドを実行してください。**

echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc

---

## **5️⃣ ffmpeg のインストール確認**

**以下のコマンドで ffmpeg が正しくインストールされているか確認できます。**

ffmpeg -version

**ffmpeg のバージョン情報が表示されれば、インストール成功です。**

---

### **🔧 ffmpeg のパス設定**

## **✅ CaptureStream2 の設定方法**
	•	「/opt/ffmpeg/bin/」に ffmpeg をインストールした場合:
	•	カスタマイズ > ffmpegパス設定 > 設定する で 「/opt/ffmpeg/bin/」 を指定してください。
	•	テスト版を使用する場合:
	•	この設定は不要です。
	•	テスト版ダウンロードはこちら
	•	ffmpegパス設定を行わない（初期値）場合:
	•	カスタマイズ > 保存フォルダ設定 で設定したフォルダに ffmpeg を保存してください。
	•	テスト版では初期設定で「/opt/ffmpeg/bin/」の ffmpeg が使用されます。

⸻

### 📌 公式の手順について

**macOS のバージョンによってセキュリティ設定が異なるため、公式の手順も参考にしてください。**

🔗 **[開発元が不明な Mac アプリを開く（Apple Mac ユーザガイド）](https://support.apple.com/ja-jp/guide/mac-help/mh40616/mac)**

---

### **✅ これで ffmpeg のインストールは完了です！🎉**


**AppleSilicon(Mシリーズ)用のffmpegをインストールする手順です。**

### １．[こちらのサイト](http://www.osxexperts.net/)からffmpeg(AppleSilicon)のzipファイルをダウンロードしてffmpegを取り出します。
* **[OSXExperts.NET](http://www.osxexperts.net/)**



### ２．**端末（ターミナル）から以下のコマンドを実行します。**     

```
    cd [ffmpegを展開したフォルダを指定します] 
    xattr -dr com.apple.quarantine ffmpeg 
    xattr -cr ffmpeg
    codesign -s - ffmpeg
    sudo mv ffmpeg /usr/local/bin/ffmpeg
```
* **「/usr/local/bin/」がffmpegの存先フォルダになります。**
* **カスタマイズ　＞　ffmpegパス設定　＞　設定する　で「/usr/local/bin/」を設定します。テスト版を使う場合はこの設定は必要ありません。 [テスト版ダウンロードはこちら](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-MacOS-20241007-1.dmg)**
* **ffmpegパス設定　で設定しない（初期値）の場合は　　カスタマイズ　＞　保存フォルダ設定　で設定したフォルダにffmpegを保存します。テスト版を使う場合は初期値で「/usr/local/bin」のffmpegが使われます。 [テスト版ダウンロードはこちら](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-MacOS-20241007-1.dmg)**

**公式の手順はmacOSのバージョンによって操作方法が異なるので、下記リンクでご使用のバージョンを選択して操作方法を確認して下さい。**  

**[開発元が不明なMacアプリを開く(Apple Macユーザガイド)](https://support.apple.com/ja-jp/guide/mac-help/mh40616/mac)**


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
