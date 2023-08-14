#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H

#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <csignal>

class WebServer {
    int masterSocket;
    int port;
    void writeRes(int workerSocket, std::string payload);
    void processReq(int workerSocket);

public:
    WebServer(int p);
    void startServer();
    ~WebServer();
};

#endif //WEBSERVER_SERVER_H

