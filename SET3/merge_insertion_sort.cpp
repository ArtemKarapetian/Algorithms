#include <fstream>
#include <iostream>
#include <vector>

void merge_combined(std::vector<int>& array, std::vector<int>& array_left, std::vector<int>& array_right) {
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < array_left.size() && j < array_right.size()) {
        if (array_left[i] < array_right[j]) {
            array[i + j] = array_left[i];
            ++i;
        } else {
            array[i + j] = array_right[j];
            ++j;
        }
    }
    while (i < array_left.size()) {
        array[i + j] = array_left[i];
        ++i;
    }
    while (j < array_right.size()) {
        array[i + j] = array_right[j];
        ++j;
    }
}

void insertion_sort(std::vector<int>& array) {
    for (std::size_t i = 1; i < array.size(); ++i) {
        int pivot = array[i];
        std::size_t j = i - 1;

        while (j < array.size() && array[j] > pivot) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = pivot;
    }
}


void combined_sort(std::vector<int>& array, const int& change) {
    if (array.size() <= 1) {
        return;
    }
    if (array.size() < change) {
        insertion_sort(array);
        return;
    }
    std::size_t mid = array.size() / 2;
    std::vector<int> array_left(array.begin(), array.begin() + mid);
    std::vector<int> array_right(array.begin() + mid, array.end());
    combined_sort(array_left, change);
    combined_sort(array_right, change);
    merge_combined(array, array_left, array_right);
}

void print_time_combined(std::vector<int>& vector, std::string print, const int& change) {
    auto start = std::chrono::high_resolution_clock::now();
    combined_sort(vector, change);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    std::cout << print << millisec << ", ";
}

void test_speed(const std::vector<int>& array) {
    std::ofstream latex_raw_data("A2_raw_data.txt", std::ofstream::app);
    latex_raw_data << std::endl;

    std::ofstream latex_coordinates_change("A2_coordinates_change.txt", std::ofstream::app);
    latex_coordinates_change << std::endl;

    std::ofstream latex_coordinates_percent_change("A2_coordinates_percent_change.txt", std::ofstream::app);
    latex_coordinates_percent_change << std::setprecision(15) << std::endl;

    std::vector<long long> raw_data(62);

    for (int current = 0; current <= 300; current += 5) {

        for (int i = 0; i < 3; ++i) {
            std::vector<int> current_array(array.begin(), array.end());
            auto start = std::chrono::high_resolution_clock::now();
            combined_sort(current_array, current);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long current_millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            raw_data[current / 5 + 1] += current_millisec;
        }

        raw_data[current / 5 + 1] /= 3;
        long long change = raw_data[current / 5 + 1] - raw_data[current / 5];
        double change_percent = static_cast<double>(change) / raw_data[current / 5] * 100;
        bool is_positive_change = change >= 0;

        std::cout << current << " " << raw_data[current / 5 + 1] 
        << (is_positive_change ? " +" : " ") << change 
        << (is_positive_change ? " +" : " ") << change_percent
        << "%" << std::endl;

        latex_raw_data << "(" << current << "," << raw_data[current / 5 + 1] << ") ";
        latex_coordinates_change << "(" << current << "," << change << ") ";
        latex_coordinates_percent_change << "(" << current << "," << change_percent << ") ";
    }
}