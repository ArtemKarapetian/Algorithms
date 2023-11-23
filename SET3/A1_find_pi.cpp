#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <climits>
#include <format>
#include <chrono>
#include <cmath>
#include <unistd.h>

double randomDouble() {
    return rand() / static_cast<double>(RAND_MAX) * 2.0 - 1;
}

void check(long long N, long long print_point) {
    std::ofstream raw_data("A1_raw_data.txt", std::ofstream::app);
    raw_data << std::endl;

    std::ofstream pi_precision("A1_pi_precision.txt", std::ofstream::app);
    pi_precision << std::setprecision(15) << std::endl;

    std::ofstream pi_precision_percent("A1_pi_precision_percent.txt", std::ofstream::app);
    pi_precision_percent << std::setprecision(15) << std::endl;

    std::cout.precision(15);

    double last_pi = 0.0;
    double current_pi = 0.0;

    long long M = 0;
    for (long long i = 1; i <= N; ++i) {
        double current_x = randomDouble();
        double current_y = randomDouble();
        if (current_x * current_x + current_y * current_y <= 1.0) {
            ++M;
        }
        if (i % print_point == 0 || i == N) {
            last_pi = current_pi;
            current_pi = 4.0 * static_cast<double>(M) / i;
            std::cout << i << " points: " << current_pi << std::endl;
            raw_data << "(" << i << "," << M << ") ";
            pi_precision << "(" << i << "," << current_pi << ") ";
            pi_precision_percent << "(" << i << "," << (current_pi - M_PI) * 100.0 / M_PI << ") ";
        }
    }
}

int main() {
    check(5000, 100);
    check(5000, 100);
    check(static_cast<long long>(INT_MAX), 50000000);
    
    return 0;
}

