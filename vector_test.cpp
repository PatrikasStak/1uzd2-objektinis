#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Vector.h"

#include <string>
#include <vector>
#include <sstream>
#include <numeric>

// ─────────────────────────────────────────────────────────────────────────────
// Constructors & assignment
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("Default constructor creates empty vector", "[constructors]") {
    Vector<int> v;
    REQUIRE(v.size()     == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.empty());
    REQUIRE(v.data()     == nullptr);
}

TEST_CASE("Fill constructor (n)", "[constructors]") {
    Vector<int> v(5);
    REQUIRE(v.size()     == 5);
    REQUIRE(v.capacity() == 5);
    REQUIRE(!v.empty());
    for (std::size_t i = 0; i < v.size(); ++i)
        REQUIRE(v[i] == 0);
}

TEST_CASE("Fill constructor (n, val)", "[constructors]") {
    Vector<int> v(4, 7);
    REQUIRE(v.size() == 4);
    for (std::size_t i = 0; i < v.size(); ++i)
        REQUIRE(v[i] == 7);
}

TEST_CASE("Fill constructor with string", "[constructors]") {
    Vector<std::string> v(3, "hi");
    REQUIRE(v.size() == 3);
    for (const auto& s : v)
        REQUIRE(s == "hi");
}

TEST_CASE("Initialiser-list constructor", "[constructors]") {
    Vector<int> v = {1, 2, 3, 4, 5};
    REQUIRE(v.size() == 5);
    for (int i = 0; i < 5; ++i)
        REQUIRE(v[i] == i + 1);
}

TEST_CASE("Range constructor from std::vector", "[constructors]") {
    std::vector<int> src = {10, 20, 30};
    Vector<int> v(src.begin(), src.end());
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 20);
    REQUIRE(v[2] == 30);
}

TEST_CASE("Range constructor from array pointers", "[constructors]") {
    int arr[] = {5, 6, 7, 8};
    Vector<int> v(arr, arr + 4);
    REQUIRE(v.size() == 4);
    REQUIRE(v[3] == 8);
}

TEST_CASE("Copy constructor produces independent copy", "[constructors]") {
    Vector<int> a = {1, 2, 3};
    Vector<int> b(a);
    REQUIRE(b.size() == 3);
    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 2);
    REQUIRE(b[2] == 3);
    // Modifying b does not affect a
    b[0] = 99;
    REQUIRE(a[0] == 1);
}

TEST_CASE("Move constructor transfers ownership", "[constructors]") {
    Vector<int> a = {1, 2, 3};
    Vector<int> b(std::move(a));
    REQUIRE(b.size() == 3);
    REQUIRE(b[0] == 1);
    // a must be in valid empty state
    REQUIRE(a.size()     == 0);
    REQUIRE(a.capacity() == 0);
    REQUIRE(a.data()     == nullptr);
}

TEST_CASE("Copy assignment operator", "[assignment]") {
    Vector<int> a = {4, 5, 6};
    Vector<int> b;
    b = a;
    REQUIRE(b.size() == 3);
    REQUIRE(b[2] == 6);
    // Independence
    a[0] = 99;
    REQUIRE(b[0] == 4);
}

TEST_CASE("Copy self-assignment is safe", "[assignment]") {
    Vector<int> v = {1, 2, 3};
    v = v;
    REQUIRE(v.size() == 3);
    REQUIRE(v[1] == 2);
}

TEST_CASE("Move assignment operator", "[assignment]") {
    Vector<int> a = {7, 8, 9};
    Vector<int> b;
    b = std::move(a);
    REQUIRE(b.size() == 3);
    REQUIRE(b[0] == 7);
    REQUIRE(a.size() == 0);
}

TEST_CASE("Initialiser-list assignment", "[assignment]") {
    Vector<int> v;
    v = {10, 20, 30};
    REQUIRE(v.size() == 3);
    REQUIRE(v[1] == 20);
}

TEST_CASE("assign(n, val)", "[assignment]") {
    Vector<int> v = {1, 2, 3, 4};
    v.assign(2, 99);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 99);
    REQUIRE(v[1] == 99);
}

TEST_CASE("assign(first, last)", "[assignment]") {
    std::vector<int> src = {5, 6, 7};
    Vector<int> v = {1, 2, 3, 4};
    v.assign(src.begin(), src.end());
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 5);
    REQUIRE(v[2] == 7);
}

TEST_CASE("assign(initialiser_list)", "[assignment]") {
    Vector<int> v = {1, 2};
    v.assign({10, 20, 30, 40});
    REQUIRE(v.size() == 4);
    REQUIRE(v[3] == 40);
}

// ─────────────────────────────────────────────────────────────────────────────
// Element access
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("operator[] read and write", "[element_access]") {
    Vector<int> v = {10, 20, 30};
    REQUIRE(v[0] == 10);
    REQUIRE(v[2] == 30);
    v[1] = 99;
    REQUIRE(v[1] == 99);
}

