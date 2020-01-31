#include "handler.h"

#include <iostream>

void handler(int connfd, MainWindow *ui, string dir){
    connecter connSocket(connfd, ui, dir);
    connSocket.run();
}