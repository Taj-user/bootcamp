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

// Summary of known issues
/*
        Critical (data race):
                → RingBuffer push/pop not thread safe

        High (reliability):
                → Server constructor fails silently
                → Detached threads outlive Server

        Medium (performance):
                → Busy-wait loop in MatchingEngine
                → double as map key for prices

        Low (design):
                → SOCKET in domain objects
                → std::cout in OrderBook
                → process_orders() is public
                → Missing includes in headers
*/
