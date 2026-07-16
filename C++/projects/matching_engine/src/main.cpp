#include "../include/MatchingEngine.hpp"
#include "../include/OrderBook.hpp"
#include "../include/Server.hpp"
#include <iostream>

int main(void) {
        OrderBook book;
        MatchingEngine engine(book);
        Server server(engine, 8080);

        std::cin.get();                 // block until Enter is pressed. Or define a signal handler

        return 0;
}