TEST_CASE("operator[] on const vector", "[element_access]") {
    const Vector<int> v = {1, 2, 3};
    REQUIRE(v[0] == 1);
    REQUIRE(v[2] == 3);
}

TEST_CASE("at() returns correct element", "[element_access]") {
    Vector<int> v = {5, 6, 7};
    REQUIRE(v.at(0) == 5);
    REQUIRE(v.at(2) == 7);
    v.at(1) = 42;
    REQUIRE(v.at(1) == 42);
}

TEST_CASE("at() throws on out-of-range", "[element_access]") {
    Vector<int> v = {1, 2, 3};
    REQUIRE_THROWS_AS(v.at(3),  std::out_of_range);
    REQUIRE_THROWS_AS(v.at(99), std::out_of_range);
}

TEST_CASE("at() throws on empty vector", "[element_access]") {
    Vector<int> v;
    REQUIRE_THROWS_AS(v.at(0), std::out_of_range);
}

TEST_CASE("front() and back()", "[element_access]") {
    Vector<int> v = {10, 20, 30};
    REQUIRE(v.front() == 10);
    REQUIRE(v.back()  == 30);
    v.front() = 1;
    v.back()  = 3;
    REQUIRE(v[0] == 1);
    REQUIRE(v[2] == 3);
}

TEST_CASE("front() and back() on const vector", "[element_access]") {
    const Vector<int> v = {7, 8, 9};
    REQUIRE(v.front() == 7);
    REQUIRE(v.back()  == 9);
}

TEST_CASE("front() == back() on single-element vector", "[element_access]") {
    Vector<int> v = {42};
    REQUIRE(v.front() == v.back());
}

TEST_CASE("data() returns pointer to first element", "[element_access]") {
    Vector<int> v = {1, 2, 3};
    int* p = v.data();
    REQUIRE(p[0] == 1);
    REQUIRE(p[2] == 3);
    p[0] = 99;
    REQUIRE(v[0] == 99);
}

TEST_CASE("data() on const vector", "[element_access]") {
    const Vector<int> v = {4, 5, 6};
    const int* p = v.data();
    REQUIRE(p[1] == 5);
}

TEST_CASE("at() and operator[] agree", "[element_access]") {
    Vector<int> v = {3, 1, 4, 1, 5};
    for (std::size_t i = 0; i < v.size(); ++i)
        REQUIRE(v[i] == v.at(i));
}

// ─────────────────────────────────────────────────────────────────────────────
// Iterators
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("begin/end range-for loop", "[iterators]") {
    Vector<int> v = {1, 2, 3, 4, 5};
    int sum = 0;
    for (int x : v) sum += x;
    REQUIRE(sum == 15);
}

TEST_CASE("begin/end manual increment", "[iterators]") {
    Vector<int> v = {10, 20, 30};
    auto it = v.begin();
    REQUIRE(*it == 10);
    ++it;
    REQUIRE(*it == 20);
    it++;
    REQUIRE(*it == 30);
    ++it;
    REQUIRE(it == v.end());
}

TEST_CASE("iterator write through dereference", "[iterators]") {
    Vector<int> v = {1, 2, 3};
    for (auto it = v.begin(); it != v.end(); ++it)
        *it *= 2;
    REQUIRE(v[0] == 2);
    REQUIRE(v[1] == 4);
    REQUIRE(v[2] == 6);
}

TEST_CASE("cbegin/cend on non-const vector", "[iterators]") {
    Vector<int> v = {5, 6, 7};
    int sum = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it)
        sum += *it;
    REQUIRE(sum == 18);
}

TEST_CASE("begin/end on const vector yields const_iterator", "[iterators]") {
    const Vector<int> v = {1, 2, 3};
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it)
        sum += *it;
    REQUIRE(sum == 6);
}

TEST_CASE("iterator arithmetic: + and -", "[iterators]") {
    Vector<int> v = {10, 20, 30, 40, 50};
    auto it = v.begin();
    REQUIRE(*(it + 2) == 30);
    REQUIRE(*(it + 4) == 50);
    auto it2 = v.end();
    REQUIRE(*(it2 - 1) == 50);
    REQUIRE(*(it2 - 3) == 30);
}

TEST_CASE("iterator difference", "[iterators]") {
    Vector<int> v = {1, 2, 3, 4, 5};
    REQUIRE(v.end() - v.begin() == 5);
    REQUIRE(v.begin() - v.begin() == 0);
}

TEST_CASE("iterator operator[]", "[iterators]") {
    Vector<int> v = {10, 20, 30};
    auto it = v.begin();
    REQUIRE(it[0] == 10);
    REQUIRE(it[1] == 20);
    REQUIRE(it[2] == 30);
}

TEST_CASE("iterator comparisons", "[iterators]") {
    Vector<int> v = {1, 2, 3};
    REQUIRE(v.begin() <  v.end());
    REQUIRE(v.begin() <= v.begin());
    REQUIRE(v.end()   >  v.begin());
    REQUIRE(v.end()   >= v.end());
    REQUIRE(v.begin() != v.end());
    REQUIRE(v.begin() == v.begin());
}

