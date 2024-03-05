#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <thread>

using namespace std;

int conn_handler(int clientSocket) {
    cout << "handling thread id: " << std::this_thread::get_id() << endl;
    char buffer[1024] = {0};
    ::recv(clientSocket, buffer, sizeof(buffer), 0);

    // output requested object to terminal and trim off leading "/"
    char * tok;
    tok = strtok(buffer, " ");
    tok = strtok(NULL, " ");
    string object(tok);
    object.erase(object.begin());


    // get file type of object
    char *type;
    if (object != "") {
        type = strtok(tok, ".");
        type = strtok(NULL, ".");
    }
    string typeStr(type);

    // set the response string based on the request
    string response;
    if (object != "") {
        if (access(object.c_str(), F_OK) == -1) {
            response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 22\r\n\r\n404: Content Not Found";
            goto send;
        }
    }
    if (object == "") {
        // replies with plain text
        response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 5\r\n\r\nHello";
    } else if (typeStr == "html") {
        // html file handler
        ifstream infile(object);
        stringstream ss;
        ss << infile.rdbuf();
        string html_str = ss.str();
        response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + to_string(html_str.length())+ "\r\n\r\n"+ html_str;
    } else if (typeStr == "pdf") {
        // pdf file handler
        ifstream infile (object);
        stringstream ss;
        ss << infile.rdbuf();
        string pdf_str = ss.str();
        response = "HTTP/1.1 200 OK\r\nContent-Type: application/pdf\r\nContent-Length: " + to_string(pdf_str.length())+ "\r\n\r\n"+ pdf_str;
    }

    send:
    // send the response
    if (send(clientSocket, response.c_str(), response.length(), 0) < 0) {
        cerr << "Send failed" << endl;

        return 1;
    }

    // close sockets
    close(clientSocket);
    return 0;
}

int listenSocket(int serverSocket) {
    cout << "listen thread id: " << std::this_thread::get_id() << endl;
    if (listen(serverSocket, 10) < 0) {
        cerr << "Listen failed" << endl;
        return 1;
    }

    while (true) {
        // accept, and receive
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        cout << "clientSocket: " << clientSocket << endl;
        if (clientSocket < 0) {
            cerr << "Accept failed" << endl;
            return 1;
            continue;
        }
        thread newThread (conn_handler, clientSocket);
        newThread.detach();
    }
}
int main(int argc, char **argv) {

    if (argc != 2) {
        cerr << "usage: ./webserver <portNum>";
        return 1;
    }

    // create socket, set its options, and bind it to an address
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == 0) {
        cerr << "Socket creation failed" << endl;
        return 1;
    }

    cout << "serverSocket: " << serverSocket << endl;
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
        cerr << "Setsockopt failed" << endl;
        return 1;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    try {
        serverAddress.sin_port = htons(stoi(argv[1]));
    } catch (std::invalid_argument) {
        cerr << "usage: ./webserver <portNum>";
        return 1;
    }
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int bindRes = ::bind(serverSocket, (const struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (bindRes < 0) {
        cerr << "Bind failed" << endl;
        return 1;
    }

    // create a single thread for the listening socket
    thread lThread(listenSocket, serverSocket);
    lThread.detach();

    // loop and break on a "quit" command
    while (true) {
        sleep(1);
        string command;
        cin >> command;
        if (command == "quit") {
            break;
        }
    }

    close(serverSocket);

    return 0;
}