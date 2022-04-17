void dfs(const auto& adj) {
    enum Color {WHITE, GRAY, BLACK};
    std::vector<Color> color(n, WHITE);

    std::function<void(int)> _dfs = [&](int u, int p) {
        color[u] = GRAY;
        for (auto v: adj[u]) {
            if (color[v] == WHITE) {
                dfs(v, u);
            } else if (color[v] == GRAY) {
            } else {
            }
        }
        color[u] = BLACK;
    };

    rep(u, n) if (color[u] == WHITE) _dfs(u, u);
}

auto bfs = [&](int start) {
    std::queue<int> q;
    std::vector<int> depth(n, INF);
    std::vector<int> parent(n, -1);

    q.push(start); parent[start] = start;
    while (not q.empty()) {
        auto u = q.front(); q.pop();
        for (auto v: adj[u]) if (depth[v] == INF) {
            q.push(v);
            depth[v] = depth[u] + 1; parent[v] = u;
        }
    }
    return depth, parent;
};

auto djikstra = [&](int start) {
    using ii = std::pair<int, int>;

    std::priority_queue<ii, std::vector<ii>, std::less<ii>> pq;
    std::vector<int> distance(n, INF);
    std::vector<int> parent(n, -1);

    distance[start] = 0;
    parent[start] = start;
    pq.push({distance[start], start});

    while (not pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > distance[u]) continue;
        assert(d == distance[u]);
        for (auto [v, w]: adj[u]) {
            if (distance[v] > d + w) {
                distance[v] = d + w;
                parent[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance, parent;
};
