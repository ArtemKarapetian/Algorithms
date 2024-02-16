#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

const std::string ELEMENTS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int P = 31;

int hashser(std::string s) {
    long long hash = 0, p_pow = 1;
    for (size_t i=0; i < s.length(); ++i) {
        hash += (s[i] - 'a' + 1) * p_pow;
        p_pow *= P;
    }
    return hash;
}

void fillVectorWithSameHash(std::string s, size_t ind, std::unordered_set<std::string>& set, int number) {
    if (s.empty()) {
        return;
    }
    for (size_t i = ind; i < s.length() - 1; i++) {
        if (set.size() == number) {
            return;
        }
        for (int j = -2; j <= 2; j++) {
            if (set.size() == number) {
                return;
            }
            if (ELEMENTS.find(s[i] + j * 31) != std::string::npos && ELEMENTS.find(s[i + 1] - j ) != std::string::npos) {
                std::string sameHashedStr = s.substr(0, i) + (char)(s[i] + j * 31) + (char)(s[i + 1] - j) + s.substr(i + 2);
                if (j != 0) {
                    set.insert(sameHashedStr);
                }
                fillVectorWithSameHash(sameHashedStr, i + 1, set, number);
            }
        }
    }
}

std::vector<std::string> sameHashedStrings(std::string s, int number) {
    std::unordered_set<std::string> result_set;
    fillVectorWithSameHash(s, 0, result_set, number);
    std::string sameHashLarger = s; 
    for (int i = 0; result_set.size() != number; i++) {
        sameHashLarger += "Aa";
        result_set.insert(sameHashLarger);
        fillVectorWithSameHash(sameHashLarger, 0, result_set, number);
    }
    return std::vector<std::string>(result_set.begin(), result_set.end());
}


int main() {
    std::cout << "Write the word you want to get the same hash strings for:" << std::endl;
    std::string line;
    std::cin >> line;
    std::cout << "Write the number of same hash strings you want to get:" << std::endl;
    int number_of_same_hashed_strings;
    std::cin >> number_of_same_hashed_strings;
    std::vector<std::string> result;
    result = sameHashedStrings(line, number_of_same_hashed_strings);
    std::sort(result.begin(), result.end());
    for (size_t i = 0; i < number_of_same_hashed_strings; i++) {
        std::cout << i + 1 << " " << result[i] << std::endl;
    }
}
