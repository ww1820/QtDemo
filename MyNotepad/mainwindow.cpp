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
    delete ui;
}

void MainWindow::activateMainWindow()
{
    if(!this->isActiveWindow()) //判断是否是活动窗口
    {
        this->activateWindow(); //设置成活动窗口
    }
}

void MainWindow::init()
{
    _subDialogPtr = new SubDialog(this);
    _cursorInfoLabel = new QLabel(ui->statusBar);
//    _zoomInfoLabel = new QLabel(ui->statusBar);

    _saveDir = "";
    _saveBaseName = "Untitled Document";
    this->setWindowTitle(_saveBaseName + " - MyNotepad");
    _cursorInfoLabel->setText("# line: 1, col: 1");
    _cursorInfoLabel->setContentsMargins(9,2,2,2);
    _cursorInfoLabel->adjustSize();

    // File 菜单
    connect(ui->actionNew_N, SIGNAL(triggered()),
            this, SLOT(newFileSlot()));
    connect(ui->actionOpen_O, SIGNAL(triggered()),
            this,SLOT(openFileSlot()));
    connect(ui->actionSave_S, SIGNAL(triggered()),
            this, SLOT(saveFileSlot()));
    connect(ui->actionSave_As_A, SIGNAL(triggered()),
            this, SLOT(saveAsFileSlot()));
    connect(ui->actionPrint_P, SIGNAL(triggered()),
            this, SLOT(printFileSlot()));
    connect(ui->actionExit_E, SIGNAL(triggered()),
            this, SLOT(exitSlot()));

    // Edit 菜单
    connect(ui->actionUndo_U, SIGNAL(triggered()),
            ui->textEdit, SLOT(undo()));
    connect(ui->actionRedo_R, SIGNAL(triggered()),
            ui->textEdit, SLOT(redo()));
    connect(ui->actionCut_T, SIGNAL(triggered()),
            ui->textEdit, SLOT(cut()));
    connect(ui->actionCopy_C, SIGNAL(triggered()),
            ui->textEdit,SLOT(copy()));
    connect(ui->actionPaste_P, SIGNAL(triggered()),
            ui->textEdit,SLOT(paste()));
    connect(ui->actionDelete_D, SIGNAL(triggered()),
            this, SLOT(deleteSelectedSlot()));
    connect(ui->actionFind_F, SIGNAL(triggered()),
            this, SLOT(showFindDialogSlot()));
    connect(ui->actionAdvance_V, SIGNAL(triggered()),
            this, SLOT(advanceSlot()));
    connect(ui->actionNext_N, SIGNAL(triggered()),
            this, SLOT(nextSlot()));
    connect(ui->actionSelect_All_A, SIGNAL(triggered()),
            ui->textEdit,SLOT(selectAll()));
    connect(ui->actionTime_Date_D,SIGNAL(triggered()),
            this, SLOT(insertTimeSlot()));

    // Options
    connect(ui->actionAuto_Wrap_W, SIGNAL(triggered()),
            this, SLOT(autoWrapSlot()));
    connect(ui->actionFont_F, SIGNAL(triggered()),
            this, SLOT(setFontSlot()));
    connect(ui->actionColor, SIGNAL(triggered()),
            this, SLOT(setColorSlot()));

    // View
    connect(ui->actionZoom_In_I, SIGNAL(triggered()),
            ui->textEdit, SLOT(zoomIn()));
    connect(ui->actionZoom_Out_O, SIGNAL(triggered()),
            ui->textEdit, SLOT(zoomOut()));
    connect(ui->actionStatus_S, SIGNAL(triggered()),
            this, SLOT(statusSlot()));

    // find&replace
    connect(_subDialogPtr, SIGNAL(findSignal()),
            this, SLOT(findSlot()));
    connect(_subDialogPtr, SIGNAL(replaceSignal()),
            this, SLOT(replaceSlot()));

}

