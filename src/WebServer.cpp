#include "WebServer.h"

extern "C" void disp(int sig) {
    if (sig == SIGCHLD) {
        while(waitpid(-1, nullptr, WNOHANG));
    }
}

WebServer::WebServer(int p) {
    port = p;
    masterSocket = -1;
}

WebServer::~WebServer() {
    port = -1;
    masterSocket = -1;
}

int WebServer::startServer() {
    // Create sigaction handler to catch zombie processes on fork
    struct sigaction sa_z{};
    sa_z.sa_handler = disp;
    sigemptyset(&sa_z.sa_mask);
    sa_z.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa_z, nullptr)) {
        std::cerr << "Error: sigaction" << std::endl;
        return -1;
    }

    std::cout << "Starting WebServer..." << std::endl;

    // Create master socket to accept connections
    masterSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (masterSocket < 0) {
        std::cerr << "Error: Creating master socket" << std::endl;
    }

    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Bind master socket to port
    if (bind(masterSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error: binding socket" << std::endl;
        return -1;
    }



    close(masterSocket);

    return 0;
}

int WebServer::writeHeaders() {
    // TODO: Not \implemented.
    return -1;
}