#include <vector>
#include <iostream>
#include <fstream>

void countingSort(std::vector<int>& nums) {
    if (nums.size() <= 1) {
        return;
    }

    int min = nums[0];
    int max = nums[0];

    for (const int& num : nums) {
        if (num > max) {
            max = num;
        }
        else if (num < min) {
            min = num;
        }
    }

    std::vector<int> counting_array(max - min + 1);

    for (const int& num : nums) {
        counting_array[num - min]++;
    }

    for (std::size_t i = 1; i < counting_array.size(); ++i) {
        counting_array[i] += counting_array[i - 1];
    }

    std::vector<int> sorted_array(nums.size());

    for (std::size_t i = nums.size() - 1; i < nums.size(); --i) {
        --counting_array[nums[i] - min];
        sorted_array[counting_array[nums[i] - min]] = nums[i];
    }

    nums = sorted_array;
}

int main() {
    
    std::size_t n;
    std::ifstream input("input.txt");
    input >> n;

    std::vector<int> nums(n);
    while (n--) {
        input >> nums[n];
    }

    countingSort(nums);

    for (const int& num : nums) {
        std::cout << num << " ";
    }
    
    return 0;
}