int MainWindow::confrimModify()
{
    //如果当前文档内容改变
    if(ui->textEdit->document()->isModified())
    {
//        qDebug() << "The document is modified.";

        // 是否保存

        int ret = QMessageBox::warning(this, tr("MyNotepad"),
                                       tr("The document has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel,
                                       QMessageBox::Cancel);

        if (ret == QMessageBox::Save)
        {
            if(_saveDir.isEmpty())
            {
                return this->saveAsFileSlot();
            }
            else
            {
                return this->saveFileSlot();
            }
        }
        else if(ret == QMessageBox::Discard)
        {
            return DISCARD;
        }
        else
        {
            return CANCEL;
        }
    }
    return SAVED;
}

// File
void MainWindow::newFileSlot()
{
    if(this->confrimModify() == CANCEL) return;

    ui->textEdit->clear();
    _saveDir = "";
    _saveBaseName = "Untitled Document";
    this->setWindowTitle(_saveBaseName + "* - MyNotepad");
}

void MainWindow::openFileSlot()
{
    if(this->confrimModify() == CANCEL) return;

    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open File"), QDir::currentPath());  // 绝对路径

    if(fileName.isEmpty())
    {
//        QMessageBox::information(this, "Message","Canceled.");
        return;
    }

    QFile* qFile = new QFile(fileName);
    bool success = qFile->open(QIODevice::ReadOnly);

    if(success)
    {
        _saveDir = QFileInfo(fileName).absolutePath();
        _saveBaseName = QFileInfo(fileName).baseName();

        this->setWindowTitle(_saveBaseName+" - MyNotepad");
        QTextStream in(qFile);
        ui->textEdit->setText(in.readAll());  // 读出文件流中所有内容
        this->setWindowTitle(_saveBaseName + " - MyNotepad");
        // 释放资源
        qFile->close();
    }
    else
    {
        QMessageBox::information(
                    this, "Error Message","Failed to open the file!");
    }
    delete qFile;
}

int MainWindow::saveFileSlot()
{
    if(_saveDir.isEmpty() || _saveBaseName.isEmpty())  //保存路径为空
    {
        return this->saveAsFileSlot();
    }

//    qDebug() << "Dir: " << _saveDir;
//    qDebug() << "BaseName: " << _saveBaseName;

    QString fileName = _saveDir +"/"+ _saveBaseName;

//    qDebug() <<"fileName: " << fileName;

    QFile* qFile = new QFile(fileName);
    bool success = qFile->open(QIODevice::WriteOnly);

    if(success)
    {
        QTextStream out(qFile);
        out << ui->textEdit->toPlainText();
        ui->textEdit->document()->setModified(false);
        this->setWindowTitle(_saveBaseName + " - MyNotepad");
        qFile->close();
        delete qFile;
        return SAVED;
    }
    else
    {
        QMessageBox::information(
                    this, "Error Message","Failed to save the file!");
        delete qFile;
        return CANCEL;
    }


}

int MainWindow::saveAsFileSlot()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, "Save as...", "/home/wwu/Documents/"+_saveBaseName);

    if(fileName.isEmpty())
    {
//        QMessageBox::information(this, "Message","Canceled.");
        return CANCEL;
    }

    QFile *qFile = new QFile(fileName);
    bool success = qFile->open(QIODevice::WriteOnly);

    if(success)
    {
        _saveDir = QFileInfo(fileName).absolutePath();
        _saveBaseName = QFileInfo(fileName).baseName();

        QTextStream out(qFile);
        out << ui->textEdit->toPlainText();

        this->setWindowTitle(_saveBaseName+" - MyNotepad");
        ui->textEdit->document()->setModified(false);

        qFile->close();
        delete qFile;
        return SAVED;
    }
    else
    {
        QMessageBox::information(
                    this, "Error Message","Failed to save the file!");
        delete qFile;
        return CANCEL;
    }
}

void MainWindow::printFileSlot()
{
    QPrinter qPrinter;
    QPrintDialog printDialog(&qPrinter); // 选择打印设备

    if (printDialog.exec() == QDialog::Accepted) {

        ui->textEdit->document()->print(&qPrinter);  // 打印

        QMessageBox::information(this, "MyNotepad","Successed!");
      }
    else
    {
        QMessageBox::information(this, "MyNotepad","Canceled!");
    }
}

void MainWindow::exitSlot()
{
    close();
}

// Edit
void MainWindow::deleteSelectedSlot()
{
    ui->textEdit->textCursor().removeSelectedText();
}

void MainWindow::showFindDialogSlot()
{
    _subDialogPtr->show();
}


void MainWindow::findSlot()
{
    bool dir = _subDialogPtr->getDirection();
    if(dir)
    {
        nextSlot();
    }
    else
    {
        advanceSlot();
    }
    activateMainWindow();
}

void MainWindow::advanceSlot()// forward
{
    QString findStr = _subDialogPtr->getFindStr();
    QTextCursor qTextCursor = ui->textEdit->textCursor();

    if(findStr.isEmpty())
    {
        QMessageBox::warning(this, "MyNotepad",
                                 "The string to search should not be empty!");
        return;
    }

    if(_subDialogPtr->getCaseSensitive())
    {
        qTextCursor = ui->textEdit->document()->find(
                    findStr, qTextCursor, QTextDocument::FindCaseSensitively
                    | QTextDocument::FindBackward);
    }
    else
    {
        qTextCursor = ui->textEdit->document()->find(
                    findStr, qTextCursor, QTextDocument::FindBackward);
    }

    if(qTextCursor.selectedText().isEmpty())
    {
        QMessageBox::warning(this, "MyNotepad",
                             tr("Cannot find \"%1\"!").arg(findStr));
        return;
    }
    ui->textEdit->setTextCursor(qTextCursor);
}

