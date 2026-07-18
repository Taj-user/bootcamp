#pragma once
#include "Order.hpp"
#include "OrderGeneratorConfig.hpp"
#include "TcpClient.hpp"
#include <random>

class OrderGenerator {
        public:
                explicit OrderGenerator(const OrderGeneratorConfig& config);
                void run();

        private:
                Order generate_order();
                u64 m_next_order_id {0};
                OrderGeneratorConfig m_config;
                TcpClient m_tcp;
                std::mt19937 m_rng;
};
