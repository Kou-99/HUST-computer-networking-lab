
#include "listenHandler.h"
#include <iostream>

void setLSocket( MainWindow *ui, string addr,string port, string dir, bool &t){
    listener listenSocket(ui);
    listenSocket.setAddr(addr);
    listenSocket.setPort(port);
    listenSocket.setDir(dir);
    t=true;
    listenSocket.start();
    listenSocket.close();
    t=false;
}
