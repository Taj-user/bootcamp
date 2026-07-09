#pragma once
#include "OrderBook.hpp"
#include "RingBuffer.hpp"

class MatchingEngine {
        public:
                MatchingEngine(OrderBook& book);
                void process_orders();
                void submit_order(const Order& order);
                // std::thread worker;

        private:
                OrderBook& m_book;
                RingBuffer<Order, 64> m_ring_buffer;
};
