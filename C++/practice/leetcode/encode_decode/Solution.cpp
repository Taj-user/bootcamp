#include <iostream>
#include <string>
#include <vector>

// Runtime Error on test case: strs = { "", "" }

class Solution {
    public:
        std::string encode(std::vector<std::string>& strs) {
            std::string encoded_string;
            for(const std::string& str : strs) {
                encoded_string += std::to_string(str.size());
                encoded_string += "|";
                encoded_string += str;
            }
            return encoded_string;
        }

        std::vector<std::string> decode(std::string s) {
            std::vector<std::string> decoded_string;
            int i = 0;
            while(i < s.size()) {
                int j = i;
                while(s[j] != '|') {
                    j++;
                }
                int len = std::stoi(s.substr(i, j - i));
                std::string word = s.substr(j + 1, len);
                decoded_string.push_back(word);
                i = j + 1 + len;
            }
            return decoded_string;
        }
};

int main(void) {
    Solution soln;
    std::vector<std::string> strings = { "", "" };
    std::string encoded = soln.encode(strings);
    std::cout << "Encoded string: " << encoded << "\n";
    std::vector<std::string> decoded = soln.decode(encoded);
    std::cout << "{ ";
    for(const std::string& str : decoded) {
        std::cout << str << " ";
    }
    std::cout << "}";
    return 0;
}
