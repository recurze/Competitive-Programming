#include <algorithm>

const int N = 1000;

std::array<std::array<int, N>, N> c;
void buildCTable(int n) {
    for (int i = 0; i <= n; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            add_to(c[i][j], c[i - 1][j]);
            add_to(c[i][j], c[i - 1][j - 1]);
        }
    }
}

int nCrp(int n, int r, int p = MD) {
    if (r > n/2) r = n - r;

    int res = 1;
    for (int i = 1; i <= r; ++i) {
        res = mul(res, div(n - r + i, i, p), p);
    }
    return res;
}

int nCrModp(int n, int r, int p = MD) {
    if (r == 0) return 1;
    if (n < p) return nCrp(n, r, p);

    int res = 1;
    for (; r; n /= p, r /= p) {
        res = mul(res, nCrModp(n%p, r%p, p), p);
    }
    return res;
}

int nCrp_CRT(int n, int r, int p) {
    int res = 0;
    for (auto f: get_prime_factors(p)) {
        int a = nCrModp(n, r, f);
        int z = p/f;
        int y = inverse(z, f);
        int w = mul(z, y, p);
        add(res, mul(a, w, p));
    }
    return res;
}

// This function is exhibit-only; use std::next_permutation of <algorithm>
void perm() {
    int c[n] = {0}, i = 0;
    //do_something();
    while (i < n) {
        if (c[i] < i) {
            (i&1) ? std::swap(a[i], a[c[i]]) : std::swap(a[i], a[0]);
            //do_something();
            ++c[i];
            i = 0;
        } else {
            c[i++] = 0;
        }
    }
}
