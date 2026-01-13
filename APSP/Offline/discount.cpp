#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    // dp[i][j][0] = Shortest path using 0 tickets
    // dp[i][j][1] = Shortest path using 1 ticket
    vector<vector<vector<ll>>> dist(n, vector<vector<ll>>(n, vector<ll>(2, INF)));

    // Initialization
    for (int i = 0; i < n; i++) {
        dist[i][i][0] = 0;
        dist[i][i][1] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v; 
        ll w;
        cin >> u >> v >> w;
        
        // 0-based indexing assumption; remove -- if inputs are 0-based
        u--; v--; 

        // Update Standard Edge
        dist[u][v][0] = min(dist[u][v][0], w);
        
        // Update Magic Edge (Cost is 0)
        // This represents using the ticket on this specific direct edge
        dist[u][v][1] = 0; 

        // If graph is undirected, mirror the edges
        // dist[v][u][0] = min(dist[v][u][0], w);
        // dist[v][u][1] = 0;
    }

    // Modified Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                
                // 1. Standard Relaxation (0 tickets)
                if (dist[i][k][0] != INF && dist[k][j][0] != INF) {
                    dist[i][j][0] = min(dist[i][j][0], dist[i][k][0] + dist[k][j][0]);
                }

                // 2. Magic Relaxation (1 ticket)
                // Option A: Ticket used in the first half (i->k)
                if (dist[i][k][1] != INF && dist[k][j][0] != INF) {
                    dist[i][j][1] = min(dist[i][j][1], dist[i][k][1] + dist[k][j][0]);
                }

                // Option B: Ticket used in the second half (k->j)
                if (dist[i][k][0] != INF && dist[k][j][1] != INF) {
                    dist[i][j][1] = min(dist[i][j][1], dist[i][k][0] + dist[k][j][1]);
                }
            }
        }
    }

    // Output Result
    // The answer is min(path with 0 tickets, path with 1 ticket)
    cout << "Min Cost Matrix (at most 1 magic ticket):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll ans = min(dist[i][j][0], dist[i][j][1]);
            if (ans == INF) cout << "INF ";
            else cout << ans << " ";
        }
        cout << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}