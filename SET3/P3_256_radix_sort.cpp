#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

void divide_negative_positive(std::vector<int>& nums) {
    std::stack<int> negative_numbers;
    std::queue<int> positive_numbers;
    for (const int& num : nums) {
        if (num < 0) {
            negative_numbers.push(num);
        }
        else {
            positive_numbers.push(num);
        }
    }

    std::size_t ind = 0;
    while (!negative_numbers.empty()) {
        nums[ind] = negative_numbers.top();
        negative_numbers.pop();
        ++ind;
    }
    while (!positive_numbers.empty()) {
        nums[ind] = positive_numbers.front();
        positive_numbers.pop();
        ++ind; 
    }
}

void sort_by_category(std::vector<int>& nums, int category) {
    std::vector<std::queue<int>> numbers_by_category(256);

    for (const int& num : nums) {
        int index = std::abs(num);
        for (int i = 0; i < category; ++i) {
            index >>= 8;
        }
        index %= 256;
        numbers_by_category[index].push(num);
    }

    std::size_t ind = 0;
    for (std::queue<int>& current : numbers_by_category) {
        while (!current.empty()) {
            nums[ind] = current.front();
            current.pop();
            ++ind;
        }
    }
}

void radixSort(std::vector<int>& nums) {
    if (nums.size() <= 1) {
        return;
    }

    int max = nums[0];
    bool is_negative = false;
    for (const int& num : nums) {
        if (num < 0) {
            is_negative = true;
        }
        if (max < std::abs(num)) {
            max = std::abs(num);
        }
    }

    for (int i = 0; i < 4; ++i) {
        sort_by_category(nums, i);
    }

    if (is_negative) {
        divide_negative_positive(nums);
    }
}

int main() {
    
    std::size_t n;
    std::ifstream input("input.txt");
    input >> n;

    std::vector<int> nums(n);
    while (n--) {
        input >> nums[n];
    }

    radixSort(nums);

    for (const int& num : nums) {
        std::cout << num << " ";
    }
    
    return 0;
}

