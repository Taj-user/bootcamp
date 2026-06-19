#include <vector>
#include <unordered_map>

class Solution {
    public:
        std::vector<int> twoSum(std::vector<int>& nums, int target) {
                std::unordered_map<int, int> seen;
                for(int i = 0; i < nums.size(); i++) {
                    int needed = target - nums[i];
                    if(seen.find(needed) != seen.end()) {
                        return {seen[needed], i};
                    }
                    seen[nums[i]] = i;
                }
                return {};
        }
};