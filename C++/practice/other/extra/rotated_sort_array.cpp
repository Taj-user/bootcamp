#include <iostream>
#include <vector>

int search_rotated_sort_array(std::vector<int>& vec, int target) {
        if(vec.empty()) return -1;
        std::size_t left = 0;
        std::size_t right = vec.size() - 1;
        while(left < right) {
                std::size_t mid = left + (right - left) / 2;
                if(vec[mid] == target) return mid;
                if(vec[left] <= vec[mid]) {
                        if(target >= vec[left] && target < vec[mid]) right = mid;
                        else left = mid + 1;
                }
                else if(vec[left] > vec[mid]) {
                        if(target > vec[mid] && target <= vec[right]) left = mid + 1;
                        else right = mid;
                }
        }
        return -1;
}

int main(void) {
        std::vector<int> vec { 4, 5, 6, 7, 0, 1, 2 };
        std::cout << search_rotated_sort_array(vec, 0);
        return 0;
}
