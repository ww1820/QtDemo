#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete myTimer;
    delete ui;
}

void MainWindow::init()
{
    myTimer = new QTimer();
    cnt = 0;
    ui->progressBar->setValue(cnt);
    ui->progressBar->setValue(cnt);
    ui->startButton->setDisabled(false);
    ui->pauseButton->setDisabled(true);
    ui->stopButton->setDisabled(true);
    connect(this->myTimer, SIGNAL(timeout()), this, SLOT(flushBar()));
}

void MainWindow::on_startButton_clicked()
{
    myTimer->start(100);
    ui->startButton->setDisabled(true);
    ui->pauseButton->setDisabled(false);
    ui->stopButton->setDisabled(false);
}

void MainWindow::on_pauseButton_clicked()
{
    myTimer->stop();
    ui->startButton->setDisabled(false);
    ui->pauseButton->setDisabled(true);
    ui->stopButton->setDisabled(false);
}

void MainWindow::on_stopButton_clicked()
{
    myTimer->stop();
    cnt = 0;
    ui->progressBar->setValue(cnt);
    ui->startButton->setDisabled(false);
    ui->pauseButton->setDisabled(true);
    ui->stopButton->setDisabled(true);
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
