#include "connecter.h"
#include <string.h>
#include <arpa/inet.h>
#include "mainwindow.h"
#include "config.h"
#include <fstream>
#include <regex>
#include <iostream>

connecter::connecter(int connfd, MainWindow *ui, string &dir):mySocket(connfd,ui){
    this->dir=dir;
    struct sockaddr_in     clntaddr;
    memset(&clntaddr, 1, sizeof(clntaddr));
    socklen_t clntlen;
    memset(&clntlen, 1, sizeof(clntlen));
    getpeername(connfd, (struct sockaddr*)&clntaddr, &clntlen);
    sPort=clntaddr.sin_port;
    sAddr=clntaddr.sin_addr.s_addr;
}
connecter::~connecter() {
    string str="Connection with "+stringifyAP()+" terminated";
    emit log(str);
}

string connecter::stringifyAP() {
    struct in_addr address;
    address.s_addr=sAddr;
    string addrStr= inet_ntoa(address);
    return addrStr+':'+to_string(ntohs(sPort));
}


void connecter::run(){
    char recvBuf[MAXBUFF];
    char sendBuf[MAXBUFF];
    int httpStatus=200;//http error code
    bool sendErrPage=false;//set true if need to send error page
    int bufLen=0;//length of send buffer
    if(!this->read(recvBuf,MAXBUFF)){
        string errLog="Read error";
        emit err(errno, errLog);
        return ;
    }
    else{
        string URL,contentType,response;
        string str="Connection with "+this->stringifyAP()+" established";
        emit log(str);

        //check if the request have a proper header line
        smatch headLine;
        regex HLPattern("(GET) +(.*) +(HTTP/[0-9].[0-9])");
        string recvBufText=recvBuf;
        if(!regex_search(recvBufText,headLine,HLPattern)){
            httpStatus=400;
            sendErrPage=true;
            str="Invalid Request header line from "+this->stringifyAP();
            emit log(str);
        }
        else{
            string method=headLine[1];
            URL=headLine[2];
            string version=headLine[3];
            str="Request header line: "+method+" "+URL+" "+version +" (source: "+this->stringifyAP()+")";
            emit log(str);
            if(URL=="/")
                URL="/index.html";//set index.html as index page
            URL=dir+URL;

            /*check if the request URL has a extension and set the content type accordingly*/
            smatch extension;
            regex extensionPattern("\\.[A-Za-z]+");
            if(!regex_search(URL,extension,extensionPattern)){
                httpStatus=404;//if request URL has no extension, respond 404
                sendErrPage=true;
            }
            else {
                string ext = extension[0];
                if (ext == ".html")
                    contentType = "text/html";
                else if (ext == ".xml")
                    contentType = "text/xml";
                else if (ext == ".css")
                    contentType = "text/css";
                else if (ext == ".png")
                    contentType = "image/png";
                else if (ext == ".gif")
                    contentType = "image/gif";
                else if (ext == ".jpg")
                    contentType = "image/jpg";
                else if (ext == ".jpeg")
                    contentType = "image/jpeg";
                else
                    contentType = "text/plain";
            }
        }
        if(httpStatus==200){
            fstream f;
            f.open(URL);
            if (!f.is_open()){
                httpStatus=404;
                if(contentType=="text/html")
                    sendErrPage=true;
            }
            else{
                response="HTTP/1.1 200 OK\r\nContent-type: "+contentType+"\r\n\r\n";
                strcpy(sendBuf,response.c_str());
                f.read(sendBuf+response.length(),MAXBUFF-response.length());
                bufLen=response.length()+f.gcount();
                f.close();
            }
        }
        if(httpStatus!=200){
            switch(httpStatus){
                case 400:{
                    response="HTTP/1.1 400 Bad Request\r\nContent-type: text/html\r\n\r\n";
                    strcpy(sendBuf,response.c_str());
                    fstream f;
                    string errURL="400.html";
                    errURL=ERRPAGE+errURL;
                    f.open(errURL);
                    f.read(sendBuf+response.length(),MAXBUFF-response.length());
                    bufLen=response.length()+f.gcount();
                    f.close();
                    break;
                }
                case 404:{
                    if(sendErrPage){
                        response="HTTP/1.1 404 Not Found\r\nContent-type: text/html\r\n\r\n";
                        strcpy(sendBuf,response.c_str());
                        fstream f;
                        string errURL="404.html";
                        errURL=ERRPAGE+errURL;
                        f.open(errURL);
                        f.read(sendBuf+response.length(),MAXBUFF-response.length());
                        bufLen=response.length()+f.gcount();
                        f.close();
                    }
                    else{
                        response="HTTP/1.1 404 Not Found";
                        strcpy(sendBuf,response.c_str());
                        bufLen=response.length();
                    }
                    break;
                }
                default:
                    break;
            }
        }
        if(this->write(sendBuf,bufLen)){
            string strStatus;
            switch(httpStatus){
                case 200:
                    strStatus="200 OK";
                    break;
                case 400:
                    strStatus="400 Bad Request";
                    break;
                case 404:
                    strStatus="404 Not Found";
                    break;
                default:
                    break;
            }
            str="Response to "+this->stringifyAP()+": "+strStatus;
            emit log(str);
        }
        this->close();
    }
}

