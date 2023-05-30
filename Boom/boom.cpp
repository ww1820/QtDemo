#include "boom.h"
#include "ui_boom.h"

Boom::Boom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Boom)
{
    ui->setupUi(this);
    init();
}

Boom::~Boom()
{
    delete boomGif;
    delete ui;
}

void Boom::init()
{
    /*
    QLabel label;
    QMovie *movie = new QMovie("animations/fire.gif");

    label.setMovie(movie);
    movie->start();
    */
    myTimer = new QTimer(this);
    boomGif = new QMovie("/home/wwu/Documents/WorkSpace/QT/Boom/boom.gif");

    num = 10;
    ui->lcdNumber->display(num);
    ui->gifLabel->hide();
    ui->gifLabel->setMovie(boomGif);
    ui->gifLabel->setScaledContents(true);// label自动放缩
    myTimer->start(1000);

    connect(myTimer, SIGNAL(timeout()), this, SLOT(LCDUpdate()));
}

void Boom::LCDUpdate()
{
    --num;
    ui->lcdNumber->display(num);
    if(num == 0)
    {
        ui->gifLabel->show();
        boomGif->start();
        this->showFullScreen();// 窗口全屏
        ui->lcdNumber->hide();
    }

    if(num == -7)
    {
        close();
    }
}
