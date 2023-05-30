#ifndef BOOM_H
#define BOOM_H

#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QMovie>
#include <QTimer>
#include <QDebug>


namespace Ui {
class Boom;
}

class Boom : public QWidget
{
    Q_OBJECT

public:
    explicit Boom(QWidget *parent = 0);
    ~Boom();

private:
    Ui::Boom *ui;
    void init();

    QTimer* myTimer;
    QMovie* boomGif;

    int num;

private slots:
    void LCDUpdate();
};

#endif // BOOM_H
