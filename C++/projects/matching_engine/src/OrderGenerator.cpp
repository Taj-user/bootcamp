#include "../include/OrderGenerator.hpp"

OrderGenerator::OrderGenerator(const OrderGeneratorConfig& config)
        : m_config      (config)
        , m_rng         (m_config.seed)
{}

Order OrderGenerator::generate_order() {
        std::uniform_int_distribution<int> price_distrib(m_config.min_price, m_config.max_price);
        Price random_price = price_distrib(m_rng);

        std::uniform_int_distribution<int> quantity_distrib(m_config.min_quantity, m_config.max_quantity);
        u32 random_quantity = quantity_distrib(m_rng);

        std::bernoulli_distribution distrib(m_config.buy_probability);
        bool random_side = distrib(m_rng);

        Order order;
        order.price = random_price;
        order.quantity = random_quantity;
        if(random_side) order.side |= OrderFlags::BUY;
        else order.side = 0;

        return order;
}

void OrderGenerator::run() {

}
