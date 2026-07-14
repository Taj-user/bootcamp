#include <algorithm>
#include <iostream>
#include <vector>
// variable sliding window

int subarray_len(std::vector<int>& vec, int target) {
        if(vec.empty()) return 0;
        size_t window_len {};
        size_t min_window_len = vec.size();
        auto left = vec.begin();
        auto right = vec.begin();
        int sum = {};
        while(right != vec.end()) {
                while(sum >= target) {
                        min_window_len = std::min(window_len, min_window_len);
                        sum -= *left;
                        left++;
                        window_len--;
                }
                sum += *right;
                right++;
                window_len++;
        }
        return (min_window_len == vec.size()) ? 0 : min_window_len;
}

int main(void) {
        std::vector<int> vec = { 2, 1, 5, 1, 3, 2 };
        std::cout << subarray_len(vec, 7);
}
