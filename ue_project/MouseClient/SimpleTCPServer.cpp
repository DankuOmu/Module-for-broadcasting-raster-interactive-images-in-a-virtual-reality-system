// SimpleTCPServer.cpp
#include <winsock2.h>
#include <ws2tcpip.h>
#include <filesystem>
#include <iostream>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    std::cout << "Server listening on 127.0.0.1:12345...\n";

    char data[] = "image.jpg";
    int len = strlen(data);

    /*FILE* fp = fopen("image.jpg", "r");
    fseek(fp, 0L, SEEK_END);
    size_t len = ftell(fp);
    fclose(fp);

    std::ifstream f("image.jpg");

    char* data = new char[len];
    f.read(data, len);*/
        
    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::cout << "Client connected!" << std::endl;

        char buffer[1024];

        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        while (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "Received: " << buffer << std::endl;

            int iSendResult = send(clientSocket, data, len, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(clientSocket);
                WSACleanup();
                return 1;
            }

            printf("Bytes sent: %d\n", iSendResult);

            bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        }

        closesocket(clientSocket);
    }


    return 0;
}
