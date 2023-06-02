#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _init();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::_init()
{
    ui->resLabel->setText("");
    ui->lineEdit->setText("0");
    ui->lineEdit->setReadOnly(true);
    _tmpValStr.clear();
    _exp.clear();
    _input.clear();


    std::stack<double>().swap(_numStk);
    std::stack<QString>().swap(_opStk);
    std::queue<QString>().swap(_tmpQue);
//    _numStk.swap(std::stack<double>());
//    _opStk.swap(std::stack<QString>());
//    _tmpStk.swap(std::queue<QString>());

    lParNum = 0;

    btnLabel=new QLabel(ui->lParButton);//设计新的label，
    btnLabel->setMargin(5);
    btnLabel->setAlignment(Qt::AlignCenter);//设置Qlabel的文字居中

    /*----------------------------connect----------------------------*/
    // digital
    connect(ui->Button0, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    connect(ui->Button1, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    connect(ui->Button2, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    connect(ui->Button3, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    connect(ui->Button4, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    connect(ui->Button5, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    connect(ui->Button6, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    connect(ui->Button7, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    connect(ui->Button8, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    connect(ui->Button9, SIGNAL(clicked()), this, SLOT(pushDigitalButton()));
    // symbol
    connect(ui->dotButton, SIGNAL(clicked()), this, SLOT(pushDotButton()));
    connect(ui->lParButton, SIGNAL(clicked()), this, SLOT(pushLParButton()));
//    connect(btnLabel, SIGNAL(clicked()), this, SLOT(pushLParButton()));
    connect(ui->rParButton, SIGNAL(clicked()), this, SLOT(pushRParButton()));

//    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(pushAddButton()));
//    connect(ui->subButton, SIGNAL(clicked()), this, SLOT(pushSubButton()));
//    connect(ui->mulButton, SIGNAL(clicked()), this, SLOT(pushMulButton()));
//    connect(ui->divButton, SIGNAL(clicked()), this, SLOT(pushDivButton()));

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(pushOpButton()));
    connect(ui->subButton, SIGNAL(clicked()), this, SLOT(pushOpButton()));
    connect(ui->mulButton, SIGNAL(clicked()), this, SLOT(pushOpButton()));
    connect(ui->divButton, SIGNAL(clicked()), this, SLOT(pushOpButton()));

    connect(ui->recButton, SIGNAL(clicked()), this, SLOT(pushRecButton()));
    connect(ui->invButton, SIGNAL(clicked()), this, SLOT(pushInvButton()));
    connect(ui->eqlButton, SIGNAL(clicked()), this, SLOT(pushEqualButton()));
    // clean
    connect(ui->clearButton, SIGNAL(clicked()),
            this, SLOT(pushClearButton()));
    connect(ui->clearEditButton, SIGNAL(clicked()),
            this, SLOT(pushClearEditButton()));
    connect(ui->bckButton, SIGNAL(clicked()),
            this, SLOT(pushBackspaceButton()));
}

QString MainWindow::_parse(QString curSymbol)
{
    QString ret = "";
    if(curSymbol == ")")
    {
        while (_opStk.top() != "(") {
            _tmpQue.push(_opStk.top());
            _opStk.pop();
        }
        _opStk.pop();

        while (!_tmpQue.empty()) {
            double v1 = _numStk.top();
            _numStk.pop();
            double v2 = _numStk.top();
            _numStk.pop();
            double res = _cal(v2, v1, _tmpQue.front());
            _tmpQue.pop();
            _numStk.push(res);
            ret = QString::number(res);
        }
    }
    while(!_opStk.empty() && _opStk.top() != "(" &&
          (_opStk.top() == "*" || _opStk.top() == "/"
           ||curSymbol == "+" || curSymbol == "-"))
    {
        double v1 = _numStk.top();
        _numStk.pop();
        double v2 = _numStk.top();
        _numStk.pop();
        double res = _cal(v2, v1, _opStk.top());
        _opStk.pop();
        _numStk.push(res);
        ret = QString::number(res);
    }
    if(curSymbol != ")")
    {
        _opStk.push(curSymbol);
    }

    return ret;
}

double MainWindow::_cal(double v1, double v2, QString op)
{
//    qDebug() << v1 << op << v2 << endl;

    if(op == "+")
    {
        return (v1 + v2);
    }
    else if(op == "-")
    {
        return (v1 - v2);
    }
    else if(op == "*")
    {
        return (v1 * v2);
    }
    else if(op == "/")
    {
        if(v2 == 0)
        {
           QMessageBox::information(this, "Calculator", "Division by zero!");
        }
        return (v1 / v2);
    }
    else
    {
        return 0;
    }
}

void MainWindow::_setParText()
{
    if(lParNum != 0)
    {
        btnLabel->setText(tr("   <sub>%1</sub>").arg(lParNum));
    }
    else
    {
        btnLabel->setText("");
    }
}

void MainWindow::_updateExp()
{
//    _input = ui->lineEdit->text();
    if(!_tmpValStr.isEmpty())
    {
        _exp.append(_tmpValStr);
        _tmpValStr.clear();
        QString str = ui->lineEdit->text();
        _numStk.push(str.toDouble());
    }
    else if(!_input.isEmpty())
    {
        _exp.append(_input);
        _numStk.push(_input.toDouble());
        _input.clear();
    }
    else if(!_exp.endsWith(')'))
    {
        QString str = ui->lineEdit->text();
        _exp.append(str);
        _numStk.push(str.toDouble());
    }
}

void MainWindow::pushDigitalButton()
{
    QString objStr = this->sender()->objectName();
    QString digital = *(objStr.end()-1);

    _input.append(digital);

    ui->resLabel->setText(_exp);
    ui->lineEdit->setText(_input);
}

void MainWindow::pushDotButton()
{
    if(_input.contains(".") || !_tmpValStr.isEmpty()) return;

    if(_input.isEmpty())
    {
        _input.append("0");
    }

    _input.append(".");

    ui->resLabel->setText(_exp);
    ui->lineEdit->setText(_input);

}

void MainWindow::pushLParButton()
{
    if(!_tmpValStr.isEmpty() && !_exp.isEmpty())
    {
        qDebug() << "invalid (" << endl;
        return;
    }

    ++lParNum;
    _opStk.push("(");

    _exp.append("(");
    _setParText();

    ui->resLabel->setText(_exp);

}

void MainWindow::pushRParButton()
{
    if(lParNum == 0)
    {
        qDebug() << "invalid )" << endl;
        return;
    }

    --lParNum;

    _updateExp();
    _exp.append(")");
    QString ret = _parse(")");

    _setParText();

    ui->resLabel->setText(_exp);
    if(!ret.isEmpty())
    {
        ui->lineEdit->setText(ret);
    }
}

void MainWindow::pushOpButton()
{
    QString objStr = this->sender()->objectName();
    objStr.chop(6);

    if(objStr == "add")
    {
        _dealOp("+");
    }
    else if(objStr =="sub")
    {
        _dealOp("-");
    }
    else if(objStr == "mul")
    {
        _dealOp("*");
    }
    else if(objStr == "div")
    {
        _dealOp("/");
    }
    else
    {
        qDebug() << "Error Operator!" << endl;
    }
}

void MainWindow::_dealOp(QString op)
{
    if(_input.isEmpty() && ui->lineEdit->text().isEmpty())
    {
        return;
    }

    _updateExp();
    _exp.append(op);
    ui->resLabel->setText(_exp);

    if(_opStk.empty() || _opStk.top() == "(")
    {
        _opStk.push(op);
        return;
    }

    QString ret = _parse(op);

//    _opStk.push(op);

    if(!ret.isEmpty())
    {
        ui->lineEdit->setText(ret);
    }
}


void MainWindow::pushRecButton()
{
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

//    _input = QString::number(ret);

    ui->resLabel->setText(_exp + _tmpValStr);
    ui->lineEdit->setText(QString::number(ret));
}

void MainWindow::pushInvButton()
{
    _input.clear();

    QString str = ui->lineEdit->text();
    if(str.isEmpty()) return;
    if(_tmpValStr.isEmpty() && ui->resLabel->text().endsWith(')')) return;

    if(_tmpValStr.isEmpty())
    {
        _tmpValStr.append(str);
    }

    _tmpValStr = "neg(" + _tmpValStr + ")";
    double ret = - str.toDouble();

    ui->resLabel->setText(_exp + _tmpValStr);
    ui->lineEdit->setText(QString::number(ret));

}

void MainWindow::pushEqualButton()
{
    if(ui->resLabel->text().endsWith('='))
    {
        return;
    }
    _updateExp();

    double res = 0;
    while(lParNum)
    {
        --lParNum;
        res= _parse(")").toDouble();
        _exp.append(')');
//        pushRParButton();
    }

    _setParText();

    _exp.append("=");
    ui->resLabel->setText(_exp);

    // TODO

    while (!_numStk.empty() && !_opStk.empty()) {
        QString op = _opStk.top();
        _opStk.pop();
        double v1 = _numStk.top();
        _numStk.pop();
        double v2 = _numStk.top();
        _numStk.pop();
        res = _cal(v2, v1,op);
        _numStk.push(res);
    }
    res = _numStk.top();
    _numStk.pop();

    if(!_numStk.empty() || !_opStk.empty())
    {
        qDebug() << "invalid result" << endl;
    }
    ui->lineEdit->setText(QString::number(res));

    _exp.clear();
    _input.clear();

}

void MainWindow::pushClearButton()
{
    _tmpValStr.clear();
    _exp.clear();
    _input.clear();
    lParNum = 0;

    _setParText();

    std::stack<double>().swap(_numStk);
    std::stack<QString>().swap(_opStk);
    std::queue<QString>().swap(_tmpQue);
    ui->lineEdit->setText("0");
    ui->resLabel->clear();
}

void MainWindow::pushClearEditButton()
{
    _tmpValStr.clear();
    _input.clear();
    ui->resLabel->setText(_exp);
    ui->lineEdit->setText("0");
}

void MainWindow::pushBackspaceButton()
{
    if(_input.isEmpty())
    {
        return;
    }
    _input.chop(1);
    ui->lineEdit->setText(_input);
}

