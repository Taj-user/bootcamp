#include "../include/OrderBook.hpp"
#include <iostream>
#include <algorithm>

void OrderBook::add_order(const Order& order) {
        if((order.side & OrderFlags::BUY) != 0) {
                m_bids[order.price].push(order);
        }
        else {
                m_asks[order.price].push(order);
        }
}

void OrderBook::match_orders() {
        auto best_bid = m_bids.begin();
        auto best_ask = m_asks.begin();
        u32 match_qty {};

        while(!m_bids.empty() && !m_asks.empty() && best_bid->first >= best_ask->first) {
                match_qty = std::min(best_bid->second.front().quantity, best_ask->second.front().quantity);

                std::cout << match_qty << " shares at " << best_ask->first <<
                        " | BID order_id=" << best_bid->second.front().order_id << " | ASK order_id=" << best_ask->second.front().order_id << "\n";

                best_bid->second.front().quantity -= match_qty;
                best_ask->second.front().quantity -= match_qty;

                if(best_bid->second.front().quantity == 0) best_bid->second.pop();
                if(best_ask->second.front().quantity == 0) best_ask->second.pop();

                if(best_bid->second.empty()) best_bid = m_bids.erase(best_bid);
                if(best_ask->second.empty()) best_ask = m_asks.erase(best_ask);
        }
}
