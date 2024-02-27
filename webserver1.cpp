#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream>
using namespace std;
int main(int argc, char **argv) {
    // wait for request
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    while (true) {
        listen(serverSocket, 5);
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << buffer << endl;
        
        stringstream s(buffer);
        char * get;
        char * file;
        //s >> get >> file;

        //cout << file << endl;
        

    }
    return 0;
}