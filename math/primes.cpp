/**
 * File              : primes.cpp
 * Author            : recurze
 * Date              : 11:44 25.12.2018
 * Last Modified Date: 14:13 25.12.2018
 */

#include <cmath>
#include <vector>
#include <map>

bool isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n%6 != 1 && n%6 != 5) return 0;
    float m = sqrt(n);

    for (int i = 5, j = 7; i <= m; i += 6, j += 6) {
        if (!(n%i) || !(n%j)) {
            return 0;
        }
    }
    return 1;
}

const int N = 1010101;
bool prime[N] = {1};
void sieve(int n) {
    prime[0] = 0;
    prime[1] = 0;
    float m = sqrt(n);
    for (int i = 2; i <= m; ++i) {
        if (prime[i]) {
            for (int k = i*i; k<= n; k += i) {
                prime[k] = 0;
            }
        }
    }
}

template <typename T>
int removeDinN(T& n, T d) {
    int count = 0;
    while (!(n%d)) {
        n /= d;
        ++count;
    }
    return count;
}

std::map<int, int> getPrimefactorsCount(int n) {
    std::map<int, int> factorsCount;
    if (n < 2) return factorsCount;

    factorsCount.insert({2, removeDinN(n, 2)});
    factorsCount.insert({3, removeDinN(n, 3)});

    for (int i = 5, j = 7; i*i <= n ; i += 6, j += 6) {
        factorsCount.insert({i, removeDinN(n, i)});
        factorsCount.insert({j, removeDinN(n, j)});
    }
    if (n - 1) factorsCount.insert({n, 1});
    return factorsCount;
}

std::vector<int> getDistinctPrimeFactors(int n) {
    std::vector<int> factors;
    if (n < 2) return factors;

    if (removeDinN(n, 2)) factors.push_back(2);
    if (removeDinN(n, 3)) factors.push_back(3);

    for (int i = 5, j = 7; i*i <= n ; i += 6, j += 6) {
        if (removeDinN(n, i)) factors.push_back(i);
        if (removeDinN(n, j)) factors.push_back(j);
    }
    if (n - 1) factors.push_back(n);
    return factors;
}

std::vector<int> getDivisors(int n) {
    std::vector<int> divisors;
    float m = sqrt(n);

    for (int i = 1; i <= m; ++i) {
        if (!(n%i)) {
            divisors.push_back(i);
        }
    }
    return divisors;
}
