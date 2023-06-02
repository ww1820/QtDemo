# 进度条功能demo

项目完整代码：[MyTimer](https://github.com/ww1820/QtDemo/tree/main/MyTimer)

## 界面

![QT进度条](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230530173351.png)

## 功能

1. 点击start进度条开始刷新，pause暂停，stop停止并清空进度条；
2. 点击button后修改使能状态。

## 实现

思路：定时器超时后，计数+1，更新progressBar的值。

主要代码：

```c++
void MainWindow::init()
{
    myTimer = new QTimer();
    cnt = 0;
    ui->progressBar->setValue(cnt);
    // ...
    connect(this->myTimer, SIGNAL(timeout()), this, SLOT(flushBar()));
}

void MainWindow::flushBar()
{
    ++cnt;
    ui->progressBar->setValue(cnt);
    if(cnt == 100)
    {
        QMessageBox::information(this, "Timer", "Done!");
        on_stopButton_clicked();
    }
}
```
