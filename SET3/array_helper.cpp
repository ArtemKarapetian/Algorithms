#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>


std::vector<int> create_random(std::size_t size) {
    std::vector<int> array(size);
    for (std::size_t i = 0; i < size; ++i) {
        array[i] = std::rand() % 3001;
    }
    return array;
}

void print_array(const std::vector<int>& vector) {
    for (const int& element : vector) {
        std::cout << element << std::endl;
    }
    std::cout << std::endl;
}

bool check_for_sorted(const std::vector<int>& array) {
    for (std::size_t i = 1; i < array.size(); ++i) {
        if (array[i] < array[i - 1]) {
            return false;
        }
    }
    return true;
}

std::vector<int> make_almost_sorted_array(std::size_t size) {
    std::vector<int> array(size);
    std::iota(array.begin(), array.end(), 0);
    int amount = size > 5000 ? std::rand() % 500 : std::rand() % (size / 10);
    for (int i = 0; i < amount; ++i) {
        std::swap(array[std::rand() % size], array[std::rand() % size]);
    }
    if (!check_for_sorted(array)) {
        return make_almost_sorted_array(size);
    }
    return array;
}

std::vector<int> make_reversed_array(std::size_t size) {
    std::vector<int> array(size);
    std::iota(array.rbegin(), array.rend(), 0);
    return array;
}