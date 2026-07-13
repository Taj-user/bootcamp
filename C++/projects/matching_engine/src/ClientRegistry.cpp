#include "../include/ClientRegistry.hpp"

void ClientRegistry::bind(u64 order_id, SOCKET client) {
        order_to_client[order_id] = client;
}

void ClientRegistry::unbind(u64 order_id) {
        order_to_client.erase(order_id);
}

SOCKET ClientRegistry::lookup(u64 order_id) const {
        return order_to_client.at(order_id);
}
