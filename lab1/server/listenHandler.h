
#ifndef SERVER_LISTENHANDLER_H 
#define SERVER_LISTENHANDLER_H

#include <string>
#include "listener.h"
class MainWindow;
using namespace std;
void setLSocket( MainWindow *ui, string addr,string port, string dir, bool &t);
#endif //SERVER_LISTENHANDLER_H
