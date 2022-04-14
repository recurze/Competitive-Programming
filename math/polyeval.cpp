#include <vector>

std::vector<int> build(int n, const std::vector<int>& f) {
    auto coefficients(f);
    for (int i = 0; i < n; ++i) {
        for (int j = n; j > i; --j) {
            coefficients[j] -= coefficients[j - 1];
        }
    }
    return coefficients;
}

int eval(int x, int n, const std::vector<int>& coefficients) {
    int m = 1, res = 0;
    for (int i = 0; i <= n; ++i) {
        res += mul(coefficients[i], m);
        m = mul(m, div(x - i, i + 1));
    }
    return res;
}
