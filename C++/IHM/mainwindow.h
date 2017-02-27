#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString getDate();
    int checkRecorded(QString s);

public slots:
    void clickForward();
    void clickBackward();
    void clickLeft();
    void clickRight();
    void clickStop();
    void clickRec();
    void clickStopRec();
    void scrollInfos();
    void securityLevel();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
