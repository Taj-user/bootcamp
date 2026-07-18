#include "Types.hpp"

struct OrderGeneratorConfig {
        u64             num_orders;
        Price           min_price;
        Price           max_price;
        double          buy_probability;
        u32             min_quantity;
        u32             max_quantity;
        unsigned int    seed;
     // std::chrono::microseconds delay -> time it should take for order to reach the server(could implement later)
};
