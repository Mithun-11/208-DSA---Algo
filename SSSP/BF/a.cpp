#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

const int INF = 1e9; // Use a sufficiently large number

struct Edge {
    int u, v, w;
};

void solve() {
    int n, m, q, s;
    while (cin >> n >> m >> q >> s && (n || m || q || s)) {
        vector<Edge> edges;
        vector<vector<int>> adj(n); // Adjacency list for the BFS part

        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
            adj[u].push_back(v);
        }

        vector<int> dist(n, INF);
        dist[s] = 0;

        // Step 1: Standard Bellman-Ford Relaxation (N-1 times)
        for (int i = 0; i < n - 1; ++i) {
            bool changed = false;
            for (const auto& e : edges) {
                if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = max(-INF, dist[e.u] + e.w); // Avoid underflow for very small nums
                    changed = true;
                }
            }
            if (!changed) break; // Optimization: stop if no updates
        }

        // Step 2 & 3: Detect Negative Cycles and Propagate
        vector<bool> is_infinite(n, false);
        queue<int> q_bfs;

        for (const auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                // We found a node reachable from a negative cycle
                if (!is_infinite[e.v]) {
                    is_infinite[e.v] = true;
                    q_bfs.push(e.v);
                }
            }
        }

        // BFS to mark all nodes reachable from the cycle nodes
        while (!q_bfs.empty()) {
            int u = q_bfs.front();
            q_bfs.pop();

            for (int v : adj[u]) {
                if (!is_infinite[v]) {
                    is_infinite[v] = true;
                    q_bfs.push(v);
                }
            }
        }

        // Handle Queries
        for (int i = 0; i < q; ++i) {
            int target;
            cin >> target;
            
            if (dist[target] == INF) {
                cout << "Impossible" << endl;
            } else if (is_infinite[target]) {
                cout << "-Infinity" << endl;
            } else {
                cout << dist[target] << endl;
            }
        }
        cout << endl; // Blank line between test cases
    }
}

int main() {
    solve();
    return 0;
}