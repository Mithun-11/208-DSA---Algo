#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
const int INF_HOPS = 1e9;

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    // dist[i][j] stores the minimum weight
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    
    // hops[i][j] stores the number of edges for that minimum weight path
    vector<vector<int>> hops(n, vector<int>(n, INF_HOPS));

    // Initialization
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        hops[i][i] = 0; // 0 edges to go from i to i
    }

    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        // u--; v--; // Uncomment for 1-based input

        // Handle multi-edges: keep smallest weight
        if (w < dist[u][v]) {
            dist[u][v] = w;
            hops[u][v] = 1; // Direct edge = 1 hop
        }
        // If weights are equal, keep the one with 1 hop (default behavior)
        else if (w == dist[u][v]) {
            hops[u][v] = min(hops[u][v], 1);
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                
                // Safety check to avoid adding INF
                if (dist[i][k] == INF || dist[k][j] == INF) continue;

                ll new_dist = dist[i][k] + dist[k][j];
                int new_hops = hops[i][k] + hops[k][j];

                // Case 1: Found a strictly shorter path (by weight)
                if (new_dist < dist[i][j]) {
                    dist[i][j] = new_dist;
                    hops[i][j] = new_hops;
                }
                // Case 2: Found a path with EQUAL weight
                else if (new_dist == dist[i][j]) {
                    // Tie-breaker: Pick the one with fewer edges
                    if (new_hops < hops[i][j]) {
                        hops[i][j] = new_hops;
                    }
                }
            }
        }
    }

    // Output
    cout << "Shortest Path (Weight, Hops) from 0 to " << n-1 << ":\n";
    if (dist[0][n-1] == INF) {
        cout << "Unreachable\n";
    } else {
        cout << "Weight: " << dist[0][n-1] << ", Edges: " << hops[0][n-1] << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}