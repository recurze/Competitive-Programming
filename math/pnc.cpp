const int N = 1000;
using mint = Mod<int>;

std::array<std::array<mint, N>, N> c;
void buildCTable(int n) {
    for (int i = 0; i <= n; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            c[i][j] += c[i - 1][j];
            c[i][j] += c[i - 1][j - 1];
        }
    }
}

mint nCrp(int n, int r, int p) {
    r = std::min(r, n - r);

    mint res(1, p);
    for (int i = 1; i <= r; ++i) {
        res *= (n - r + i);
        res /= i;
    }
    return res;
}

mint nCrModp(int n, int r, int p = MD) {
    if (r == 0) return 1;
    if (n < p) return nCrp(n, r, p);

    mint res(1, p);
    for (; r; n /= p, r /= p) {
        res *= nCrModp(n%p, r%p, p);
    }
    return res;
}

int nCrp_CRT(int n, int r, int m) {
    mint res(0, m);
    for (auto [f, _]: get_prime_factors_count(m)) {
        auto a = nCrModp(n, r, f);
        auto z = mint(m/f, f);
        auto y = inverse(z);
        auto w = z*y;
        res += a*w;
    }
    return res();
}

// This function is exhibit-only; use std::next_permutation of <algorithm>
//void perm() {
//    int c[n] = {0}, i = 0;
//    //do_something();
//    while (i < n) {
//        if (c[i] < i) {
//            (i&1) ? std::swap(a[i], a[c[i]]) : std::swap(a[i], a[0]);
//            //do_something();
//            ++c[i];
//            i = 0;
//        } else {
//            c[i++] = 0;
//        }
//    }
//}
