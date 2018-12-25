/**
 * File              : gcd.cpp
 * Author            : recurze
 * Date              : 12:28 25.12.2018
 * Last Modified Date: 16:17 25.12.2018
 */

#include <algorithm>

int gcd(int a, int b) {
    while (a && b) {
        if (a > b) a %= b;
        else b %= a;
    }
    return a + b;
}

// Bezout identity: as + bt = g = gcd(a, b)
// t, s  = a/g, b/g
std::pair<int, std::pair<int, int> > extended_gcd(int a, int b) {
    int r = b, oldr = a;
    int s = 0, olds = 1;
    int q;
    while (r) {
        q = oldr / r;
        oldr -= q * r; std::swap(r, oldr);
        olds -= q * s; std::swap(s, olds);
    }
    return { oldr, { olds, (oldr - 1L*a*olds)/b } };
}

// as + bt = g; n = b, inverse = s
int inverse(int a, int n) {
    int r = n, oldr = a;
    int s = 0, olds = 1;
    int q;
    while (r) {
        q = oldr / r;
        oldr -= q * r; std::swap(r, oldr);
        olds -= q * s; std::swap(s, olds);
    }
    if (oldr - 1) return -1;
    return olds + n*(olds < 0);
}
