#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

class Solution {
    public:
        std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
            std::unordered_map<std::string, std::vector<std::string>> groups;
            for(const std::string& str : strs) {
                std::string original = str;
                std::sort(original.begin(), original.end());
                groups[original].push_back(str);
            }
            std::vector<std::vector<std::string>> result;
            for(const auto& group : groups) {
                result.push_back(group.second);
            }
            return result;
        }
};