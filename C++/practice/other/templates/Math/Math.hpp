#pragma once
#include <vector>
#include <type_traits>

template<typename T>
concept Arithmetic = std::is_integral_v<T> || std::is_floating_point_v<T>;

namespace Math {
    // Sum of all parameter
    template<typename T, typename... Ts>
    requires Arithmetic<T>
    T sum(T t, Ts... ts) {
        return t + sum(ts...);
    }

    // Sum each element in a vector
    template<typename T>
    requires Arithmetic<T>
    T sum(const std::vector<T>& vec) {
        T sum = T{};
        for(const T& num : vec) {
            sum += num;
        }
        return sum;
    }

    // Raises a number to some power. floating point power not supported
    template<typename T>
    requires Arithmetic<T>
    T exp(T num, int pow) {
        if(pow == 0) return 1;
        if(pow > 0) {
            return num * exp(num, pow-1);
        }
        if(pow < 0) {
            return 1 / (num * exp(num, pow-1));
        }
        return -1;
    }

    // Dot product on two equivalent size vectors
    template<typename T>
    requires Arithmetic<T>
    T dot(const std::vector<T>& vec1, const std::vector<T>& vec2) {
        T dot = T{};
        for(size_t i = 0; i < vec1.size(); i++) {
            dot += vec1.at(i) * vec2.at(i);
        }
        return dot;
    }

    // Square root template for a number
    template<typename T>
    T sqrt(T num) {
        if(num < 0) return T{};
        T result = num;
        for(int i = 0; i < 20; i++) {
            result = (result + num / result) / 2;
        }
        return result;
    }
}
