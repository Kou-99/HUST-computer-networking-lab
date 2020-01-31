#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

#include "mySocket.h"
#include "config.h"
#include <QMetaType>

mySocket::mySocket(MainWindow *ui){
    qRegisterMetaType<string>("string");
    socketID=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(this,SIGNAL(err(int,string)),ui,SLOT(printFatal(int,string)));
    connect(this,SIGNAL(err(string)),ui,SLOT(printFatal(string)));
    connect(this,SIGNAL(log(string)),ui,SLOT(printInfo(string)));
    if(socketID==-1){
        string errLog="Fail to create socket";
        emit err(errno,errLog);
    }
}

mySocket::mySocket(int num, MainWindow *ui){
    connect(this,SIGNAL(err(int,string)),ui,SLOT(printFatal(int,string)));
    connect(this,SIGNAL(log(string)),ui,SLOT(printInfo(string)));
    socketID=num;
}

mySocket::~mySocket()=default;

bool mySocket::bind(unsigned short port, unsigned long addr){
    struct sockaddr_in     servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = addr;
    servaddr.sin_port = port;
    if(::bind(this->socketID, (struct sockaddr*)&servaddr, sizeof(servaddr))==-1){
        string errLog="Bind error";
        emit err(errno,errLog);
        return false;
    }
    return true;
}
bool mySocket::listen(){
    if(::listen(this->socketID, backlogNum)==-1){
        string errLog="Listen error";
        emit err(errno,errLog);
        return false;
    }
    return true;
}

int mySocket::accept(){
    struct sockaddr connSocketAddr;
    unsigned int addr_len= sizeof(struct sockaddr);
    int connfd=::accept(this->socketID, &connSocketAddr, &addr_len);
    if(connfd==-1){
        string errLog="Accept error";
        emit err(errno,errLog);
    }
    return connfd;
}

bool mySocket::read(char * recvBuf,int len){
    if(::read(this->socketID,recvBuf,len)==-1){
        string errLog="Read error";
        emit err(errno,errLog);
        return false;
    }
    return true;
}

bool mySocket::write(char * sendBuf, int len){
    if(::write(this->socketID,sendBuf,len)==-1){
        string errLog="Write error";
        emit err(errno,errLog);
        return false;
    }
    return true;
}

void mySocket::close(){
    if(::close(this->socketID)==-1){
        string errLog="Close error";
        emit err(errno,errLog);
    }
}