void MainWindow::nextSlot()// backward
{
    QString findStr = _subDialogPtr->getFindStr();
    QTextCursor qTextCursor = ui->textEdit->textCursor();

    if(findStr.isEmpty())
    {
        QMessageBox::warning(this, "MyNotepad",
                                 "The string to search should not be empty!");
        return;
    }

    if(_subDialogPtr->getCaseSensitive())
    {
        qTextCursor = ui->textEdit->document()->find(
                    findStr, qTextCursor, QTextDocument::FindCaseSensitively);
    }
    else
    {
        qTextCursor = ui->textEdit->document()->find(
                    findStr, qTextCursor);
    }

    if(qTextCursor.selectedText().isEmpty())
    {
        QMessageBox::information(this, "MyNotepad",
                             tr("Cannot find \"%1\"!").arg(findStr));
        return;
    }

    ui->textEdit->setTextCursor(qTextCursor);
}

void MainWindow::replaceSlot()
{

    QString findStr = _subDialogPtr->getFindStr();
    QString replaceStr = _subDialogPtr->getReplaceStr();
    QString seletedStr = ui->textEdit->textCursor().selectedText();

    if(findStr.isEmpty())
    {
        QMessageBox::information(this, "MyNotepad",
                                 "The string to search should not be empty!");
        return;
    }

    bool flag = _subDialogPtr->getCaseSensitive();
    if(!((flag && seletedStr.compare(findStr) == 0)
         || (!flag && seletedStr.compare(findStr, Qt::CaseInsensitive) == 0)))
    {
        findSlot();
    }
    ui->textEdit->textCursor().removeSelectedText();
    ui->textEdit->insertPlainText(replaceStr);

    QTextCursor qTextCursor = ui->textEdit->textCursor();
    int end = qTextCursor.position();
    int start = end - replaceStr.length();
//    qDebug() << start << endl;
//    qDebug() << end << endl;
    qTextCursor.setPosition(start,QTextCursor::MoveAnchor);
    qTextCursor.setPosition(end,QTextCursor::KeepAnchor);
    ui->textEdit->setTextCursor(qTextCursor);

    activateMainWindow();
}

void MainWindow::insertTimeSlot()
{
    QString qTimeDate =
            QDateTime::currentDateTime().toString("hh:mm yyyy/MM/dd");
    ui->textEdit->insertPlainText(qTimeDate);
}

// Options
void MainWindow::autoWrapSlot()
{
    if(ui->textEdit->lineWrapMode() == QTextEdit::NoWrap)
    {
        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    }
    else
    {
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }
}

void MainWindow::setFontSlot()
{
    bool success;
    QFont qFont = QFontDialog::getFont(
                &success, ui->textEdit->currentFont(), this);
    if (success) {
      // font is set to the font the user selected
        ui->textEdit->setFont(qFont);
    }
}

void MainWindow::setColorSlot()
{
    QColor qColor = ui->textEdit->palette().color(QPalette::Text);
    qColor = QColorDialog::getColor(qColor, this);
    if(qColor.isValid())
    {
        QPalette p = ui->textEdit->palette();
        p.setColor(QPalette::Text, qColor); // QPalette::WindowText 无效
        ui->textEdit->setPalette(p);
    }
}

void MainWindow::statusSlot()
{
    if(ui->statusBar->isVisible())
    {
        ui->statusBar->setVisible(false);
    }
    else
    {
        ui->statusBar->setVisible(true);
    }
}



void MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor qTextCursor = ui->textEdit->textCursor(); //当前光标
    int rowNum = qTextCursor.blockNumber() + 1;//获取光标所在行的行号
//    int colNum = qTextCursor.columnNumber() + 1;
    int colNum = qTextCursor.positionInBlock() +1;
    _cursorInfoLabel->setText(
                "# line: " + QString::number(rowNum) +
                ", col: " + QString::number(colNum));
    _cursorInfoLabel->adjustSize();
}

void MainWindow::on_textEdit_textChanged()
{
    this->setWindowTitle(_saveBaseName + "* - MyNotepad");
}


// 退出前检查是否保存
void MainWindow::closeEvent(QCloseEvent * e)
{
    if(this->confrimModify() == CANCEL)
    {
        e->ignore();
    }
    else
    {
        e->accept();
    }
}

