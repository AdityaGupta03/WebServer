#include "WebServer.h"

extern "C" void disp(int sig) {
    if (sig == SIGINT) { // server end

        exit(EXIT_SUCCESS);
    }
    if (sig == SIGCHLD) { // kill zombies
        while(waitpid(-1, nullptr, WNOHANG));
    }
}

WebServer::WebServer(int p) {
    port = p;
    masterSocket = -1;
}

WebServer::~WebServer() {
    port = -1;
    close(masterSocket);
}

void WebServer::startServer() {
    // Create sigaction handler to catch zombie processes on fork
    struct sigaction sa_z{};
    sa_z.sa_handler = disp;
    sigemptyset(&sa_z.sa_mask);
    sa_z.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa_z, nullptr)) {
        std::cerr << "Error: sigaction" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Starting Server..." << std::endl;

    // Create master socket to accept connections
    masterSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (masterSocket < 0) {
        std::cerr << "Error: socket" << std::endl;
    }

    struct sockaddr_in serverIP{};
    serverIP.sin_family = AF_INET;
    serverIP.sin_addr.s_addr = INADDR_ANY;
    serverIP.sin_port = htons(port);

    // Bind master socket to port
    int err;
    err = bind(masterSocket, (struct sockaddr*)&serverIP, sizeof(serverIP));
    if (err < 0) {
        std::cerr << "Error: bind" << std::endl;
        exit(EXIT_FAILURE);
    }

    err = listen(masterSocket, 1);
    if (err < 0) {
        std::cerr << "Error: listen" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Successfully started. Waiting for connection...\n\n"
                 "Expected credentials...\nUsername: aditya\nPassword: aditya\n"
                 << std::endl;

    while (true) {
        struct sockaddr_in clientIP{};
        socklen_t clientIPLen = sizeof(clientIP);
        int workerSocket = accept(masterSocket, (sockaddr*)(&clientIP), (socklen_t*)(&clientIPLen));
        if (workerSocket < 0) {
            std::cerr << "Error: accept" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Client accepted. Creating new process..." << std::endl;

        int pid = fork();
        if (pid == 0) { // child process
            std::cout << "Child process created. Handling Request..." << std::endl;
            processReq(workerSocket);
            _exit(EXIT_SUCCESS);
        } else if (pid == -1) {
            std::cerr << "Error: fork" << std::endl;
            exit(EXIT_FAILURE);
        }

        close(workerSocket);
    }
}

void WebServer::processReq(int workerSocket) {

}

int WebServer::writeRes(int workerSocket) {
    // TODO: Not implemented.
    return -1;
}