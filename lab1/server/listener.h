#ifndef SERVER_LISTENER_H
#define SERVER_LISTENER_H

#include "mySocket.h"
#include <string>
#include <QObject>


using namespace std;

class listener: public mySocket {

Q_OBJECT

private:
    volatile bool running;
    MainWindow *ui;

protected:
    unsigned short port;//in network order
    unsigned long addr;//in network order
    string dir;


public:
    explicit listener(MainWindow *ui);
    ~listener();

    void start();
    void setAddr(string &addr);
    void setPort(string &port);
    void setDir(string &dir);

    string getAddr();
    string getPort();
    string getDir();
    bool getState();

    string stringifyAP();

public slots:
    void stop();
};

#endif //SERVER_LISTENER_H