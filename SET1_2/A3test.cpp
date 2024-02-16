#include <iostream>
#include <map>
#include <string>
#include <vector>


const char ELEMENTS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int A = 'a' * 32;

int main() {
    std::map<int, std::vector<std::string>> map;
    for (char a : ELEMENTS) {
        for (char b : ELEMENTS) {
            map[a + b * 31 - A].push_back(std::string({a, b}));
        }
    }
    for (auto& [key, value] : map) {
        if (value.size() == 1) {
            continue;
        }
        for (const auto& s : value) {
            std::cout << s << " ";
        }
        std::cout << std::endl;   
    }
}

// цифры: -48 - -39
// заглавные: -31 - -6
// строчные : 1 - 27