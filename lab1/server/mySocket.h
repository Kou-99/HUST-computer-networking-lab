#ifndef SERVER_MYSOCKET_H
#define SERVER_MYSOCKET_H

#include <sys/socket.h>
#include <string>
#include <QtCore/QObject>
#include "mainwindow.h"


using std::string;

class mySocket: public QObject
{

    Q_OBJECT

    protected:
        int socketID;

    public:
        explicit mySocket(MainWindow *ui);
        explicit mySocket(int num, MainWindow *ui);
        ~mySocket();

        /*basic operations with socket*/
        bool bind(unsigned short port, unsigned long addr);
        bool listen();
        int accept();
        bool read(char * recvBuf,int n);
        bool write(char * sendBuf, int n);
        void close();

    signals:
        void err(int, string);
        void err(string);
        void log(string);



};

#endif //SERVER_MYSOCKET_H
