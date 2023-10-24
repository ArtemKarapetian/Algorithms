#include <iostream>
#include <vector>

int merge_with_counting_permutations(std::vector<int>& numbers, std::vector<int>& numbers_left, std::vector<int>& numbers_right) {
    int answer = 0;
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < numbers_left.size() && j < numbers_right.size()) {

        if (numbers_left[i] < numbers_right[j]) {
            numbers[i + j] = numbers_left[i];
            ++i;
        } else {
            answer += numbers_left.size() - i;
            numbers[i + j] = numbers_right[j];
            ++j;
        }
    }
    while (i < numbers_left.size()) {
        numbers[i + j] = numbers_left[i];
        ++i;
    }
    while (j < numbers_right.size()) {
        numbers[i + j] = numbers_right[j];
        ++j;
    }
    return answer;
}


int count_permutations_while_sort(std::vector<int>& numbers) {
    int answer = 0;
    if (numbers.size() > 1) {
        std::size_t mid = numbers.size() / 2;
        std::vector<int> numbers_left(numbers.begin(), numbers.begin() + mid);
        std::vector<int> numbers_right(numbers.begin() + mid, numbers.end());
        answer += count_permutations_while_sort(numbers_left);
        answer += count_permutations_while_sort(numbers_right);
        answer += merge_with_counting_permutations(numbers, numbers_left, numbers_right);
    }
    return answer;
}

int main() {
    std::vector<int> numbers{1, 3, 4, 2, 5};
    std::cout << count_permutations_while_sort(numbers) << std::endl;
    numbers = {5, 3, 2, 4, 1};
    std::cout << count_permutations_while_sort(numbers) << std::endl;
    return 0;
}
