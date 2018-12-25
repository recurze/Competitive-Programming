/**
 * File              : primesTest.cpp
 * Author            : recurze
 * Date              : 17:07 25.12.2018
 * Last Modified Date: 17:41 25.12.2018
 */

#include "primes.cpp"

#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    sieve(1010101);
    for (int i = 1; i < 1010101; ++i) {
        assert (prime[i] == isPrime(i));
        if (prime[i]) {
            std::cout<<i<<'\n';
        }
    }
    return 0;
}
