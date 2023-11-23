#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>

void heapify(std::vector<int>& nums, std::size_t current, std::size_t left, std::size_t right) {
    if (current * 2 - left + 1 > right) {
        return;
    }
    if (current * 2 - left + 2 > right) {
        std::size_t child = current * 2 - left + 1;
        if (nums[child] > nums[current]) {
            std::swap(nums[child], nums[current]);
        }
        return;
    }

    std::size_t left_child = current * 2 - left + 1;
    std::size_t right_child = current * 2 - left + 2;
    std::size_t actual_parent = current;

    if (nums[left_child] > nums[actual_parent]) {
        actual_parent = left_child;
    } 
    if (nums[right_child] > nums[actual_parent]) {
        actual_parent = right_child;
    }

    if (actual_parent != current) {
        std::swap(nums[actual_parent], nums[current]);
        heapify(nums, actual_parent, left, right);
    }
}

void build_heap(std::vector<int>& nums, std::size_t left, std::size_t right) {
    std::size_t i = left + (right - left) / 2;
    while (i > left) {
        i--;
        heapify(nums, i, left, right);
    }
}

void heap_sort(std::vector<int>& nums, std::size_t left, std::size_t right) {
    if (right - left <= 1) {
        return;
    }

    build_heap(nums, left, right);

    for (std::size_t i = right; i > left; --i) {
        std::swap(nums[left], nums[i]);
        heapify(nums, left, left, i - 1);
    }
}

std::size_t partition(std::vector<int>& nums, std::size_t left, std::size_t right) {
    int pivot = nums[right];
    std::size_t i = left;

    for (std::size_t j = left; j < right; ++j) {
        if (nums[j] <= pivot) {
            std::swap(nums[i], nums[j]);
            ++i;
        }
    }
    std::swap(nums[i], nums[right]);

    return i;
}

void quick_heap_sort(std::vector<int>& nums, int change) {
    std::stack<std::pair<std::size_t, std::size_t> > partitions;
    partitions.emplace(0, nums.size() - 1);

    while (!partitions.empty()) {
        std::pair<std::size_t, std::size_t> current = partitions.top();
        partitions.pop();

        if (current.second - current.first <= change) {
            heap_sort(nums, current.first, current.second);
            continue;
        }

        std::size_t pivot = partition(nums, current.first, current.second);

        if (pivot > current.first + 1) {
            partitions.emplace(current.first, pivot - 1);
        }

        if (pivot + 1 < current.second) {
            partitions.emplace(pivot + 1, current.second);
        }

    }
}

void test_speed(const std::vector<int>& array) {
    std::ofstream latex_raw_data("A3_raw_data.txt", std::ofstream::app);
    latex_raw_data << std::endl;

    std::ofstream latex_coordinates_change("A3_coordinates_change.txt", std::ofstream::app);
    latex_coordinates_change << std::endl;

    std::ofstream latex_coordinates_percent_change("A3_coordinates_percent_change.txt", std::ofstream::app);
    latex_coordinates_percent_change << std::setprecision(15) << std::endl;

    long long previous_millisec = 0;
    long long current_millisec = 0;

    for (int current = 0; current <= 300; current += 5) {

        std::vector<int> current_array(array.begin(), array.end());
        auto start = std::chrono::high_resolution_clock::now();
        quick_heap_sort(current_array, current);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        current_millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        
        long long change = current_millisec - previous_millisec;
        double change_percent = static_cast<double>(change) / previous_millisec * 100;
        bool is_positive_change = current_millisec > previous_millisec;

        std::cout << current << " " << current_millisec 
        << (is_positive_change ? " +" : " ") << change 
        << (is_positive_change ? " +" : " ") << change_percent
        << "%" << std::endl;

        latex_raw_data << "(" << current << "," << current_millisec << ") ";
        latex_coordinates_change << "(" << current << "," << change << ") ";
        latex_coordinates_percent_change << "(" << current << "," << change_percent << ") ";
        
        previous_millisec = current_millisec;
    }
}