#include <iostream>
#include <iomanip>
#include <vector>
#include "Vector.h"

// Count reallocations: a realloc happens the moment capacity == size
// just before push_back grows the buffer (i.e. when we'd exceed capacity).
template <typename Vec>
struct FillResult { int reallocations; };

template <typename Vec>
FillResult<Vec> count_reallocs(unsigned int sz) {
    Vec v;
    int reallocs = 0;
    for (unsigned int i = 1; i <= sz; ++i) {
        if (v.size() == v.capacity())
            ++reallocs;
        v.push_back(static_cast<int>(i));
    }
    return {reallocs};
}

int main() {
    const unsigned int sz = 100000000;

    auto r_std = count_reallocs<std::vector<int>>(sz);
    auto r_my  = count_reallocs<Vector<int>>(sz);

    std::cout << "Filling " << sz << " elements via push_back\n\n";
    std::cout << std::setw(20) << "Container"
              << std::setw(18) << "Reallocations\n";
    std::cout << std::string(38, '-') << "\n";
    std::cout << std::setw(20) << "std::vector"
              << std::setw(18) << r_std.reallocations << "\n";
    std::cout << std::setw(20) << "Vector"
              << std::setw(18) << r_my.reallocations  << "\n";

    std::cout << "\nExpected: ceil(log2(" << sz << ")) + 1 = "
              << [&]{
                     int n = 0;
                     unsigned long long cap = 1;
                     while (cap < sz) { cap *= 2; ++n; }
                     return n + 1;
                 }()
              << " (doubling strategy)\n";
}
