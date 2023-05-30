#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->setGeometry(100, 100, 1200, 800);
    ui->textBrowser->setFont(QFont("Ubuntu Mono", 16));
}

MyWidget::~MyWidget()
{
    delete ui;
}

QString MyWidget::getButtonName(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        return "Left Button";
    }
    else if(event->button() == Qt::RightButton)
    {
        return "Right Button";
    }
    else if(event->button() == Qt::MiddleButton)
    {
        return "Middle Button";
    }

    return "UnKonw Button";
}

void MyWidget::getPosInfo(QMouseEvent* e, QString& msg)
{
    /*
    ** globalPos = screenPosF;
    ** localPosF = pos = windowPosF;
    ** QPoint & QPointF ?
    */
    QPoint pos1 = e->globalPos();
    msg.append(tr("globalPos(%1, %2), \n").arg(
                   QString::number(pos1.x()), QString::number(pos1.y())));

    QPointF pos2 = e->localPos();
    msg.append(tr(" localPos(%1, %2), \n").arg(
                   QString::number(pos2.x()), QString::number(pos2.y())));

//    QPoint pos3 = e->pos();
//    msg.append(tr("      pos(%1, %2), \n").arg(
//                   QString::number(pos3.x()), QString::number(pos3.y())));

//    QPointF pos4 = e->screenPos();
//    msg.append(tr("screenPos(%1, %2), \n").arg(
//                   QString::number(pos4.x()), QString::number(pos4.y())));

//    QPointF pos5 = e->windowPos();
//    msg.append(tr("windowPos(%1, %2).\n ").arg(
//                   QString::number(pos5.x()), QString::number(pos5.y())));
}

/*

QPoint globalPos() const
const QPointF & localPos() const
QPoint pos() const
const QPointF & screenPos() const
const QPointF & windowPos() const

*/

void MyWidget::mousePressEvent(QMouseEvent* e)
{
//    qDebug() << "mousePressEvent" << endl;

    QString msg = "";
    msg.append(getButtonName(e));
    msg.append(" has been Pressed at: \n");

    getPosInfo(e,msg);

    ui->textBrowser->append(msg);
}

void MyWidget::mouseReleaseEvent(QMouseEvent* e)
{
//    qDebug() << "mouseReleaseEvent" << endl;

    QString msg = "";
    msg.append(getButtonName(e));
    msg.append(" has been Released at: \n");

    getPosInfo(e,msg);

    ui->textBrowser->append(msg);
}

void MyWidget::mouseMoveEvent(QMouseEvent* e)
{
//    qDebug() << "mouseMoveEvent" << endl;
//    qDebug() << e->button() << endl; // Qt::NoButton

    QString msg = "";
    msg.append("The mouse is Moving from: \n");

    getPosInfo(e,msg);

    ui->textBrowser->append(msg);
}

void MyWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
//    qDebug() << "mouseDoubleClickEvent" << endl;

    QString msg = "";
    msg.append(getButtonName(e));
    msg.append(" has been Double Click at: \n");

    getPosInfo(e,msg);

    ui->textBrowser->append(msg);
}
