#include "boom.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Boom w;
    w.show();

    return a.exec();
}
