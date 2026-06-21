#include <iostream>
#include <concepts>
#include <type_traits>

template<typename T>
concept Pointer = std::is_pointer_v<T>;

template<typename T>
requires Pointer<T>
void describe(T value) {
    std::cout << "pointer to: " << *value << "\n";
}

template<typename T>
requires (!Pointer<T>)
void describe(T value) {
    std::cout << "value: " << value << "\n";
}

int main(void) {
    int n = 42;
    int* p = &n;
    describe(p);
    describe(n);
    return 0;
}
