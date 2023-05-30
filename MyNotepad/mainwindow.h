#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QTextDocument>
#include <QPrintDialog>
#include <QPrinter>
#include <QDate>
#include <QFontDialog>
#include <QColorDialog>
#include <QLabel>
#include <QCloseEvent>
#include <QPalette>

#include "subdialog.h"

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
    SubDialog* _subDialogPtr;
    QString _saveDir;
    QString _saveBaseName;
    QLabel* _cursorInfoLabel;
//    QLabel* _zoomInfoLabel;


    void activateMainWindow();
    void init();
    int confrimModify();
    void closeEvent(QCloseEvent *);

    enum confrimCode
    {
        SAVED,
        DISCARD,
        CANCEL
    };

private slots:
    // File
    void newFileSlot();
    void openFileSlot();
    int saveFileSlot();
    int saveAsFileSlot();
    void printFileSlot();
    void exitSlot();

    // Edit
    void deleteSelectedSlot();
    void showFindDialogSlot();
    void findSlot();
    void advanceSlot();
    void nextSlot();
    void replaceSlot();
    void insertTimeSlot();


    // Options
    void autoWrapSlot();
    void setFontSlot();
    void setColorSlot();


    // View
    void statusSlot();
    void on_textEdit_cursorPositionChanged();
    void on_textEdit_textChanged();
};

#endif // MAINWINDOW_H
