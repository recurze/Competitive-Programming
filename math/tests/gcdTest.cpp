/**
 * File              : gcdTest.cpp
 * Author            : recurze
 * Date              : 15:47 25.12.2018
 * Last Modified Date: 16:29 25.12.2018
 */

#include "gcd.cpp"

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cassert>

void test_gcd() {
    int a, b, g;
    for (int i = 0; i < 10000000; ++i) {
        g = 1 + rand()%1000;
        a = (1 + rand()%100000)*g;
        b = (1 + rand()%100000)*g;
        assert(gcd(a, b) == std::__gcd(a, b));
    }
}

void test_egcd() {
    int a, b, g;
    for (int i = 0; i < 10000000; ++i) {
        g = 1 + rand()%1000;
        a = (1 + rand()%100000)*g;
        b = (1 + rand()%100000)*g;
        auto res = extended_gcd(a, b);
        assert(a*res.second.first + b*res.second.second == res.first);
        assert(res.first == std::__gcd(a, b));
    }
}

#include <chrono>
const int N = 10000000;
int a[N], b[N], g[N], ans[N], ans2[N];
void timeTest_gcd() {
    for (int i = 0; i < N; ++i) {
        g[i] = 1 + rand()%10000;
        a[i] = (1 + rand()%10000)*g[i];
        b[i] = (1 + rand()%10000)*g[i];
    }

    using milli = std::chrono::milliseconds;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) ans[i] = gcd(a[i], b[i]);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<milli>(finish-start).count()<<'\n';

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) ans2[i] = std::__gcd(a[i], b[i]);
    finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<milli>(finish-start).count()<<'\n';
    for (int i = 0; i < N; ++i) assert(ans[i] == ans2[i]);
}

int main() {
    srand(time(0));
    //test_gcd();
    //test_egcd();
    timeTest_gcd();
}
