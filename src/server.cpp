#include <iostream>

#include "WebServer.h"

using namespace std;

string usage = "Usage: WebServer [port-number]\n"
               "OR WebServer";

int main(int argc, char **argv) {

    cout << "Welcome to C++ HTTP WebServer!\n" << endl;

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

    // Create and start webserver service
    WebServer *server;
    server = new WebServer(port);
    int err = server->startServer();
    if (err == -1) exit(EXIT_FAILURE); // Web server failure

    return 0;

}