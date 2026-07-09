#include "../include/MatchingEngine.hpp"

MatchingEngine::MatchingEngine(OrderBook& book)
        : m_book        (book)
        , m_running     (true)
        , m_worker      (&MatchingEngine::process_orders, this)
{}

MatchingEngine::~MatchingEngine() {
        m_running = false;
        m_worker.join();
}

void MatchingEngine::process_orders() {
        while(m_running) {
                Order order;
                if(m_ring_buffer.pop(order)) {
                        m_book.add_order(order);
                        m_book.match_orders();
                }
        }
}

void MatchingEngine::submit_order(const Order& order) {
        m_ring_buffer.push(order);
}
