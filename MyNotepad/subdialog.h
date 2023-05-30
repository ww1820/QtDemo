#ifndef SUBDIALOG_H
#define SUBDIALOG_H

#include <QDialog>
#include <QString>
#include <QCloseEvent>
#include <QDebug>

namespace Ui {
class SubDialog;
}

class SubDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SubDialog(QWidget *parent = 0);
    ~SubDialog();

    void init();

    QString getFindStr();
    QString getReplaceStr();
    bool getDirection();
    bool getCaseSensitive();

private:
    Ui::SubDialog *ui;

private slots:
    void sendFindSignal();
    void sendReplaceSignal();

signals:
    void findSignal();
    void replaceSignal();
};

#endif // REPLACEDIALOG_H
