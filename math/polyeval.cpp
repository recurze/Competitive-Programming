/**
 * File              : polyeval.cpp
 * Author            : recurze
 * Date              : 14:21 25.12.2018
 * Last Modified Date: 15:46 25.12.2018
 */

#include <vector>

int n;
std::vector<int> coef;
void build(int _n, std::vector<int> f) {
    n = _n;
    coef = f;
    int j;
    for (int i = 0; i < n; ++i) {
        j = n;
        while (j > i) {
            coef[j] -= coef[--j];
        }
    }
}

int eval(int x) {
    int m = 1, res = 0;
    for (int i = 0; i <= n; ++i) {
        res += mul(coef[i], m);
        m = mul(m, div(x - i, i + 1));
    }
    return res;
}
