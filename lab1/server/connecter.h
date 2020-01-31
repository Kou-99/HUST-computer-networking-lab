

#ifndef SERVER_CONNECTER_H
#define SERVER_CONNECTER_H

#include "mySocket.h"
#include <sys/socket.h>
#include <netinet/in.h>

class connecter: public mySocket {

Q_OBJECT

public:
    unsigned short sPort;//in network order
    unsigned long sAddr;//in network order
    string dir;


public:
    explicit connecter(int connfd, MainWindow *ui, string &dir);
    ~connecter();

    void run();

    /*return address and port in format "address:port"*/
    /*note that port and address should be in network order*/
    string stringifyAP();
};

#endif //SERVER_CONNECTER_H
