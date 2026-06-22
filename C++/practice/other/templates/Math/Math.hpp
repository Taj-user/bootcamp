#pragma once
#include <vector>
#include <concepts>
#include <type_traits>

template<typename T>
concept Arithmetic = std::is_integral_v<T> || std::is_floating_point_v<T>;

namespace Math {
    template<typename T>
    requires Arithmetic<T>
    T sum(const std::vector<T>& vec) {
        T sum = T{};
        for(T& num : vec) {
            sum += num;
        }
        return sum;
    }

    template<typename T>
    requires Arithmetic<T>
    T dot(const std::vector<T>& vec1, const std::vector<T>& vec2) {
        T dot = T{};
        for(size_t i = 0; i < vec1.size(); i++) {
            dot += vec1.at(i) * vec2.at(i);
        }
        return dot;
    }

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
}

