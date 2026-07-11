#include "../include/Order.hpp"
#include "../include/utils.hpp"
#include <iostream>

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

        // Create orders
        Order o1;
        o1.order_id     = 0;
        o1.side         |= OrderFlags::BUY;     // bid
        o1.price        = 50.00;
        o1.quantity     = 100;

        Order o2;
        o2.order_id     = 1;
        o2.side         = 0;                    // ask
        o2.price        = 49.00;
        o2.quantity     = 30;

        send_all(sockfd, reinterpret_cast<char*>(&o1), sizeof(o1));
        send_all(sockfd, reinterpret_cast<char*>(&o2), sizeof(o2));

        MatchResult result;
        int recvfd {};
        while((recvfd = recv(sockfd, reinterpret_cast<char*>(&result), sizeof(result), 0)) > 0) {
                std::cout << "ORDER FILLED: " << result.match_qty << "shares at " << result.price
                        << " | bid_order_id=" << result.bid_order_id
                        << " | ask_order_id=" << result.ask_order_id << "\n";
        }

        closesocket(sockfd);

        WSACleanup();

        return 0;
}
