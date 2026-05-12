## [語学講座CS2](https://csreviser.github.io/CaptureStream2/)  
## 【ショートカットアプリ活用事例(Mac)】     
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
**語学講座CS2のmacOS版とショートカットアプリを使う応用活用事例です。**

**[1. 特番録音用ショートカット](./mac-shortcuts#1-特番録音用ショートカット)**       

**[2. CS2自己承認用ショートカット](./mac-shortcuts#2-CS2自己承認用ショートカット)**



#### **1. 特番録音用ショートカット**

* **概要**

* **特番の番組IDを入力してiCloud Driveとローカルドライブに保存する。**


<img width="600" alt="image" src="https://github.com/user-attachments/assets/98e0451a-9359-4614-a2bb-6663da2a57b8" />

```sh
/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui $1 -a1 -o "$HOME/Library/Mobile Documents/com~apple~CloudDocs/CaptureStream2/"
/Applications/CaptureStream2.app/Contents/MacOS/CaptureStream2 -nogui $1 -a1
```


#### **2. CS2自己承認用ショートカット**

* **概要**

* **/Applications/内の語学講座CS2に自己署名し、インストール・更新作業を簡素化する。**


<img width="600" alt="image" src="https://github.com/user-attachments/assets/25ec92be-ee16-426e-85d2-8aa04768e2be" />

```sh
xattr -cr com.apple.quarantine /Applications/CaptureStream2.app
codesign --force --deep --sign - /Applications/CaptureStream2.app
```


#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
