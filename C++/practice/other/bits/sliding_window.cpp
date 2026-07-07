#include <iostream>
#include <vector>

int maxFixedWindowSum(const std::vector<int>& arr, size_t k) {
        int sum = 0;
        for(size_t i = 0; i < k; i++) {
                sum += arr[i];
        }

        int max_sum = sum;
        for(size_t i = k; i < arr.size(); i++) {
                sum += arr[i];
                sum -= arr[i - k];
                max_sum = std::max(max_sum, sum);
        }

        return max_sum;
}

int maxVariableWindowSum(const std::vector<int>& arr, int T) {
        int left = 0;
        int sum = 0;
        int max_sum = 0;

        for(size_t right = 0; right < arr.size(); right++) {
                sum += arr[right];
                while(sum > T) {
                        sum -= arr[left];
                        left++;
                }
                max_sum = std::max(max_sum, sum);
        }

        return max_sum;
}

int main(void) {
        std::vector<int> vec = {3, 2, 1, 5, 4, 2, 3, 1};
        std::cout << maxFixedWindowSum(vec, 3) << "\n";
        std::cout << maxVariableWindowSum(vec, 8) << "\n";
}
