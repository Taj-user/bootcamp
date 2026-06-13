#include <iostream>
#include <variant>

int main(void) {
    std::variant<int, double, std::string> v;

    v = 42;
    std::cout << std::get<int>(v) << "\n";

    v = 3.14;
    std::cout << std::get<double>(v) << "\n";

    v = std::string("hello");
    std::cout << std::get<std::string>(v) << "\n";

    // Show what happens with wrong type access
    try {
        std::get<int>(v);  // v holds string, not int
    }
    catch(const std::bad_variant_access& e) {
        std::cerr << e.what() << "\n";
    }
}
