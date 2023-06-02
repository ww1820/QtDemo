# 简易计算器

项目完整代码：[Calculator](https://github.com/ww1820/QtDemo/tree/main/Calculator)

## 界面

![计算器](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230531120821.png)

## 功能

1. 实现带括号的四则运算、倒数、相反数功能；
2. 实时计算；
3. 括号计数，自动补全。

## 实现

### 思路

1. 按下数字键或者合法的小数点对输入的文本进行追加，作为操作数；
2. 按下右括号或者操作符后，将当前lineEdit中的值作为操作数压入栈中，对表达式**进行计算**后更新表达式；
3. 按下`1/x` 或者`+/-`将lineEdit中的表达式作为操作数计算中间结果并显示，同时更新临时表达式。

使用两个栈（操作数栈numStk，操作符栈opStk）和一个队列（最内层括号的操作符tmpQue）实现带括号的计算（按下括号或者操作符后），具体算法流程如下：

1. 如果当前符号（symbol）为(，直接入栈；
2. 如果symbol为+、-、*、/，比较opStk栈顶元素与symbol：
   1. 如果opStk为空，symbol 直接入栈；
   2. 如果opStk栈顶元素为(，symbol 直接入栈；
   3. 如果opStk栈顶元素为*、/或者 symbol 为 +、-，进行计算，并重复第2步；
   4. 否则 symbol 直接入栈；
3. 如果 symbol 是右括号 )，则不断弹出opStk的栈顶元素并加入tmpQue中，直到遇到栈顶元素为左括号(为止，且左括号(从栈弹出后不加入tmpQue中。从tmpQue队首取出操作符进行计算；

### 问题

1. 为左括号(添加计数

   ```c++
   btnLabel=new QLabel(ui->lParButton);
   // ...
   btnLabel->setText(tr("   <sub>%1</sub>").arg(lParNum));
   ```

2. 1/x 和 +/- 的实现：

   设计一个tmpStr作为临时操作数的表达式，以1/x为例：

   ```c++
   void MainWindow::pushRecButton()
   {
      // _input 只记录键入的操作数，lineEdit可能为中间结果
      // 如果不清空，无法判断_input的内容为当前输入的内容还是上次输入的内容
      _input.clear();
      

      QString str = ui->lineEdit->text();
      if(str.isEmpty()) return;
      if(_tmpValStr.isEmpty() && ui->resLabel->text().endsWith(')')) return;

      if(_tmpValStr.isEmpty())
      {
         _tmpValStr.append(str);
      }

      _tmpValStr = "1 / (" + _tmpValStr + ")";
      double ret = 1 / str.toDouble();

      ui->resLabel->setText(_exp + _tmpValStr); // 追加 tmpValStr 到 表达式exp
      ui->lineEdit->setText(QString::number(ret));
   }
   ```
