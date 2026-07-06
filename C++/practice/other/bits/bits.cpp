#include <iostream>
#include "ring_buffer.hpp"

int main(void) {
        RingBuffer<int, 4> buffer;
        int val;
        std::cout << buffer.push(1) << "\n";
        std::cout << buffer.push(2) << "\n";
        std::cout << buffer.push(3) << "\n";
        std::cout << buffer.push(4) << "\n";
        std::cout << buffer.push(5) << "\n";

        std::cout << buffer.pop(val) << "\n";
        std::cout << val << "\n";
        std::cout << buffer.pop(val) << "\n";
        std::cout << val << "\n";
        std::cout << buffer.pop(val) << "\n";
        std::cout << val << "\n";
        std::cout << buffer.pop(val) << "\n";
        std::cout << val << "\n";
        std::cout << buffer.pop(val) << "\n";
}
