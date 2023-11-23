#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

void heapify(std::vector<int>& nums, std::size_t current, std::size_t size) {
    if (current * 2 + 1 >= size) {
        return;
    }
    if (current * 2 + 2 >= size) {
        std::size_t child = current * 2 + 1;
        if (nums[child] > nums[current]) {
            std::swap(nums[child], nums[current]);
        }
        return;
    }

    std::size_t left_child = current * 2 + 1;
    std::size_t right_child = current * 2 + 2;
    std::size_t actual_parent = current;

    if (nums[left_child] > nums[actual_parent]) {
        actual_parent = left_child;
    } 
    if (nums[right_child] > nums[actual_parent]) {
        actual_parent = right_child;
    }

    if (actual_parent != current) {
        std::swap(nums[actual_parent], nums[current]);
        heapify(nums, actual_parent, size);
    }
}

void buildHeap(std::vector<int>& nums) {
    std::size_t i = nums.size() / 2;
    while (i) {
        i--;
        heapify(nums, i, nums.size());
    }
}

void heapSort(std::vector<int>& nums) {
    if (nums.size() <= 1) {
        return;
    }

    buildHeap(nums);

    for (std::size_t i = nums.size() - 1; i > 0; --i) {
        std::swap(nums[0], nums[i]);
        heapify(nums, 0, i);
    }
}

int main() {
    
    std::size_t n;
    std::cin >> n;

    std::vector<int> nums(n);
    while (n--) {
        std::cin >> nums[n];
    }

    heapSort(nums);

    for (const int& num : nums) {
        std::cout << num << " ";
    }
    
    return 0;
}

