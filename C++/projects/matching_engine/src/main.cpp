#include "../include/MatchingEngine.hpp"
#include "../include/OrderBook.hpp"
#include "../include/Server.hpp"
#include <chrono>

int main(void) {
        OrderBook book;
        MatchingEngine engine(book);
        Server server(engine, 8080);
        server.run();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        return 0;
}
