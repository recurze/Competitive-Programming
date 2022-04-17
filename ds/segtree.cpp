#include <cassert>
#include <vector>

template <typename T>
class SegmentTree {
#define lchild(i) (i << 1)
#define rchild(i) (i << 1 | 1)
public:
    SegmentTree(const std::vector<T>& a) : n((int) a.size()), a(a), t(std::vector<Segment>(n << 2)) {
        build(0, n);
    }

    T query(int l, int r) {
        assert(l < r);
        return _query(l, r, 1, 0, n).val;
    }

    void update(int pos, const T& new_value) {
        assert(0 <= pos and pos < n);
        _update(pos, new_value, 1, 0, n);
    }

    template <typename C>
    int find_first(int l, int r, const C& test) {
        return _find_first(l, r, test, 1, 0, n);
    }
private:
    struct Segment {
        T val;
    };

    const int n;
    std::vector<T> a;
    std::vector<Segment> t;

    static Segment combine(const Segment& a, const Segment& b) {
        return Segment{std::max(a.val, b.val)};
    }

    void push_up(int i) {
        t[i] = combine(t[lchild(i)], t[rchild(i)]);
    }

    void build(int l, int r, int i = 1) {
        if (r - l == 1) {
            t[i] = Segment{a[l]};
            return;
        }
        auto c = l + (r - l)/2;
        build(l, c, lchild(i));
        build(c, r, rchild(i));
        push_up(i);
    }

    Segment _query(int l, int r, int i, int tl, int tr) {
        assert(tl <= l and l < r and r <= tr);
        if (l == tl and r == tr) return t[i];
        auto tc = tl + (tr - tl)/2;
        if (r <= tc) return _query(l, r, lchild(i), tl, tc);
        if (l >= tc) return _query(l, r, rchild(i), tc, tr);
        return combine(_query(l, tc, lchild(i), tl, tc), _query(tc, r, rchild(i), tc, tr));
    }

    void _update(int pos, const T& new_value, int i, int tl, int tr) {
        if (tr - tl == 1) {
            assert(pos == tl);
            a[pos] = new_value;
            t[i] = Segment{a[pos]};
            return;
        }
        auto tc = tl + (tr - tl)/2;
        if (pos < tc) {
            _update(pos, new_value, lchild(i), tl, tc);
        } else {
            _update(pos, new_value, rchild(i), tc, tr);
        }
        push_up(i);
    }

    template <typename C>
    int _find_first(int l, int r, const C& test, int i, int tl, int tr) const {
        assert(tl <= l and l < r and r <= tr);
        if (not test(t[i].val)) return n;

        if (tr - tl == 1) return tl;

        auto tc = tl + (tr - tl)/2;
        if (r <= tc) return _find_first(l, r, test, lchild(i), tl, tc);
        if (l >= tc) return _find_first(l, r, test, rchild(i), tc, tr);

        auto f = _find_first(l, tc, test, lchild(i), tl, tc);
        return f != n ? f : _find_first(tc, r, test, rchild(i), tc, tr);
    }
};

template <typename T>
class LazySegmentTree {
#define lchild(i) (i << 1)
#define rchild(i) (i << 1 | 1)
public:
    LazySegmentTree(const std::vector<T>& a) :
        n((int) a.size()), a(a),
        t(std::vector<Segment>(n << 2)),
        lazy(std::vector<T>(n << 2, 0)),
        marked(std::vector<bool>(n << 2, false)) {
        build(0, n);
    }

    T query(int l, int r) {
        assert(l < r);
        return _query(l, r, 1, 0, n).val;
    }

    void apply_range(int l, int r, const T& v) {
        assert(0 <= l and l < r and r <= n);
        _apply_range(l, r, v, 1, 0, n);
    }
private:
    struct Segment {
        T val;
    };

    const int n;
    std::vector<T> a;
    std::vector<Segment> t;
    std::vector<T> lazy;
    std::vector<bool> marked;

    void apply(int i, const T& v) {
        //t[i].val = v; marked[i] = true;
        //t[i].val += v; lazy[i] += v;
    }

    static Segment combine(const Segment& a, const Segment& b) {
        return Segment{std::max(a.val, b.val)};
    }

    void push_up(int i) {
        t[i] = combine(t[lchild(i)], t[rchild(i)]);
    }

    void push_down(int i) {
        if (marked[i]) {
            apply(lchild(i), t[i].val);
            apply(rchild(i), t[i].val);
            marked[i] = false;
        }
        if (lazy[i] != 0) {
            apply(lchild(i), lazy[i]);
            apply(rchild(i), lazy[i]);
            lazy[i] = 0;
        }
    }

    void build(int l, int r, int i = 1) {
        if (r - l == 1) {
            t[i] = Segment{a[l]};
            return;
        }
        auto c = l + (r - l)/2;
        build(l, c, lchild(i));
        build(c, r, rchild(i));
        push_up(i);
    }

    Segment _query(int l, int r, int i, int tl, int tr) {
        assert(tl <= l and l < r and r <= tr);
        if (marked[i]) return t[i];
        if (l == tl and r == tr) return t[i];
        push_down(i);
        auto tc = tl + (tr - tl)/2;
        if (r <= tc) return _query(l, r, lchild(i), tl, tc);
        if (l >= tc) return _query(l, r, rchild(i), tc, tr);
        return combine(_query(l, tc, lchild(i), tl, tc), _query(tc, r, rchild(i), tc, tr));
    }

    void _apply_range(int l, int r, const T& v, int i, int tl, int tr) {
        if (l == r) return;
        assert(tl <= l and l < r and r <= tr);
        if (tl == l and r == tr) {
            apply(i, v);
            return;
        }
        push_down(i);
        auto tc = tl + (tr - tl)/2;
        if (l < tc) _apply_range(l, std::min(r, tc), v, lchild(i), tl, tc);
        if (r > tc) _apply_range(std::max(l, tc), r, v, rchild(i), tc, tr);
        push_up(i);
    }
};
