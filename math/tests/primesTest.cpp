/**
 * File              : primesTest.cpp
 * Author            : recurze
 * Date              : 17:07 25.12.2018
 * Last Modified Date: 21:34 25.12.2018
 */

#include "primes.cpp"

#include <cassert>
#include <cmath>
#include <iostream>

void test_prime() {
    sieve(1010101);
    for (int i = 1; i < 1010101; ++i) {
        if (prime[i]) {
            std::cerr<<i<<'\n';
        }
        assert (prime[i] == isPrime(i));
    }
}

void test_primefactors() {
    int n, m, j;
    for (int i = 0; i < 100000; ++i) {
        n = rand();
        auto pfc = getPrimefactorsCount(n);
        auto pf = getDistinctPrimeFactors(n);
        m = 1, j = 0;
        for (auto& fc: pfc) {
            for (int c = 0; c < fc.second; ++c) {
                assert(isPrime(fc.first));
                m *= (fc.first);
            }
            assert(pf[j++] == fc.first);
        }

        std::cerr<<n<<'\n';
        assert (n == m);
    }
}

void test_divisors() {
    auto d = getDivisors(110);
    for (int i: d) {
        std::cerr<<i<<' ';
    }
}

int main() {
    test_prime();
    srand(time(0));
    test_primefactors();
    test_divisors();
    return 0;
}
