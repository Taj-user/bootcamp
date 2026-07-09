#pragma once
#include "OrderBook.hpp"
#include "RingBuffer.hpp"
#include <thread>

class MatchingEngine {
        public:
                MatchingEngine(OrderBook& book);
                ~MatchingEngine();
                void process_orders();
                void submit_order(const Order& order);

        private:
                OrderBook&              m_book;
                RingBuffer<Order, 64>   m_ring_buffer;
                std::atomic<bool>       m_running;
                std::thread             m_worker;
};
