#include <algorithm>
#include <format>
#include <iostream>
#include <vector>

auto three_sum(std::vector<int>& vec) -> std::vector<std::vector<int>> {
        std::vector<std::vector<int>> solution;
        std::sort(vec.begin(), vec.end());
        for(size_t i = 0; i < vec.size(); i++) {
                if(i != 0 && vec[i] == vec[i - 1]) continue;
                size_t begin = i + 1;
                size_t end = vec.size() - 1;
                while(begin < end) {
                        if(vec[i] + vec[begin] + vec[end] == 0) {
                                solution.push_back({ vec[i], vec[begin], vec[end] });
                                begin++;
                                end--;
                                while(begin < end && vec[begin] == vec[begin - 1]) {
                                        begin++;
                                }
                                while(begin < end && vec[end] == vec[end + 1]) {
                                        end--;
                                }
                        }
                        else if(vec[i] + vec[begin] + vec[end] < 0) begin++;
                        else end--;
                }
        }
        return solution;
}

int main(void) {
        std::vector<int> arr = {-4, -1, -1, 0, 1, 2};
        auto result = three_sum(arr);
        for(auto vec : result) {
                std::string fmt = std::format("{{{}, {}, {}}}", vec[0], vec[1], vec[2]);
                std::cout << fmt << "\n";
        }
}
