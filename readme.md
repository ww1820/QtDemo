# README

## 文件结构

```bash
├─Boom              # 倒计时Demo
├─Calculator        # 简易计算器Demo
├─MouseEventDemo    # 鼠标点击事件Demo
├─MyLayout          # 运行对话框Demo
├─MyNotepad         # 记事本功能Demo
├─MyTimer           # 进度条功能Demo
└─Note              # 笔记
```

## 运行环境

1. Ubuntu 16.04
2. Qt Creator 4.0.3
3. Qt 5.6.2

## 运行对话框

界面：
![Running程序界面](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230520180848.png)

功能：

1. 获取文本框内容，作为命令执行；
2. 点击submit后清空文本框，关闭对话框；
3. LineEdit激活时回车运行程序。

笔记：[运行对话框demo.md](/Note/%E8%BF%90%E8%A1%8C%E5%AF%B9%E8%AF%9D%E6%A1%86demo.md)

## 进度条功能

界面：

![QT进度条](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230530173351.png)

功能：

1. 点击start进度条开始刷新，pause暂停，stop停止并清空进度条；
2. 点击button后修改使能状态。

笔记：[进度条功能demo.md](/Note/%E8%BF%9B%E5%BA%A6%E6%9D%A1%E5%8A%9F%E8%83%BDdemo.md)

## 倒计时

界面：

![倒计时](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230531120221.png)
![爆炸动画](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230531120333.png)

功能：

使用LCDNumber控件显示倒计时，倒计时结束窗口最大化播放爆炸动画。

笔记：[倒计时demo.md](/Note/%E5%80%92%E8%AE%A1%E6%97%B6demo.md)

## 鼠标点击事件

界面：

![界面](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230531120708.png)

功能：

打印鼠标事件。

笔记：[鼠标点击事件.md](/Note/%E9%BC%A0%E6%A0%87%E7%82%B9%E5%87%BB%E4%BA%8B%E4%BB%B6.md)

## 简易计算器

界面：

![计算器](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230531120821.png)

功能：

1. 实现带括号的四则运算、倒数、相反数功能；
2. 实时计算；
3. 括号自动补全。

笔记：[简易计算器demo.md](/Note/%E7%AE%80%E6%98%93%E8%AE%A1%E7%AE%97%E5%99%A8demo.md)

## 记事本功能

界面：

![记事本](https://blog-1312962011.cos.ap-nanjing.myqcloud.com/imgs/20230531122139.png)

功能：

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

笔记：[记事本功能demo.md](/Note/%E8%AE%B0%E4%BA%8B%E6%9C%AC%E5%8A%9F%E8%83%BDdemo.md)
