#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <thread>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initSignalSlots();

signals:
    void stopServer();

public slots:
    void on_startListen();
    void on_stopListen();
    void printInfo(string log);
    void printFatal(int errType, string log);
    void printFatal(string log);
    void printErr(string log);
private:
    Ui::MainWindow *ui;
    class thread * listenerThread;
    bool isListening;
    string addr;
    string port;
    string dir;
};

#endif // MAINWINDOW_H
