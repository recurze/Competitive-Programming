#include <cstdint>
#include <algorithm>

// This fn is an exhibit only; prefer std::gcd of <numeric>
int gcd(int a, int b) {
    while (a && b) {
        if (a > b) a %= b;
        else b %= a;
    }
    return a + b;
}

template <typename T>
std::enable_if_t<std::is_signed<T>::value, T> binary_gcd(T a, T b) {
    if (a == 0) return b;
    if (b == 0) return a;

    auto az = __builtin_ctz(a);
    auto bz = __builtin_ctz(b); b >>= bz;
    auto shift = std::min(az, bz);

    while (a != 0) {
        a >>= az;
        auto diff = b - a;
        az = __builtin_ctz(diff);
        b = std::min(a, b);
        a = std::abs(diff);
    }

    return b << shift;
}

// Bezout identity: as + bt = g = gcd(a, b)
// t-step, s-step = +a/g, -b/g
template <typename T>
std::pair<T, std::pair<T, T> > extended_gcd(const T& a, const T& b) {
    T r = b, oldr = a;
    T s = 0, olds = 1;
    while (r) {
        auto q = oldr / r;
        oldr -= q * r; std::swap(r, oldr);
        olds -= q * s; std::swap(s, olds);
    }
    return { oldr, { olds, (oldr - (std::int64_t) a*olds)/b } };
}

// as + bt = g; n = b, inverse = s
template <typename T>
T inverse(const T& a, const T& n) {
    auto [g, p] = extended_gcd(a, n);
    assert(g == 1);
    return p.first < 0 ? p.first + n : p.first;
}
