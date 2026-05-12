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
