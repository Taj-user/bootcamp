#include "../include/MatchingEngine.hpp"
#include "../include/OrderBook.hpp"

int main(void) {
        OrderBook book;
        MatchingEngine engine(book);
        // bid
        Order o1;
        o1.order_id = 0;
        o1.side |= OrderFlags::BUY;
        o1.price = 50.00;
        o1.quantity = 100;

        // ask
        Order o2;
        o2.order_id = 1;
        o2.side = 0;
        o2.price = 49.00;
        o2.quantity = 30;

        engine.submit_order(o1);
        engine.submit_order(o2);

        engine.process_orders();
        engine.process_orders();

        return 0;
}
