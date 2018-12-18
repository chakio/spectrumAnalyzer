[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
spectrumAnalyzer
====
* LEDアレイでスペクトラムアナライザー  
![result](https://github.com/chakio/spectrumAnalyzer/blob/master/media/spectrumAnalyzer.gif) 
## Description
音響機器によく搭載されていたスペクトラムアナライザーをarduinoとLEDバーで作成しました。  
音の可視化方法のひとつとして作ってみたかったものです。
製作時期 2017年1月中旬  
## Composition
* マイコン: arduino micro
* LED: [WS2812B](https://www.amazon.co.jp/HiLetgo%C2%AE-5%E5%80%8B%E3%82%BB%E3%83%83%E3%83%88-WS2812-%E3%83%91%E3%83%8D%E3%83%AB%E3%83%A2%E3%82%B8%E3%83%A5%E3%83%BC%E3%83%AB-Arduino%E3%81%AB%E5%AF%BE%E5%BF%9C/dp/B014F5VLN0/ref=pd_sbs_21_1?_encoding=UTF8&pd_rd_i=B014F5VLN0&pd_rd_r=fcc49ac4-02e5-11e9-9d6f-17897b8b43cf&pd_rd_w=Og5h7&pd_rd_wg=ap99w&pf_rd_p=cda7018a-662b-401f-9c16-bd4ec317039e&pf_rd_r=R3BYS9DRZQ91EAQ87ECX&psc=1&refRID=R3BYS9DRZQ91EAQ87ECX)
* IC: [MSGEQ7P](https://www.switch-science.com/catalog/585/)
## Detail
<img src="https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9826.JPG" width="500px">  
筐体はシームレスで真っ黒になるように設計しました。  
真っ黒なのに光るのがポイントです。  
<img src="https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9836.JPG" width="500px">  

[フロントパネル](https://github.com/chakio/spectrumAnalyzer/blob/master/model/frontPanel.stl)はクリアブラックの3mm厚のアクリル板と乳白色のの2mm厚のアクリル板を重ねることで、程よいLED明かりを拡散させることと、内側が透けないようにする工夫をしています。  
[dxf](https://github.com/chakio/spectrumAnalyzer/blob/master/model/frontPanel.dxf)で書き出して、レーザカッター切り出しました.  

メインの筐体の[モデル](https://github.com/chakio/spectrumAnalyzer/blob/master/model/body.stl)を、3Dプリンタで制作しました。  
上面には、明るさ調整用のボリューム、
側面には、arduinoの書き込み用のmicroUSBの先込み口、
背面には、DC電源と音声入力用のイヤホンジャック、モード切り替え用のスイッチ用の穴が開いています。

<img src="https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9833.JPG" width="500px">  

内側にはLEDアレイが並んでいます。
3Dプリンタで作成した[固定パネル](https://github.com/chakio/spectrumAnalyzer/blob/master/model/ledHolder.stl)にプラスチックリベットを用いて固定しています。  

<img src="https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9834.JPG" width="500px">  
<img src="https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9835.JPG" width="500px"> 
回路周りはユニバーサル基板に手半田で作成しています。

## Appendix
<img src="https://github.com/chakio/spectrumAnalyzer/blob/master/media/IMG_9829.JPG" width="500px">  
側面が虹色でかっこいいです。