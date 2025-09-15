## [語学講座CS2](https://csreviser.github.io/CaptureStream2/) 
### スケジュール録音の設定方法(Ubuntu版：crontab)　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]
#### 　　　　　
#### crontabを使ったスケジュール録音の設定方法です。
#### 　　　　　
#### 1. 端末（ターミナル）アプリを起動します。ショートカットキーは『Ctrl+Alt+T』です。
#### ２. 端末（ターミナル）アプリが起動したら『crontab -e』と入力し、Enterキーを押します。

```sh
$ crontab -e
```
#### 3. エディタは『nano』を使用します。最終行にカーソルを移動し、例えば下記のように入力します。

```sh
5 10 * * * export DISPLAY=:0 && $HOME/ダウンロード/LinCaptureStream2/CaptureStream2 -nogui
```

#### 　　この例では毎日10時5分に実行されます。   　　
#### 　　　　
#### ＜起動時に実行させる例＞   

```sh
@reboot sleep 20 && export DISPLAY=:0 && $HOME/ダウンロード/LinCaptureStream2/CaptureStream2 -nogui
```

#### 　　　　
#### ＜Wineを使ったWindows版の例＞   

```sh
25 10 * * * export DISPLAY=:0 && /usr/bin/wine $HOME/ダウンロード/WinCaptureStream2/CaptureStream2.exe -nogui
```

#### 　　　　
#### ＜Wineを使ったWindows版を起動時に実行させる例＞   

```sh
@reboot sleep 20 && export DISPLAY=:0 && /usr/bin/wine $HOME/ダウンロード/WinCaptureStream2/CaptureStream2.exe -nogui
```

   
#### 4. 変更内容を保存します。『Ctrl+O』と入力後、Enterキーを押します。  
![image](https://user-images.githubusercontent.com/46049273/210122479-eb459b72-f6e8-4e95-9457-18a17516a870.png)

#### 4. nanoを終了します。『Ctrl+X』と入力します。
#### 　　　　　
#### 　　　　　
#### 　　　　　
#### ［[ＴＯＰ](./)**｜**[目次](./#目次)**｜**[ドキュメント](./#ドキュメント-1)]

*** 
 <link rel="shortcut icon" type="image/x-icon" href="https://avatars.githubusercontent.com/u/46049273?v=4">
 <meta name="twitter:image:src" content="https://avatars.githubusercontent.com/u/46049273?v=4">
