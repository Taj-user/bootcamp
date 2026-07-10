#include "../include/MatchingEngine.hpp"

bool send_all(SOCKET fd, const char* buffer, int length) {
        int total = 0;
        while(total < length) {
                int sent = send(fd, buffer + total, length - total , 0);
                if(sent == -1) return false;
                total += sent;
        }
        return true;
}

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
                std::vector<MatchResult> match_vec;
                if(m_ring_buffer.pop(order)) {
                        m_book.add_order(order);
                        match_vec = m_book.match_orders();
                        for(const auto& match : match_vec) {
                                send_all(match.bid_client, reinterpret_cast<const char*>(&match), sizeof(match));
                                send_all(match.ask_client, reinterpret_cast<const char*>(&match), sizeof(match));
                        }
                }
        }
}

void MatchingEngine::submit_order(const Order& order) {
        m_ring_buffer.push(order);
}
