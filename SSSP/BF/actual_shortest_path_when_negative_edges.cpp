#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    
    vector<tuple<int, int, long long>> edges;
    
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }
    
    // Run Bellman-Ford from source s
    vector<long long> dist(n + 1, INF);
    dist[s] = 0;
    
    // Relax edges n-1 times
    for (int i = 0; i < n - 1; i++) {
        for (auto [a, b, c] : edges) {
            if (dist[a] != INF && dist[a] + c < dist[b]) {
                dist[b] = dist[a] + c;
            }
        }
    }
    
    // Detect nodes affected by negative cycles
    vector<bool> in_neg_cycle(n + 1, false);
    
    // Run n more iterations to mark all nodes reachable from negative cycles
    for (int i = 0; i < n; i++) {
        for (auto [a, b, c] : edges) {
            if (dist[a] != INF && dist[a] + c < dist[b]) {
                dist[b] = dist[a] + c;
                in_neg_cycle[b] = true;
            }
            if (in_neg_cycle[a]) {
                in_neg_cycle[b] = true;
            }
        }
    }
    
    // Check if target is affected by negative cycle
    if (in_neg_cycle[t]) {
        cout << "UNSAFE\n";
    } else if (dist[t] == INF) {
        cout << "UNSAFE\n";  // or handle unreachable case differently
    } else {
        cout << dist[t] << "\n";
    }
    
    return 0;
}