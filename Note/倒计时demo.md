# 倒计时demo

项目完整代码：[Boom](https://github.com/ww1820/QtDemo/tree/main/Boom)

## 界面

![倒计时](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230531120221.png)
![爆炸动画](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230531120333.png)

## 功能

使用LCDNumber控件显示倒计时，倒计时结束窗口最大化播放爆炸动画。

## 实现

### 倒计时

设置一个超时时间为1000ms的计时器，计时器超时信号发生时更新LCD显示的数字，数字为0时播放爆炸动画，动画结束后停止播放和计时器。

### 播放爆炸动画

使用QMovie上播放gif，在QLabel上显示。

```c++
#include <QLabel>
#include <QMovie>

QLabel label;
QMovie *movie = new QMovie("animations/fire.gif");

label.setMovie(movie);
movie->start();
```
