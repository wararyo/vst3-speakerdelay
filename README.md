# SpeakerDelay

DSPを内蔵したスピーカーとそうでないスピーカーを同時に使用する場合、DSPを内蔵したスピーカーに若干のレイテンシが生じ、定位感が悪化してしまいます。  
SpeakerDelayをマスターに指してDSP処理を行っていないスピーカーの発音を遅らせることで位相のずれを解消し、本来の定位感で聴くことができます。

一部のDAWではGUIが正しく表示されない可能性があります。

## 動作確認済み環境

### OS

* macOS Ventura (Apple Silicon)
* macOS Monterey (x64)
* Windows 11 (x64)

### DAW

* Cubase Pro 12.0.40

## 動作確認済み構成

* Stereo
* 5.1
* 5.1.4

## ライセンス

GPLv3  
商用利用可能です。  
このソフトウェアの使用により不利益が生じたとしても、作者は一切責任を負いません。

## ビルド方法

### macOS

```
git submodule update --init --recursive
cmake -B build -G Xcode -DSMTG_ADD_VSTGUI=ON
xed build
```

XCodeが開くので、ウィンドウ上部の `My Mac` を `Any Mac (Apple Silicon, Intel)` に変更する  
Product > Build でビルドを行うと、 .vst3 ファイルが生成され、 ~/Library/Audio/Plug-Ins/VST3/ 配下にシンボリックリンクが生成される  
Product > Scheme > Edit Scheme... で表示されるウィンドウから Build Configuration を Release に変更するとリリースビルドになる

### Windows

Visual Studio Installerから「C++によるデスクトップ開発」を追加する  
vst3-speakerdelayフォルダをVisual Studioで開く  
ビルド > すべてビルド を選択するとビルドが行われ、 .vst3 ファイルが生成される

## Credit

[vst3-boilerplate](https://github.com/ryohey/vst3-boilerplate) by ryohey
