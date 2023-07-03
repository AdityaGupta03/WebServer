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
    int writeHeaders();

public:
    WebServer(int p);
    int startServer();
    ~WebServer();
};

#endif //WEBSERVER_SERVER_H

