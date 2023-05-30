#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void flushBar();

private:
    Ui::MainWindow *ui;
    QTimer* myTimer;
    int cnt;

    void init();
};

#endif // MAINWINDOW_H
