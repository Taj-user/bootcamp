#include <cstdint>
#include <iostream>

namespace OrderFlags {
        constexpr uint8_t BUY           = 1 << 0;
        constexpr uint8_t LIMIT         = 1 << 1;
        constexpr uint8_t IOC           = 1 << 2;
        // constexpr uint8_t FOK           = 1 << 3;
        // constexpr uint8_t HIDDEN        = 1 << 4;
}

int main(void) {
        uint8_t flags = 0;
        flags |= OrderFlags::BUY | OrderFlags::LIMIT;
        std::cout << ((flags & OrderFlags::IOC) != 0) << "\n";
        flags |= OrderFlags::IOC;
        std::cout << ((flags & OrderFlags::IOC) != 0) << "\n";
        flags &= ~OrderFlags::IOC;
        std::cout << ((flags & OrderFlags::IOC) != 0) << "\n";
        return 0;
}
