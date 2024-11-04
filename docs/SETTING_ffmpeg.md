## [語学講座CS2](https://csreviser.github.io/CaptureStream2/)  
## 【ffmpegパス設定】 　　　   
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
#### 語学講座ＣＳ２では通常初期値のままで使用することができますが、一部の環境でffmpegが正常に動作しない場合があります。正常に動作するffmpegをインストールしてそのパス（ffmpegをインストールしたフォルダ）を設定することができます。
**メインウィンドウ上部　カスタマイズ > ffmpegパス設定 を選択すると下記が表示されます。**

　　　　　　![image](https://github.com/user-attachments/assets/698092a5-f7d7-4aef-9801-623aa3e4e2b7)

#### 1. 設定する：
#### ffmpegをインストールしたフォルダを設定します。
#### この設定をした場合は設定したフォルダのffmpegが使われます。指定したフォルダにffmpegが存在しない場合や存在しても動作しない場合はレコーディング実行時にエラーとなります。
#### 　　　　


#### 2. 初期値に戻す：
#### 語学講座CS2の本体があるフォルダにあるffmpegが使われます。 語学講座CS2の本体があるフォルダにあるffmpegを正常に動作するものに置き換えることにより動作不具合を解消することもできます。OSによって以下のように動作仕様が異なります。ご使用のOSによって読み替えてください。            
* **Windows：語学講座CS2の本体（CaptureStream2.exe）と同じフォルダにあるffmpeg.exeが使われます。**          
* **Ubuntu：語学講座CS2の本体（CaptureStream2）と同じフォルダにあるffmpegが使われます。**          
* **macOS：下記の優先順位で存在するffmpegが使われます。**           
  * **１：保存フォルダで設定したフォルダにffmpegが存在する場合はそのffmpegが優先して使われます。使いたくない場合はffmpegをフォルダから削除または移動してください。**          
  * **２： "~/Library/Preferences"フォルダにffmpegが存在する場合はそのffmpegが優先して使われます。使いたくない場合はffmpegをフォルダから削除または移動してください。**          
  * **３： "/usr/local/bin"フォルダにffmpegが存在する場合はそのffmpegが優先して使われます。使いたくない場合はffmpegをフォルダから削除または移動してください。初期値で"/usr/local/bin"フォルダにあるffmpegを使う場合はテスト版が必要です。 [テスト版ダウンロードはこちら](https://github.com/CSReviser/CaptureStream2/releases/download/20241007/CaptureStream2-MacOS-20241007-1.dmg)**
  * **４：語学講座CS2の本体（CaptureStream2）と同じフォルダにあるffmpegが使われます。** 

#### 　　　　　
#### 　　　　　　        
#### 　　　　　　        

#### **[ffmpeg最新版入手サイト](./FFMPEG)**
#### 　　　　　
#### 　　　　　　        
#### 　　　　　　        

#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
