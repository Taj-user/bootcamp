#pragma once
#include "Types.h"
#include <winsock2.h>
#include <ws2tcpip.h>

namespace OrderFlags {
        constexpr u8 BUY        = 1 << 0;
        constexpr u8 LIMIT      = 1 << 1;
        constexpr u8 IOC        = 1 << 2;
        constexpr u8 FOK        = 1 << 3;
        constexpr u8 HIDDEN     = 1 << 4;
}

struct Order {
        u64     order_id;
        double  price;
        SOCKET  client;
        u32     quantity;
        u8      side = OrderFlags::BUY;
};

struct MatchResult {
        u64     bid_order_id;
        u64     ask_order_id;
        double  price;
        SOCKET  bid_client;
        SOCKET  ask_client;
        u32     match_qty;
};
