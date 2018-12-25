/**
 * File              : pnc.cpp
 * Author            : recurze
 * Date              : 13:54 25.12.2018
 * Last Modified Date: 14:21 25.12.2018
 */

#include <algorithm>

const int N = 1000;
int c[N][N];
void buildCTable(int n) {
    for (int i = 0; i <= n; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            add(c[i][j], c[i - 1][j    ]);
            add(c[i][j], c[i - 1][j - 1]);
        }
    }
}

int nCrp(int n, int r, int p = MD) {
    int res = 1;
    if (r > n/2) r = n - r;
    for (int i = 1; i <= r; ++i) {
        res = mul(res, div(n - r + i, i, p), p);
    }
    return res;
}

int nCrModp(int n, int r, int p = MD) {
    if (!r) return 1;
    if (n < p) return nCrp(n, r, p);
    int res = 1;
    while (r) {
        res = mul(res, nCrModp(n%p, r%p, p));
        n /= p;
        r /= p;
    }
    return res;
}

int nCrp_CRT(int n, int r, int p) {
    int a, z, y, w, res = 0;
    for (const int& f: getDistinctPrimeFactors(p)) {
        a = nCrModp(n, r, f);
        z = p/f;
        y = inverse(z, f);
        w = mul(z, y, p);
        add(res, mul(a, w, p));
    }
    return res;
}

void print() {
    for (int i = 0; i < n; ++i) {
        //printf("%d ", a[i]);
    }
    //printf("\n");
}

void perm(){
    int c[n] = {0}, i = 0;
    print();
    while (i < n) {
        if (c[i] < i) {
            if (i&1) std::swap(a[i], a[c[i]]);
            else std::swap(a[i], a[0]);
            print();
            ++c[i];
            i = 0;
        } else {
            c[i++] = 0;
        }
    }
}
