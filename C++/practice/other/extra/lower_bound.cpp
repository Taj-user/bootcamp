#include <cstddef>
#include <iostream>
#include <vector>

size_t lower_bound(std::vector<int>& vec, int target) {
        if(vec.empty()) return vec.size();
        size_t left = 0;
        size_t right = vec.size() - 1;
        while(left != right) {
                size_t mid = left + (right - left) / 2;
                if(vec[mid] < target) left = mid + 1;
                else right = mid;
        }
        if(vec[left] < target) return vec.size();
        return left;
}

int main(void) {
        std::vector<int> arr = { 1, 3, 3, 5, 7, 9 };
        size_t result = lower_bound(arr, 1);
        std::cout << result;

        return 0;
}
