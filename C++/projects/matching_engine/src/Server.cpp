#include "../include/Server.hpp"

Server::Server(MatchingEngine& engine, int port)
        : m_engine (engine)
{
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        m_socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if(m_socketfd == INVALID_SOCKET) return;

        struct sockaddr_in addr;
        addr.sin_family         = AF_INET;
        addr.sin_port           = htons(static_cast<u_short>(port));
        addr.sin_addr.s_addr    = INADDR_ANY;

        int bindfd = bind(m_socketfd, (struct sockaddr*)&addr, sizeof(addr));
        if(bindfd == -1) {
                closesocket(m_socketfd);
                return;
        }

        int listenfd = listen(m_socketfd, 5);
        if(listenfd == -1) {
                closesocket(m_socketfd);
                return;
        }

}

Server::~Server() {
        closesocket(m_socketfd);
        WSACleanup();
}

void Server::run() {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        while(true) {
                SOCKET clientfd = accept(m_socketfd, (struct sockaddr*)&client_addr, &client_len);
                if(clientfd == INVALID_SOCKET) {
                        closesocket(m_socketfd);
                        return;
                }
                std::thread t([clientfd, this]() -> void {
                        Order order;
                        int recvfd {};
                        while((recvfd = recv(clientfd, reinterpret_cast<char*>(&order), sizeof(order), 0)) > 0) {
                                order.client = clientfd;
                                m_engine.submit_order(order);
                        }
                        closesocket(clientfd);
                });
                t.detach();
        }
}
