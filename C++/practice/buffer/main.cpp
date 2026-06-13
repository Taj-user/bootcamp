#include <iostream>
#include <utility>
#include "buffer.h"

int main(void) {
    Buffer b1(8);
    Buffer b2(b1);
    Buffer b3(4);

    std::cout << "Buffer 1 size: " << b1.getSize() << "\n";
    std::cout << "Buffer 2 size: " << b2.getSize() << "\n";
    std::cout << "Buffer 3 size: " << b3.getSize() << "\n";

    Buffer b4 = std::move(b3);
    std::cout << "Buffer 3 size: " << b3.getSize() << "\n";
    std::cout << "Buffer 4 size: " << b4.getSize() << "\n";

    Buffer b5(10);
    std::cout << "Buffer 5 size before: " << b5.getSize() << "\n";
    std::cout << "Buffer 1 size before: " << b1.getSize() << "\n";
    b5 = std::move(b1);  // move assignment
    std::cout << "Buffer 5 size after: " << b5.getSize() << "\n";
    std::cout << "Buffer 1 size after: " << b1.getSize() << "\n";

    return 0;
}
