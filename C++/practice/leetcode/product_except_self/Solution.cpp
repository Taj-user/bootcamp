#include <iostream>
#include <vector>

class Solution {
        public:
                std::vector<int> productExceptSelf(std::vector<int>& nums) {
                        std::vector<int> output(nums.size());

                        output[0] = 1;
                        for(int i = 1; i < static_cast<int>(nums.size()); i++) {
                                output[i] = output[i - 1] * nums[i - 1];
                        }

                        int suffix = 1;
                        for(int i = static_cast<int>(nums.size()) - 1; i >= 0; i--) {
                                output[i] *= suffix;
                                suffix *= nums[i];
                        }

                        return output;
                }
};

int main() {
        Solution s;
        std::vector<int> vec = { -1, 0, 1, 2, 3 };
        std::vector<int> result = s.productExceptSelf(vec);
        for(auto num : result) {
                std::cout << num << "\n";
        }
        return 0;
}
