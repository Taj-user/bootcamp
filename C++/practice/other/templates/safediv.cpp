#include <iostream>
#include <concepts>
#include <type_traits>

// concepts
template<typename T>
concept Divisible = requires(T a, T b) {
    a / b;
};

template<typename T>
T safeDivide2(T num1, T num2) {
    std::cerr << "Division not supported for this type\n";
    return T{};
}

template<typename T>
requires Divisible<T>
T safeDivide2(T num1, T num2) {
    return num1 / num2;
}

// sfinae
template<typename T>
T safeDivide(T num1, T num2) {
    if constexpr(std::is_floating_point_v<T>) {
        return num1 / num2;
    }
    else if constexpr(std::is_integral_v<T>) {
        if( num2 == 0) {
            std::cerr << "divide by zero error\n";
            return 0;
        }
        return num1 / num2;
    }
    else {
        static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>, "safeDivide only supports integral or floating-point types");
    }
}

int main(void) {
    std::cout << safeDivide(4, 2);          // is the same thing as
    std::cout << safeDivide<int>(4, 2);
    return 0;
}
