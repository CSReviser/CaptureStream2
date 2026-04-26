## [語学講座CS2](https://csreviser.github.io/CaptureStream2/)  
## 【ショートカットアプリ活用事例(Mac)】     
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
**語学講座CS2のmacOS版とショートカットアプリを使う応用活用事例です。**

**特番録音用ショートカット**
**概要**
**特番の番組IDを入力してiCloud Driveとローカルドライブに保存する。**


<img width="685" height="463" alt="image" src="https://github.com/user-attachments/assets/98e0451a-9359-4614-a2bb-6663da2a57b8" />

```sh
/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui $1 -a1 -o "$HOME/Library/Mobile Documents/com~apple~CloudDocs/CaptureStream2/"
/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui $1 -a1
```
