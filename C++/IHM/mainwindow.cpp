#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFont>
#include <QDesktopWidget>
#include <QPlainTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QString>
#include <QDate>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Setup base UI (see mainwindow.ui)
    ui->setupUi(this);

    // Button effects
    QWidget::connect(ui->buttonForward, SIGNAL(clicked()), this, SLOT(clickForward()));
    QWidget::connect(ui->buttonBackward, SIGNAL(clicked()), this, SLOT(clickBackward()));    
    QWidget::connect(ui->buttonLeft, SIGNAL(clicked()), this, SLOT(clickLeft()));    
    QWidget::connect(ui->buttonRight, SIGNAL(clicked()), this, SLOT(clickRight()));    
    QWidget::connect(ui->buttonStop, SIGNAL(clicked()), this, SLOT(clickStop()));    
    QWidget::connect(ui->buttonRec, SIGNAL(clicked()), this, SLOT(clickRec()));    
    QWidget::connect(ui->buttonStopRec, SIGNAL(clicked()), this, SLOT(clickStopRec()));
    QWidget::connect(ui->radioSecuLow, SIGNAL(clicked()), this, SLOT(securityLevel()));
    QWidget::connect(ui->radioSecuMed, SIGNAL(clicked()), this, SLOT(securityLevel()));
    QWidget::connect(ui->radioSecuHigh, SIGNAL(clicked()), this, SLOT(securityLevel()));

    // Information notification effect for each button
    QWidget::connect(ui->buttonForward, SIGNAL(clicked()), this, SLOT(scrollInfos()));
    QWidget::connect(ui->buttonBackward, SIGNAL(clicked()), this, SLOT(scrollInfos()));
    QWidget::connect(ui->buttonLeft, SIGNAL(clicked()), this, SLOT(scrollInfos()));
    QWidget::connect(ui->buttonRight, SIGNAL(clicked()), this, SLOT(scrollInfos()));
    QWidget::connect(ui->buttonStop, SIGNAL(clicked()), this, SLOT(scrollInfos()));
    QWidget::connect(ui->buttonRec, SIGNAL(clicked()), this, SLOT(scrollInfos()));
    QWidget::connect(ui->buttonStopRec, SIGNAL(clicked()), this, SLOT(scrollInfos()));
    QWidget::connect(ui->radioSecuLow, SIGNAL(clicked()), this, SLOT(scrollInfos()));
    QWidget::connect(ui->radioSecuMed, SIGNAL(clicked()), this, SLOT(scrollInfos()));
    QWidget::connect(ui->radioSecuHigh, SIGNAL(clicked()), this, SLOT(scrollInfos()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Return a string similar to : "YYYY/MM/DD HH:MM:SS - "
QString MainWindow::getDate() {
    int year = QDate::currentDate().year();
    int month = QDate::currentDate().month();
    int day = QDate::currentDate().day();
    QString time = QTime::currentTime().toString();
    QString res = QString::number(year)+"/"+QString::number(month)+"/"+QString::number(day)+" "+time+" - ";
    return res;
}

void MainWindow::clickForward() {
    ui->listInfos->addItem(getDate()+"Going forward");
}

void MainWindow::clickBackward() {
    ui->listInfos->addItem(getDate()+"Going backward");
}

void MainWindow::clickLeft() {
    ui->listInfos->addItem(getDate()+"Turning to the left");
}

void MainWindow::clickRight() {
    ui->listInfos->addItem(getDate()+"Turning to the right");
}

void MainWindow::clickStop() {
    ui->listInfos->addItem(getDate()+"Freeze all motor functions");
}

void MainWindow::clickRec() {
    QString s = ui->comboRec->currentText();
    int recorded = checkRecorded(s);
    if(recorded<0) {
        ui->listInfos->addItem(getDate()+"Recording "+s);
        ui->listCurrentRec->addItem(s);
    }
    else {
        ui->listInfos->addItem(getDate()+s+" is already in recording list");
    }
}

void MainWindow::clickStopRec() {
    QString s = ui->comboRec->currentText();
    int recorded = checkRecorded(s);
    if(recorded>=0) {
        ui->listInfos->addItem(getDate()+"Recording of "+s+" has stopped");
        QListWidgetItem *item = ui->listCurrentRec->item(recorded);
        delete item;
    }
    else {
        ui->listInfos->addItem(getDate()+s+" is not recorded");
    }

}

void MainWindow::scrollInfos() {
    int c = ui->listInfos->count();
    if( c > 200) {
        for(int row = 0; row < c-150; row++)
        {
                 QListWidgetItem *item = ui->listInfos->item(0);
                delete item;
        }
    }
    ui->listInfos->scrollToBottom();
}

void MainWindow::securityLevel() {
    QString res = getDate()+"Security level set to ";
    QString s;
    if(ui->radioSecuLow->isChecked()) {
        s = "Low";
    }
    else if(ui->radioSecuMed->isChecked()) {
        s = "Medium";
    }
    else {
        s = "High";
    }
    ui->listInfos->addItem(res+s);
}

int MainWindow::checkRecorded(QString s) {
    int c = ui->listCurrentRec->count();
    for(int row = 0; row < c; row++)
    {
             QListWidgetItem *item = ui->listCurrentRec->item(row);
             if (s==item->text()) {
                 return row;
             }
    }
    return -1;
}

