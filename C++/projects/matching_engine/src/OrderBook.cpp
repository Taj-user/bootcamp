#include "../include/OrderBook.hpp"
#include <algorithm>

void OrderBook::add_order(const Order& order) {
        if((order.side & OrderFlags::BUY) != 0) {
                m_bids[(order.price) * 100].push(order);
        }
        else {
                m_asks[(order.price) * 100].push(order);
        }
}

std::vector<MatchResult> OrderBook::match_orders() {
        auto best_bid = m_bids.begin();
        auto best_ask = m_asks.begin();
        u32 match_qty {};
        std::vector<MatchResult> match_results;

        while(!m_bids.empty() && !m_asks.empty() && best_bid->first >= best_ask->first) {
                match_qty = std::min(best_bid->second.front().quantity, best_ask->second.front().quantity);

                MatchResult result;
                result.bid_order_id     = best_bid->second.front().order_id;
                result.ask_order_id     = best_ask->second.front().order_id;
                result.price            = static_cast<double>(best_ask->first) / 100.0;
                result.match_qty        = match_qty;
                match_results.push_back(result);

                best_bid->second.front().quantity -= match_qty;
                best_ask->second.front().quantity -= match_qty;

                if(best_bid->second.front().quantity == 0) best_bid->second.pop();
                if(best_ask->second.front().quantity == 0) best_ask->second.pop();

                if(best_bid->second.empty()) best_bid = m_bids.erase(best_bid);
                if(best_ask->second.empty()) best_ask = m_asks.erase(best_ask);
        }
        return match_results;
}

// match_orders() shouldnt know about output. Caller should decide how to display it
// double as map key is dangerous
