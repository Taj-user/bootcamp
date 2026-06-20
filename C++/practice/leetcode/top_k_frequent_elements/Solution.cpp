#include <algorithm>
#include <vector>
#include <unordered_map>

class Solution {
    public:
        std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
            std::unordered_map<int, int> freq;
            for(int num : nums) freq[num]++;

            std::vector<std::pair<int, int>> count;
            for(const auto& [num, freq] : freq) count.push_back({num, freq});

            std::sort(count.begin(), count.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

            std::vector<int> result;
            for(int i = 0; i < k; i++) { result.push_back(count[i].first); }
            return result;
        }
};
