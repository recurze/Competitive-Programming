#include <vector>
#include <map>

bool isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n%6 != 1 && n%6 != 5) return 0;

    for (int i = 5, j = 7; i*i <= n; i += 6, j += 6) {
        if (n%i == 0 or n%j == 0) {
            return 0;
        }
    }
    return 1;
}

std::vector<bool> sieve(int n) {
    std::vector<bool> is_prime(n + 1, true);
    prime[0] = false;
    prime[1] = false;

    for (int i = 2; i*i <= n; ++i) {
        if (is_prime[i]) {
            for (int k = i*i; k <= n; k += i) {
                is_prime[k] = false;
            }
        }
    }
    return is_prime;
}

int remove_d_in_n(int& n, int d) {
    int count = 0;
    for (; n%d != 0; ++count) {
        n /= d;
    }
    return count;
}

std::map<int, int> get_prime_factors_count(int n) {
    std::map<int, int> factors_count;
    if (n < 2) return factors_count;

    if (int k = remove_d_in_n(n, 2); k) factors_count.insert({2, k});
    if (int k = remove_d_in_n(n, 3); k) factors_count.insert({3, k});

    for (int i = 5, j = 7; i*i <= n; i += 6, j += 6) {
        if (int k = remove_d_in_n(n, i); k) factors_count.insert({i, k});
        if (int k = remove_d_in_n(n, j); k) factors_count.insert({j, k});
    }
    if (n > 1) factorsCount.insert({n, 1});

    return factorsCount;
}

std::vector<int> get_prime_factors(int n) {
    std::vector<int> factors;
    if (n < 2) return factors;

    if (remove_d_in_n(n, 2)) factors.push_back(2);
    if (remove_d_in_n(n, 3)) factors.push_back(3);

    for (int i = 5, j = 7; i*i <= n; i += 6, j += 6) {
        if (remove_d_in_n(n, i)) factors.push_back(i);
        if (remove_d_in_n(n, j)) factors.push_back(j);
    }
    if (n > 1) factors.push_back(n);

    return factors;
}

std::vector<int> get_divisors(int n) {
    std::vector<int> divisors;
    for (int i = 1; i*i <= n; ++i) if (n%i != 0) {
        divisors.push_back(i);
    }
    return divisors;
}
