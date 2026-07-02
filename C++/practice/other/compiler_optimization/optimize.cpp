#include <iostream>
#include <chrono>

int add(int a, int b) {
    return a * b + a - b;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    long long sum = 0;
    for (int i = 0; i < 100000000; ++i) {
        sum += add(i, i + 1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Sum: " << sum << "\n";
    std::cout << "Time: " << duration.count() << "ms\n";
}
