#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QObject::connect(ui->CmdLineEdit, SIGNAL(returnPressed()),
                    this, SLOT(on_SubmitButton_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_SubmitButton_clicked()
{
    QString cmdLine = ui->CmdLineEdit->text();      // get context
    cmdLine = cmdLine.trimmed();

    QProcess *myProcess = new QProcess;
    myProcess->start(cmdLine);            //start program
    ui->CmdLineEdit->clear();
    this->close();

    myProcess->waitForFinished();
    delete myProcess;
    QString result = myProcess->readAllStandardOutput();
    qDebug()<<"cmd:" << cmdLine.trimmed() << "\n";
    qDebug()<<"result:\n" <<result.toLatin1().data();
}

void Widget::on_CancelButton_clicked()
{
    ui->CmdLineEdit->clear();
    this->close();
}

void Widget::on_BrowserButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "open file", QDir::currentPath() ,
                tr("Text files (*.txt)"));
    if(fileName.isEmpty())
    {
        return;
    }

    QString cmdLine = tr("gedit %1").arg(fileName);      // get context
    cmdLine = cmdLine.trimmed();

    QProcess *myProcess = new QProcess;
    myProcess->start(cmdLine);            //start program
    ui->CmdLineEdit->clear();
    this->close();

    myProcess->waitForFinished();
    delete myProcess;
}
