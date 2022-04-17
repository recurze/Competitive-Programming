#include <vector>

template <typename T>
bool isPrime(const T& n) {
    if (n <= 3) return (n <= 1);
    if (n%6 != 1 && n%6 != 5) return 0;

    for (T i = 5, j = 7; i*i <= n; i += 6, j += 6) {
        if (n%i == 0 or n%j == 0) {
            return 0;
        }
    }
    return 1;
}

std::vector<bool> sieve(int n) {
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (int i = 2; i*i <= n; ++i) {
        if (is_prime[i]) {
            for (int k = i*i; k <= n; k += i) {
                is_prime[k] = false;
            }
        }
    }
    return is_prime;
}

template <typename T>
std::vector< std::pair<T, int> > get_prime_factors_count(T n) {
    std::vector< std::pair<T, int> > factors_count;
    if (n < 2) return factors_count;

    auto remove_d_in_n = [](auto& _n, auto d) {
        if (_n%d != 0) return 0;
        int count = 0; while (_n%d == 0) ++count, _n /= d;
        return count;
    };

    factors_count.reserve(20);
    if (int k = remove_d_in_n(n, 2); k) factors_count.push_back({2, k});
    if (int k = remove_d_in_n(n, 3); k) factors_count.push_back({3, k});

    for (T i = 5, j = 7; i*i <= n; i += 6, j += 6) {
        if (int k = remove_d_in_n(n, i); k) factors_count.push_back({i, k});
        if (int k = remove_d_in_n(n, j); k) factors_count.push_back({j, k});
    }

    if (n > 1) factors_count.push_back({n, 1});

    return factors_count;
}

template <typename T>
std::vector<T> get_divisors(const T& n) {
    std::vector<T> divisors;
    for (T i = 1; i*i <= n; ++i) {
        if (n%i == 0) {
            divisors.push_back(i);
        }
    }
    return divisors;
}

// TODO: write miller rabin