TEST_CASE("rbegin/rend traverses in reverse", "[iterators]") {
    Vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> reversed;
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        reversed.push_back(*it);
    REQUIRE(reversed[0] == 5);
    REQUIRE(reversed[4] == 1);
}

TEST_CASE("crbegin/crend on const vector", "[iterators]") {
    const Vector<int> v = {10, 20, 30};
    auto it = v.crbegin();
    REQUIRE(*it == 30);
    ++it;
    REQUIRE(*it == 20);
}

TEST_CASE("std::sort works via random-access iterators", "[iterators]") {
    Vector<int> v = {5, 3, 1, 4, 2};
    std::sort(v.begin(), v.end());
    for (int i = 0; i < 5; ++i)
        REQUIRE(v[i] == i + 1);
}

TEST_CASE("std::accumulate works via iterators", "[iterators]") {
    Vector<int> v = {1, 2, 3, 4, 5};
    int total = std::accumulate(v.begin(), v.end(), 0);
    REQUIRE(total == 15);
}

TEST_CASE("empty vector begin equals end", "[iterators]") {
    Vector<int> v;
    REQUIRE(v.begin()  == v.end());
    REQUIRE(v.cbegin() == v.cend());
    REQUIRE(v.rbegin() == v.rend());
}

// ─────────────────────────────────────────────────────────────────────────────
// Capacity
// ─────────────────────────────────────────────────────────────────────────────

TEST_CASE("empty() reflects vector state", "[capacity]") {
    Vector<int> v;
    REQUIRE(v.empty());
    v.push_back(1);
    REQUIRE(!v.empty());
    v.pop_back();
    REQUIRE(v.empty());
}

TEST_CASE("size() tracks element count", "[capacity]") {
    Vector<int> v;
    REQUIRE(v.size() == 0);
    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
        REQUIRE(v.size() == static_cast<std::size_t>(i + 1));
    }
}

TEST_CASE("capacity() grows on push_back", "[capacity]") {
    Vector<int> v;
    REQUIRE(v.capacity() == 0);
    v.push_back(1);
    REQUIRE(v.capacity() >= 1);
    std::size_t prev = v.capacity();
    // Fill to capacity then add one more to force reallocation
    while (v.size() < prev) v.push_back(0);
    v.push_back(0);
    REQUIRE(v.capacity() > prev);
}

TEST_CASE("capacity() doubles on reallocation", "[capacity]") {
    Vector<int> v;
    v.push_back(1); // cap = 1
    std::size_t c1 = v.capacity();
    v.push_back(2); // triggers realloc → cap = 2
    std::size_t c2 = v.capacity();
    v.push_back(3); v.push_back(4); // triggers realloc → cap = 4
    std::size_t c4 = v.capacity();
    REQUIRE(c2 == c1 * 2);
    REQUIRE(c4 == c2 * 2);
}

TEST_CASE("reserve() increases capacity without changing size", "[capacity]") {
    Vector<int> v = {1, 2, 3};
    v.reserve(100);
    REQUIRE(v.size()     == 3);
    REQUIRE(v.capacity() >= 100);
    // Elements still intact
    REQUIRE(v[0] == 1);
    REQUIRE(v[2] == 3);
}

TEST_CASE("reserve() is a no-op when capacity already sufficient", "[capacity]") {
    Vector<int> v;
    v.reserve(50);
    std::size_t cap = v.capacity();
    v.reserve(10);
    REQUIRE(v.capacity() == cap);
}

TEST_CASE("reserve() preserves elements after reallocation", "[capacity]") {
    Vector<int> v = {10, 20, 30, 40, 50};
    v.reserve(1000);
    for (int i = 0; i < 5; ++i)
        REQUIRE(v[i] == (i + 1) * 10);
}

TEST_CASE("shrink_to_fit() reduces capacity to size", "[capacity]") {
    Vector<int> v;
    v.reserve(100);
    v.push_back(1);
    v.push_back(2);
    v.shrink_to_fit();
    REQUIRE(v.capacity() == v.size());
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
}

TEST_CASE("shrink_to_fit() on empty vector frees memory", "[capacity]") {
    Vector<int> v;
    v.reserve(50);
    v.shrink_to_fit();
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.data()     == nullptr);
}

TEST_CASE("max_size() is large and non-zero", "[capacity]") {
    Vector<int> v;
    REQUIRE(v.max_size() > 0);
    REQUIRE(v.max_size() >= (1u << 20));
}

TEST_CASE("size and capacity after clear()", "[capacity]") {
    Vector<int> v = {1, 2, 3, 4, 5};
    std::size_t cap = v.capacity();
    v.clear();
    REQUIRE(v.size()     == 0);
    REQUIRE(v.capacity() == cap); // capacity unchanged by clear
    REQUIRE(v.empty());
}
