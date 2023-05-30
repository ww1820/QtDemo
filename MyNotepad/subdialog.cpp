#include "subdialog.h"
#include "ui_subdialog.h"
#include "mainwindow.h"

SubDialog::SubDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubDialog)
{
    ui->setupUi(this);
    init();
}

SubDialog::~SubDialog()
{
    delete ui;
}

void SubDialog::init()
{
//    this->setAttribute(Qt::WA_ShowWithoutActivating,true);
    this->setFocusPolicy(Qt::NoFocus);
    connect(ui->findButton, SIGNAL(clicked()),
            this, SLOT(sendFindSignal()));
    connect(ui->replaceButton, SIGNAL(clicked()),
            this, SLOT(sendReplaceSignal()));
    connect(ui->cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

QString SubDialog::getFindStr()
{
    return ui->findStrEdit->text();
}

QString SubDialog::getReplaceStr()
{
    return ui->replaceStrEdit->text();
}

bool SubDialog::getDirection()
{
    if(ui->upRadioButton->isChecked()) // defaut : down
    {
        return false;
    }
    return true;
}

bool SubDialog::getCaseSensitive()
{
    if(ui->CasecheckBox->isChecked())
    {
        return true;
    }
    return false;
}

void SubDialog::sendFindSignal()
{
    emit findSignal();
}

void SubDialog::sendReplaceSignal()
{
    emit replaceSignal();
}
