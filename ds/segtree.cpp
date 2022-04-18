#include <cassert>
#include <vector>

template <typename T>
class SegmentTree {
#define mid(l, r) ((l) + ((r) - (l))>>1)
#define lchild(i) (i << 1)
#define rchild(i) ((i << 1) | 1)
public:
    SegmentTree(const std::vector<T>& _a) : n((int) _a.size()), a(_a), t(std::vector<Node>(n << 2)) {
        build(0, n);
    }

    T query(int l, int r) {
        assert(l < r);
        return _query(l, r, 1, 0, n);
    }

    void update(int pos, const T& new_value) {
        assert(0 <= pos and pos < n);
        _update(pos, new_value, 1, 0, n);
    }

    template <typename C>
    int find_first(int l, int r, const C& test) {
        assert(l < r);
        return _find_first(l, r, test);
    }
private:
    struct Node {
        T val;
        Node() { }
        Node(const T& v) : val(v) { }
        Node(const Node& node) : val(node.val) { }

        Node& operator=(const Node& node) {
            val = node.val;
            return *this;
        }

        Node& operator+=(const Node& node) {
            val = std::max(val, node.val);
            return *this;
        }

        operator T() const { return val; }

        friend Node operator+(Node node1, const Node& node2) { return node1 += node2; }
    };

    const int n;
    std::vector<T> a;
    std::vector<Node> t;

    void push_up(int i) { t[i] = t[lchild(i)] + t[rchild(i)]; }

    void build(int l, int r, int i = 1) {
        if (r - l == 1) {
            t[i] = Node(a[l]);
            return;
        }
        auto c = mid(l, r);
        build(l, c, lchild(i));
        build(c, r, rchild(i));
        push_up(i);
    }

    Node _query(int l, int r, int i, int tl, int tr) {
        assert(tl <= l and l < r and r <= tr);
        if (l == tl and r == tr) return t[i];
        auto tc = mid(tl, tr);
        if (r <= tc) return _query(l, r, lchild(i), tl, tc);
        if (l >= tc) return _query(l, r, rchild(i), tc, tr);
        return _query(l, tc, lchild(i), tl, tc) + _query(tc, r, rchild(i), tc, tr);
    }

    void _update(int pos, const T& new_value, int i, int tl, int tr) {
        if (tr - tl == 1) {
            assert(pos == tl);
            a[pos] = new_value;
            t[i] = Node(a[pos]);
            return;
        }
        auto tc = mid(tl, tr);
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
        if (not test(t[i])) return n;

        if (tr - tl == 1) return tl;

        auto tc = mid(tl, tr);
        if (r <= tc) return _find_first(l, r, test, lchild(i), tl, tc);
        if (l >= tc) return _find_first(l, r, test, rchild(i), tc, tr);

        auto f = _find_first(l, tc, test, lchild(i), tl, tc);
        return f != n ? f : _find_first(tc, r, test, rchild(i), tc, tr);
    }
};

template <typename T>
class LazySegmentTree {
#ifndef mid
#define mid(l, r) ((l) + ((r) - (l))>>1)
#define lchild(i) (i << 1)
#define rchild(i) (i << 1 | 1)
#endif
public:
    LazySegmentTree(const std::vector<T>& _a) :
        n((int) _a.size()), a(_a),
        t(std::vector<Node>(n << 2)),
#ifndef UNIFORM_APPLY
        lazy(std::vector<T>(n << 2, 0)) {
#else
        marked(std::vector<bool>(n << 2, false)) {
#endif
        build(0, n);
    }

    T query(int l, int r) {
        assert(l < r);
        return _query(l, r, 1, 0, n);
    }

    void apply_range(int l, int r, const T& v) {
        assert(0 <= l and l < r and r <= n);
        _apply_range(l, r, v, 1, 0, n);
    }
private:
    struct Node {
        T val;
        Node() { }
        Node(const T& v) : val(v) { }
        Node(const Node& node) : val(node.val) { }

        Node& operator=(const Node& node) {
            val = node.val;
            return *this;
        }

        Node& operator+=(const Node& node) {
            val = std::max(val, node.val);
            return *this;
        }

        operator T() const { return val; }

        friend Node operator+(Node node1, const Node& node2) { return node1 += node2; }
    };

    const int n;
    std::vector<T> a;
    std::vector<Node> t;

#ifndef UNIFORM_APPLY
    std::vector<T> lazy;

    void apply(int i, const T& v) {
        t[i].val += v; lazy[i] += v;
    }

    void push_down(int i) {
        if (lazy[i] != 0) {
            apply(lchild(i), lazy[i]);
            apply(rchild(i), lazy[i]);
            lazy[i] = 0;
        }
    }
#else
    std::vector<bool> marked;

    void apply(int i, const T& v) {
        t[i].val = v; marked[i] = true;
    }

    void push_down(int i) {
        if (marked[i]) {
            apply(lchild(i), t[i].val);
            apply(rchild(i), t[i].val);
            marked[i] = false;
        }
    }
#endif

    void push_up(int i) { t[i] = t[lchild(i)] + t[rchild(i)]; }

    void build(int l, int r, int i = 1) {
        if (r - l == 1) {
            t[i] = Node{a[l]};
            return;
        }
        auto c = l + (r - l)/2;
        build(l, c, lchild(i));
        build(c, r, rchild(i));
        push_up(i);
    }

    Node _query(int l, int r, int i, int tl, int tr) {
        assert(tl <= l and l < r and r <= tr);
#ifdef UNIFORM_APPLY
        if (marked[i]) return t[i];
#endif
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
