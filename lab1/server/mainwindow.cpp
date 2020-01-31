#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "listenHandler.h"
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isListening(false),
    listenerThread(nullptr)
{
    ui->setupUi(this);
    initSignalSlots();
    setWindowTitle("Server");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSignalSlots() {
    connect(ui->startButt,SIGNAL(clicked()),this,SLOT(on_startListen()));
    connect(ui->stopButt,SIGNAL(clicked()),this,SLOT(on_stopListen()));
}
void MainWindow::on_startListen() {
    if(isListening){
        string str="There is a server listening at " + addr + ':' + port + ". If you wish to listen at a new port, please stop this server first.";
        printErr(str);
        return;
    }
    else{
        addr=ui->addressText->text().toStdString();
        port=ui->portText->text().toStdString();
        dir=ui->pathText->text().toStdString();
        listenerThread= new class thread (setLSocket,this,addr,port,dir,ref(isListening));
    }
}

void MainWindow::on_stopListen() {
    if(!isListening){
        string str="There is no server running at the moment.";
        printErr(str);
    }
    else{
        emit stopServer();
    }
}

void MainWindow::printInfo(string log){
    time_t t=time(nullptr);
    char tmp[64];
    strftime(tmp, sizeof(tmp),"%Y/%m/%d %T",localtime(&t));
    string time=tmp;
    string logMessage="[info] "+time+" "+log;
    ui->Log->append(QString::fromStdString(logMessage));
}

void MainWindow::printFatal(int errType, string log){
    time_t t=time(nullptr);
    char tmp[64];
    strftime(tmp, sizeof(tmp),"%Y/%m/%d %T",localtime(&t));
    string time=tmp;
    string ErrMessage="[fatal] "+time+" "+log + ':' + strerror(errType) + "(errno:" + to_string(errType) +')';
    ui->Log->append(QString::fromStdString(ErrMessage));
    QTextCursor cursor=ui->Log->textCursor();
    cursor.select(QTextCursor::BlockUnderCursor);
    QTextCharFormat fmt;
    fmt.setForeground(QColor(Qt::red));
    cursor.mergeCharFormat(fmt);
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::EndOfBlock);
}

void MainWindow::printFatal(string log){
    time_t t=time(nullptr);
    char tmp[64];
    strftime(tmp, sizeof(tmp),"%Y/%m/%d %T",localtime(&t));
    string time=tmp;
    string ErrMessage="[fatal] "+time+" "+log;
    ui->Log->append(QString::fromStdString(ErrMessage));
    QTextCursor cursor=ui->Log->textCursor();
    cursor.select(QTextCursor::BlockUnderCursor);
    QTextCharFormat fmt;
    fmt.setForeground(QColor(Qt::red));
    cursor.mergeCharFormat(fmt);
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::EndOfBlock);
}

void MainWindow::printErr(string log){
    time_t t=time(nullptr);
    char tmp[64];
    strftime(tmp, sizeof(tmp),"%Y/%m/%d %T",localtime(&t));
    string time=tmp;
    string ErrMessage="[err] "+time+" "+log;
    ui->Log->append(QString::fromStdString(ErrMessage));
    QTextCursor cursor=ui->Log->textCursor();
    cursor.select(QTextCursor::BlockUnderCursor);
    QTextCharFormat fmt;
    fmt.setForeground(QColor(Qt::darkYellow));
    cursor.mergeCharFormat(fmt);
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::EndOfBlock);
}