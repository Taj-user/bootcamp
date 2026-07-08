#include <thread>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

bool send_all(SOCKET fd, const char* buffer, int length);

void handleClient(SOCKET clientfd) {
        char buffer[1024];
        int recvfd {};
        while((recvfd = recv(clientfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
                buffer[recvfd] = '\0';
                std::cout << buffer << "\n";
                const char* response = "Message received";
                send_all(clientfd, response, static_cast<int>(strlen(response)));
        }

        closesocket(clientfd);
}

bool send_all(SOCKET fd, const char* buffer, int length) {
        int total = 0;
        while(total < length) {
                int sent = send(fd, buffer + total, length - total , 0);
                if(sent == -1) return false;
                total += sent;
        }
        return true;
}

int main(void) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == INVALID_SOCKET) return -1;

        struct sockaddr_in addr;
        addr.sin_family         = AF_INET;
        addr.sin_port           = htons(8080);
        addr.sin_addr.s_addr    = INADDR_ANY;

        int bindfd = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
        if(bindfd == -1) {
                closesocket(sockfd);
                return -1;
        }

        int listenfd = listen(sockfd, 5);
        if(listenfd == -1) {
                closesocket(sockfd);
                return -1;
        }

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        while(true) {
                SOCKET clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
                if(clientfd == INVALID_SOCKET) {
                        closesocket(sockfd);
                        return -1;
                }
                std::thread t(handleClient, clientfd);
                t.detach();
        }

        closesocket(sockfd);

        WSACleanup();

        return 0;
}
