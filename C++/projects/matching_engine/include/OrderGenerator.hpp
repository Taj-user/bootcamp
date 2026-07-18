#pragma once
#include "Order.hpp"
#include "OrderGeneratorConfig.hpp"
#include <random>

class OrderGenerator {
        public:
                explicit OrderGenerator(const OrderGeneratorConfig& config);
                void run();

        private:
                Order generate_order();
                OrderGeneratorConfig m_config;
                std::mt19937 m_rng;
};
