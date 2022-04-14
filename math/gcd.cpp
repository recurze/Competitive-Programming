#include <algorithm>

// This fn is an exhibit only; prefer std::gcd of <numeric>
int gcd(int a, int b) {
    while (a && b) {
        if (a > b) a %= b;
        else b %= a;
    }
    return a + b;
}

// Bezout identity: as + bt = g = gcd(a, b)
// t, s  = a/g, b/g
template <typename T>
std::pair<T, std::pair<T, T> > extended_gcd(const T& a, const T& b) {
    T r = b, oldr = a;
    T s = 0, olds = 1;
    T q;
    while (r) {
        q = oldr / r;
        oldr -= q * r; std::swap(r, oldr);
        olds -= q * s; std::swap(s, olds);
    }
    return { oldr, { olds, (oldr - 1L*a*olds)/b } };
}

// as + bt = g; n = b, inverse = s
template <typename T>
T inverse(const T& a, const T& n) {
    auto [g, p] = extended_gcd(a, n);
    assert(g == 1);
    auto s = p.first; assert(s != 0);
    return s < 0 : s + n : s;
}
