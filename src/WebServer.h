#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <csignal>

#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H

class WebServer {
    int masterSocket;
    int port;
    int writeRes(int workerSocket);
    void processReq(int workerSocket);

public:
    WebServer(int p);
    void startServer();
    ~WebServer();
};

#endif //WEBSERVER_SERVER_H

