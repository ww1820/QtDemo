# 记事本功能

项目完整代码：[MyNotepad](https://github.com/ww1820/QtDemo/tree/main/MyNotepad)

## 界面

![记事本](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230531122139.png)

## 功能

1. 编辑文本
2. 文件菜单：
   1. 新建、打开、保存、另存为
   2. 打印
   3. 退出
3. 编辑菜单：
   1. 撤销、重做
   2. 剪切、复制、粘贴
   3. 查找、替换
   4. 全选
   5. 插入当前时间日期
4. 选项菜单
   1. 自动换行
   2. 字体
   3. 颜色
5. 视图菜单
   1. 缩放
   2. 打开/关闭状态栏
6. 其他：
   1. 状态栏显示当前光标位置
   2. 窗口标题显示文件名
   3. 文本内容修改后窗口显示`*`

## 实现

主要是查找&替换功能的实现：添加一个对话框，输入查找和替换的字符串，点击查找（替换），对话框发送查找（替换）信号，主窗口接收到查找（替换）信号后，获取查找（替换）字符串进行查找（替换）。

查找功能直接调用`document()->find()`函数，返回一个QTextCursor对象，调用`setTextCursor()`将查找到的文本选中。

点击替换时先判断当前光标选中内容是否为想要被替换掉的内容，如果是，直接替换，否则，查找下一个并替换。进行替换时先删除当前选中再插入想替换的内容。

部分代码如下：

```c++
// subdialog.cpp
void SubDialog::init()
{
    connect(ui->findButton, SIGNAL(clicked()),
            this, SLOT(sendFindSignal()));
    connect(ui->replaceButton, SIGNAL(clicked()),
            this, SLOT(sendReplaceSignal()));
}

void SubDialog::sendFindSignal()
{
    emit findSignal();
}

void SubDialog::sendReplaceSignal()
{
    emit replaceSignal();
}

// mainwindow.cpp
void MainWindow::findSlot()
{
    bool dir = _subDialogPtr->getDirection();
    if(dir) // 查找方向前/后
    {
        nextSlot();
    }
    else
    {
        advanceSlot();
    }
    activateMainWindow(); // 将主窗口设为活动窗口
}

void MainWindow::advanceSlot()// forward
{
    QString findStr = _subDialogPtr->getFindStr();
    QTextCursor qTextCursor = ui->textEdit->textCursor();

    if(findStr.isEmpty())
    {
        QMessageBox::warning(this, "MyNotepad",
                                 "The string to search should not be empty!");
        return;
    }

    if(_subDialogPtr->getCaseSensitive()) // 大小写敏感
    {
        qTextCursor = ui->textEdit->document()->find(
                    findStr, qTextCursor, QTextDocument::FindCaseSensitively
                    | QTextDocument::FindBackward);
    }
    else
    {
        qTextCursor = ui->textEdit->document()->find(
                    findStr, qTextCursor, QTextDocument::FindBackward);
    }

    if(qTextCursor.selectedText().isEmpty())
    {
        QMessageBox::warning(this, "MyNotepad",
                             tr("Cannot find \"%1\"!").arg(findStr));
        return;
    }
    ui->textEdit->setTextCursor(qTextCursor);
}

void MainWindow::nextSlot()// backward
{
    // ...
}

void MainWindow::replaceSlot()
{

    // ...
}

```

### 问题

1. 设置活动窗口

   ```c++
   void MainWindow::activateMainWindow()
   {
      if(!this->isActiveWindow()) //判断是否是活动窗口
      {
         this->activateWindow(); //设置成活动窗口
      }
   }
   ```

2. 在记事本中修改文件后保存需要`ui->textEdit->document()->setModified(false)`，否则文本框的状态为已修改无法直接关闭或者打开新文件。
3. 打印文本

   ```c++
   // .pro 文件
   QT += printsupport

   // mainwindow.cpp
   #
   #include <QPrintDialog>
   # include <QPrinter>
   void MainWindow::printFileSlot()
   {
      QPrinter qPrinter;
      QPrintDialog printDialog(&qPrinter); // 选择打印设备

      if (printDialog.exec() == QDialog::Accepted) {

         ui->textEdit->document()->print(&qPrinter);  // 打印

         QMessageBox::information(this, "MyNotepad","Successed!");
         }
      else
      {
         QMessageBox::information(this, "MyNotepad","Canceled!");
      }
   }
   ```

4. 设置文本颜色Palette，使用setColor只能修改选中文本的颜色

   ```c++
   void MainWindow::setColorSlot()
   {
      QColor qColor = ui->textEdit->palette().color(QPalette::Text);
      qColor = QColorDialog::getColor(qColor, this);
      if(qColor.isValid())
      {
         QPalette p = ui->textEdit->palette();
         p.setColor(QPalette::Text, qColor); // QPalette::WindowText 无效
         ui->textEdit->setPalette(p);
      }
   }
   ```

5. 状态栏显示当前光标位置

   ```c++
   void MainWindow::on_textEdit_cursorPositionChanged()
   {
      QTextCursor qTextCursor = ui->textEdit->textCursor(); //当前光标
      int rowNum = qTextCursor.blockNumber() + 1;//获取光标所在行的行号
      // int colNum = qTextCursor.columnNumber() + 1; // 该函数获取的是自动换行后的列号
      int colNum = qTextCursor.positionInBlock() + 1;
      _cursorInfoLabel->setText(
                  "# line: " + QString::number(rowNum) +
                  ", col: " + QString::number(colNum));
      _cursorInfoLabel->adjustSize();
   }
   ```
