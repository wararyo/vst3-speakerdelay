# SpeakerDelay

DSPを内蔵したスピーカーとそうでないスピーカーを同時に使用する場合、DSPを内蔵したスピーカーに若干のレイテンシが生じ、定位感が悪化してしまいます。  
SpeakerDelayをマスターに指してDSP処理を行っていないスピーカーの発音を遅らせることで位相のずれを解消し、本来の定位感で聴くことができます。

macOS(Apple Silicon)でビルドできることを確認しています。

## 対応予定のスピーカー配置

* [ ] Mono
* [x] Stereo
* [ ] 5.1
* [ ] 5.1.4
* [ ] 7.1.4

## Credit

[vst3-boilerplate](https://github.com/ryohey/vst3-boilerplate) by ryohey
