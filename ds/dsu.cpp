class DSU {
public:
    DSU(int _n): n(_n), parent(std::vector<int>(n)), size(std::vector<int>(n, 1)) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    void union_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) {
                std::swap(a, b);
            }
            parent[b] = a; size[a] += size[b];
        }
    }

    int find_set(int v) {
        assert(0 <= v and v < n);
        return v == parent[v] ? v : (parent[v] = find_set(parent[v]));
    }
private:
    int n;
    std::vector<int> parent;
    std::vector<int> size;
};
