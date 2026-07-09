#pragma once
#include "Order.hpp"
#include <map>
#include <queue>

class OrderBook {
        public:
                void add_order(const Order& order);
                void match_orders();

        private:
                std::map<double, std::queue<Order>, std::greater<double>>       m_bids;
                std::map<double, std::queue<Order>>                             m_asks;
};
