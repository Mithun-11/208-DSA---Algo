#include <bits/stdc++.h>
using namespace std;

struct Edge { int u, v, w, id; };

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w, i});
    }

    vector<bool> active(m, true);
    int removed_count = 0;

    while (true) {
        vector<long long> dist(n + 1, 0);
        vector<int> p(n + 1, -1);
        vector<int> edge_from(n + 1, -1);
        int x = -1;

        // 1. Bellman-Ford Relaxation
        for (int i = 0; i < n; ++i) {
            x = -1;
            for (const auto& e : edges) {
                if (!active[e.id]) continue;
                if (dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                    p[e.v] = e.u;
                    edge_from[e.v] = e.id;
                    x = e.v;
                }
            }
        }

        // 2. If no relaxation in nth step, no negative cycle exists
        if (x == -1) break;

        // 3. Step back n times to ensure we are inside the cycle (avoids the tail)
        for (int i = 0; i < n; ++i) x = p[x];

        // 4. Identify the cycle edges
        vector<int> cycle_indices;
        int curr = x;
        while (true) {
            int id = edge_from[curr];
            cycle_indices.push_back(id);
            curr = p[curr];
            if (curr == x && cycle_indices.size() > 0) break;
        }

        // 5. Find and remove the "best" edge (max weight)
        int best_edge = -1;
        int max_w = INT_MAX;
        
        for (int id : cycle_indices) {
            if (edges[id].w < max_w) {
                max_w = edges[id].w;
                best_edge = id;
            }
        }

        active[best_edge] = false;
        removed_count++;
    }

    cout << removed_count << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}
