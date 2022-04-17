// first 1 in [l, r) or r
template <typename C>
int binary_search(int l, int r, const C& cond) {
    if (r - l == 1) return cond(l) ? l : r;
    int c = l + (r - l)/2;
    return cond(c - 1) ? binary_search(l, c, cond) : binary_search(c, r, cond);
}

// first 1 in [l, r) or r
template <typename T, typename F>
T binary_search(T l, T r, const F& test) {
    if (test(l)) return l;

    for (auto step = r - l; ; step = (step + 1) >> 1) {
        if (l + step < r and not test(l + step)) {
            l += step;
        }
        if (step == 1) break;
    }
    ++l;

    assert(l == r or test(l));
    return l;
}
