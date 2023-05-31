# QT 实现运行对话框

项目完整代码：[MyLayout](https://github.com/ww1820/QtDemo/tree/main/MyLayout)

## 界面

![Running程序界面](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230520180848.png)

## 功能

1. 获取文本框内容，作为命令执行；
2. 点击submit后清空文本框，关闭对话框；
3. LineEdit激活时回车运行程序，`connect()`。

```c++
QObject::connect(ui->CmdLineEdit, SIGNAL(returnPressed()),
                this, SLOT(on_SubmitButton_clicked()));
```

<!-- 影子工程：会在另一个目录下生成可执行文件 -->

## 问题

1. 获取Edit文本时需要去除前后空格：`trimmed()`
2. Linux `QProcess::start()` 没反应
3. QT 修改绑定了槽的控件Label时，需要删除.h文件里对应的槽函数
4. `QString`转换为`char *`

参考资料：[QT中执行linux指令的几种方法](https://blog.csdn.net/wangpailiulanqi8/article/details/129293799)

### QProcess::start()

`QProcess::start()`的有输出的命令执行结果可以从程序中获取字符流，比如`ls`命令。
但是需要`waitForFinished()`等待程序执行完成，不然可能无法获取到结果。

```c++
myProcess->start(cmdLine.trimmed());
myProcess->waitForFinished();

QString result = myProcess->readAllStandardOutput();    //获取执行结果
qDebug()<<"cmd:" << cmdLine.trimmed() << "\n";
qDebug()<<"result:\n" <<result;

/*
输入：ls
输出：
cmd: "ls" 

result:
 "main.o\nMakefile\nmoc_widget.cpp\nmoc_widget.o\nMyLayout\nui_widget.h\nwidget.o\n"
*/
```

但是如果将`myProcess->waitForFinished()`注释掉，运行结果：

```c++
/*
输入：ls
输出：
cmd: "ls" 

result:
 
*/
```

## QString转换为char *

`qDebug()`参数为`QString`类型时，输出里`\n`为字符，需要将`QString`转为`char*`。
具体代码如下：

```c++
qDebug()<<"result:\n" <<result.toLatin1().data();
```

运行结果：

```c++
/*
输入：ls
输出：
cmd: "ls" 

result:
 main.o
Makefile
moc_widget.cpp
moc_widget.o
MyLayout
ui_widget.h
widget.o
*/
```
