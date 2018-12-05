[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
spectrumAnalyzer
====
* LEDアレイでスペクトラムアナライザー  
![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/spectrumAnalyzer.gif) 
## Description
音響機器によく搭載されていたスペクトラムアナライザーをarduinoとLEDバーで作成しました。  
音の可視化方法のひとつとして作ってみたかったものです。
## Composition
* マイコン: arduino micro
* LED: WS2812B
* IC: MSGEQ7P
## Detail
![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9826.JPG)  
筐体はシームレスで真っ黒になるように設計しました。  
真っ黒なのに光るのがポイントです。  
![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9836.JPG)  
[フロントパネル](https://github.com/chakio/spectrumAnalyzer/blob/master/model/frontPanel.stl)はクリアブラックの3mm厚のアクリル板と乳白色のの2mm厚のアクリル板を重ねることで、程よいLED明かりを拡散させることと、内側が透けないようにする工夫をしています。  
[dxf](https://github.com/chakio/spectrumAnalyzer/blob/master/model/frontPanel.dxf)で書き出して、レーザカッター切り出しました.  

メインの筐体の[モデル](https://github.com/chakio/spectrumAnalyzer/blob/master/model/body.stl)を、3Dプリンタで制作しました。  
背面には、DC電源と音声入力用のイヤホンジャック、モード切り替え用のスイッチ用の穴が開いています。

![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9833.JPG)   
内側にはLEDアレイが並んでいます。
3Dプリンタで作成した[固定パネル](https://github.com/chakio/spectrumAnalyzer/blob/master/model/ledHolder.stl)にプラスチック
リベットを用いて固定しています。  

![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9834.JPG)   
![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9835.JPG)   
回路周りはユニバーサル基板に手半田で作成しています。

## Appendix
![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9829.JPG)   
側面が虹色でかっこいいです。