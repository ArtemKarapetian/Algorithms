#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include "array_helper.cpp"
#include "quick_heap_sort.cpp"

int main() {

    std::vector<int> random_vector = create_random(2000000);

    quick_heap_sort(random_vector, 150);

    // print_array(random_vector);
    // std::cout << check_for_sorted(random_vector);

    // std::cout << "Random vector change:" << std::endl;
    // test_speed(random_vector);

    // std::vector<int> reversed_vector = make_reversed_array(200000);

    // std::cout << std::endl << std::endl << "Reversed vector change:" << std::endl;
    // test_speed(reversed_vector);


    // std::vector<int> almost_sorted_vector = make_almost_sorted_array(200000);

    // std::cout << std::endl << std::endl << "Almost sorted vector change:" << std::endl;
    // test_speed(almost_sorted_vector);


    return 0;
}
