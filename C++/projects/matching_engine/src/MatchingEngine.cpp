#include "../include/MatchingEngine.hpp"

MatchingEngine::MatchingEngine(OrderBook& book)
        : m_book (book)
{}

void MatchingEngine::process_orders() {
        Order order;
        if(m_ring_buffer.pop(order)) {
                m_book.add_order(order);
                m_book.match_orders();
        }
}

void MatchingEngine::submit_order(const Order& order) {
        m_ring_buffer.push(order);
}
