#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

#include <stack>
#include <queue>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString _tmpValStr;
    QString _exp;
    QString _input; // 输入的值
    QLabel* btnLabel;

    std::stack<double> _numStk; //暂存的操作数
    std::stack<QString> _opStk; //暂存的操作符
    std::queue<QString> _tmpStk; // ()中的操作符
    int lParNum; //  未匹配( 的数目

    void _init();
    QString _parse(QString curOP);
    double _cal(double, double, QString);
    void _setParText();
    void _updateExp();
    void _dealOp(QString);


private slots:
    void pushDigitalButton();
    void pushDotButton();

    void pushLParButton();
    void pushRParButton();
    void pushOpButton();
//    void pushAddButton();
//    void pushSubButton();
//    void pushMulButton();
//    void pushDivButton();

    void pushRecButton();
    void pushInvButton();

    void pushEqualButton();

    void pushClearButton();
    void pushClearEditButton();
    void pushBackspaceButton();


};

#endif // MAINWINDOW_H
