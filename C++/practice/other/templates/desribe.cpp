#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_pointer_v<T>, void> describe(T value) {
    std::cout << "pointer to: " << *value << "\n";
}

template<typename T>
std::enable_if_t<!std::is_pointer_v<T>, void> describe(T value) {
    std::cout << "value: " << value << "\n";
}

int main(void) {
    int n = 42;
    int* p = &n;
    describe<int*>(p);
    describe<int>(n);
    return 0;
}
