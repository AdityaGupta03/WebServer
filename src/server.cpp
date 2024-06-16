#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <csignal>


using namespace std;

// Globals
string usage = "Usage: WebServer [port-number]\n"
               "OR WebServer";

// Functions
void writeRes(int workerSocket, std::string payload);
void processReq(int workerSocket);
void startServer();
void handleZombies();


extern "C" void disp(int sig)
{
    if (sig == SIGCHLD) { // kill zombies
        while(waitpid(-1, nullptr, WNOHANG));
    }
}


void handleZombies()
{
    // Create sigaction handler to catch zombie processes on fork
    struct sigaction sa_z;
    sa_z.sa_handler = disp;
    sigemptyset(&sa_z.sa_mask);
    sa_z.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa_z, nullptr)) {
        std::cerr << "Error: sigaction" << std::endl;
        exit(EXIT_FAILURE);
    }
}


void startServer(int port)
{
    // Create master socket to accept connections
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error: socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set socket options
    int optval = 0;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        std::cerr << "Error: setsockopt" << std::endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverIP;
    serverIP.sin_family = AF_INET;
    serverIP.sin_addr.s_addr = INADDR_ANY;
    serverIP.sin_port = htons(port);

    int err;
    // Bind master socket to port
    err = bind(serverSocket, (struct sockaddr*)&serverIP, sizeof(serverIP));
    if (err < 0) {
        std::cerr << "Error: bind" << std::endl;
        exit(EXIT_FAILURE);
    }

    err = listen(serverSocket, 1);
    if (err < 0) {
        std::cerr << "Error: listen" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Started Server. Waiting for connection...\n\n"
                 "Expected credentials...\nUsername: aditya\nPassword: aditya\n"
                 << std::endl;

    while (true) {
        struct sockaddr_in clientIP;
        socklen_t clientIPLen = sizeof(clientIP);
        int workerSocket = accept(serverSocket, (sockaddr*)(&clientIP), (socklen_t*)(&clientIPLen));
        if (workerSocket < 0) {
            std::cerr << "Error: accept" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Client accepted. Creating new process..." << std::endl;

        int pid = fork();
        if (pid == 0) { // child process
            std::cout << "Child process created. Handling Request..." << std::endl;
            // processReq(workerSocket);
            close(workerSocket);
        } else if (pid == -1) {
            std::cerr << "Error: fork" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}


void writeRes(int workerSocket, std::string payload)
{
    write(workerSocket, "HTTP/1.1 200 OK\r\n", 17);
    write(workerSocket, "Content-Type: text/html\r\n", 25);
    write(workerSocket, "Server: SimpleWebServer\r\n", 25);
    write(workerSocket, "Connection: keep-alive\r\n", 22);
    write(workerSocket, "\r\n", 2);
    write(workerSocket, "The current time is:", 12);
    write(workerSocket, payload.c_str(), payload.size());
}


int main(int argc, char **argv)
{
    cout << "Welcome to C++ HTTP WebServer!" << "\n" << endl;

    int port;
    if (argc == 1) { // No port specified
        port = 8080;
    } else if (argc == 2) { // Port specified in second arg
        try {
            port = stoi(argv[1]);
        } catch (out_of_range& e) {
            cerr << "Error: port out of range of integer" << endl;
            exit(EXIT_FAILURE);
        } catch (invalid_argument& e) {
            cerr << "Error: port cast error" << endl;
            exit(EXIT_FAILURE);
        }
    } else { // Incorrect usage of program
        cout << usage << endl;
        exit(EXIT_SUCCESS);
    }

    cout << "Port: " << port << endl;
    handleZombies();
    startServer(port);
}
