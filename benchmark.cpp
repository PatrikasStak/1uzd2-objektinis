#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include "Vector.h"

using Clock = std::chrono::high_resolution_clock;
using Ms    = std::chrono::duration<double, std::milli>;

template <typename Vec>
double fill_ms(unsigned int sz) {
    auto t0 = Clock::now();
    Vec v;
    for (unsigned int i = 1; i <= sz; ++i)
        v.push_back(static_cast<int>(i));
    auto t1 = Clock::now();
    return std::chrono::duration_cast<Ms>(t1 - t0).count();
}

int main() {
    const unsigned int sizes[] = {
        10000, 100000, 1000000, 10000000, 100000000
    };

    std::cout << std::fixed << std::setprecision(3);
    std::cout << std::setw(12) << "n"
              << std::setw(18) << "std::vector (ms)"
              << std::setw(16) << "Vector (ms)"
              << std::setw(12) << "ratio\n";
    std::cout << std::string(58, '-') << "\n";

    for (unsigned int sz : sizes) {
        double t_std = fill_ms<std::vector<int>>(sz);
        double t_my  = fill_ms<Vector<int>>(sz);
        std::cout << std::setw(12) << sz
                  << std::setw(18) << t_std
                  << std::setw(16) << t_my
                  << std::setw(11) << (t_my / t_std) << "x\n";
    }
}
