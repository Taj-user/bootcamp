#include <iostream>

template<typename T>
class FunctionTraits {
    public:
        static constexpr bool isFunction = false;
};

template<typename Ret, typename... Args>
class FunctionTraits<Ret(Args...)> {
    public:
        static constexpr bool isFunction = true;
        static constexpr size_t argCount = sizeof...(Args);
        using returnType = Ret;
};

int main(void) {
    std::cout << FunctionTraits<int(double, float)>::isFunction << "\n";
    std::cout << FunctionTraits<int(double, float)>::argCount << "\n";
    std::cout << FunctionTraits<int>::isFunction << "\n";
    return 0;
}
