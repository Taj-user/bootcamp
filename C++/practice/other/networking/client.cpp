#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

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
        inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

        if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
                closesocket(sockfd);
                return -1;
        }

        for(int i = 0; i < 3; i++) {
                const char* msg = "Hello world from client.";
                send_all(sockfd, msg, static_cast<int>(strlen(msg)));

                char buffer[1024];
                int bytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
                buffer[bytes] = '\0';
                std::cout << buffer << "\n";
        }


        closesocket(sockfd);

        WSACleanup();

        return 0;
}
