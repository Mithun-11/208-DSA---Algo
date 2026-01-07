#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q, s;
    while (cin >> n >> m >> q >> s && (n || m || q || s)) {
        vector<tuple<int,int,int>> edges;
        
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
        }
        
        // Bellman-Ford: relax n-1 times
        vector<long long> dist(n, INF);
        dist[s] = 0;
        
        for (int i = 0; i < n - 1; i++) {
            for (auto [u, v, w] : edges) {
                if (dist[u] < INF) {
                    dist[v] = min(dist[v], dist[u] + w);
                }
            }
        }
        
        // Detect negative cycle reachability: run n more iterations
        vector<bool> neg_cycle(n, false);
        
        for (int i = 0; i < n; i++) {
            for (auto [u, v, w] : edges) {
                if (dist[u] < INF) {
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        neg_cycle[v] = true;
                    }
                    if (neg_cycle[u]) {
                        neg_cycle[v] = true;
                    }
                }
            }
        }
        
        // Answer queries
        for (int i = 0; i < q; i++) {
            int t;
            cin >> t;
            
            if (dist[t] == INF) {
                cout << "Impossible\n";
            } else if (neg_cycle[t]) {
                cout << "-Infinity\n";
            } else {
                cout << dist[t] << "\n";
            }
        }
        cout << "\n";
    }
    
    return 0;
}