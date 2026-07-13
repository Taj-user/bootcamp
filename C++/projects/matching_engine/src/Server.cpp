#include "../include/Server.hpp"
#include "../include/utils.hpp"

Server::Server(MatchingEngine& engine, int port)
        : m_engine      (engine)
        , m_running     (true)
        , m_worker      (&Server::dispatch_results, this)
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
        m_running = false;
        m_worker.join();
        closesocket(m_socketfd);
        WSACleanup();
}

void Server::dispatch_results() {
        while(m_running) {
                MatchResult result;
                m_engine.pop_result(result);
                SOCKET bid_socket = m_registry.lookup(result.bid_order_id);
                SOCKET ask_socket = m_registry.lookup(result.ask_order_id);
                send_all(bid_socket, reinterpret_cast<char*>(&result), sizeof(result));
                send_all(ask_socket, reinterpret_cast<char*>(&result), sizeof(result));
                m_registry.unbind(result.bid_order_id);
                m_registry.unbind(result.ask_order_id);
        }
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

// constructor failure is silent
// run() has to exit condition
// naming confusion for the return values of bind() and listen()
// detached threads outlive the server if its destroyed while client threads are still running
