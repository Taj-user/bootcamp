#include <iostream>
#include <format>
#include <utility>
#include <vector>

std::pair<int, int> two_pointer(std::vector<int>& vec, int target) {
        std::pair<int, int> indexes;
        size_t size = vec.size();
        size_t begin = 0;
        size_t end = size - 1;
        while(begin < end) {
                if(vec[begin] + vec[end] == target) {
                        indexes = std::make_pair(begin, end);
                        break;
                }
                else if(vec[begin] + vec[end] < target) begin++;
                else end--;
        }
        return indexes;
}

int main(void) {
        std::vector<int> arr = { 1, 2, 4, 6, 8, 9 };
        auto pair = two_pointer(arr, 14);
        std::string answer = std::format("{{{}, {}}}", pair.first, pair.second);
        std::cout << answer;
}
