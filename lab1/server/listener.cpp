#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include "listener.h"
#include "mySocket.h"
#include "handler.h"
#include <iostream>

listener::listener(MainWindow *ui):mySocket(ui),running(false),ui(ui){
    connect(ui,SIGNAL(stopServer()),this,SLOT(stop()),Qt::DirectConnection);
}
listener::~listener()=default;

void listener::start(){
    this->running=true;
    if(!bind(port,addr)){
        this->running=false;
        string str="Server failed to start";
        emit err(str);
        return ;
    }
    if(!listen()){
        this->running=false;
        string str="Server failed to start";
        emit err(str);
        return ;
    }
    string str="Server is now listening at " + stringifyAP();
    emit log(str);
    while (running){
        fd_set lfd;
        struct timeval tv;
        FD_ZERO(&lfd);
        FD_SET(socketID,&lfd);
        tv.tv_sec=1;
        tv.tv_usec=0;
        if(!select(socketID+1,&lfd,nullptr,nullptr,&tv))
            continue;
        else{
            int sId=accept();
            if (sId==-1)
                continue;
            std::thread newThread(handler,sId,this->ui,dir);
            newThread.detach();
        }
    }
    str="Server stopped";
    emit log(str);
}
void listener::stop(){
    this->running=false;
}

void listener::setAddr(string &strAddr){
    struct in_addr address;
    inet_aton(strAddr.c_str(),&address);
    this->addr=address.s_addr;
}
void listener::setPort(string &strPort){
    this->port=htons((unsigned short)strtoul(strPort.c_str(),NULL,0));
}
void listener::setDir(string &strDir){
    this->dir=strDir;
}


string listener::getAddr(){
    struct in_addr address;
    address.s_addr=this->addr;
    return inet_ntoa(address);
}
string listener::getPort(){
    return to_string(this->port);
}
string listener::getDir(){
    return this->dir;
}

bool listener::getState(){
    return this->running;
}

string listener::stringifyAP() {
    struct in_addr address;
    address.s_addr=addr;
    string addrStr= inet_ntoa(address);
    return addrStr+':'+to_string(ntohs(port));
}
