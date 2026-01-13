#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;

void solve() {
    int n, m, k_limit;
    if (!(cin >> n >> m >> k_limit)) return;

    // dp[i][j][t] = Shortest path from i to j using exactly t tickets
    // We use vector for safety, but raw arrays dp[100][100][11] are faster
    vector<vector<vector<ll>>> dist(n, vector<vector<ll>>(n, vector<ll>(k_limit + 1, INF)));

    // 1. Initialization (Base Cases)
    for (int i = 0; i < n; i++) {
        // Distance to self is always 0 for any number of tickets
        for (int t = 0; t <= k_limit; t++) dist[i][i][t] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v; 
        ll w;
        cin >> u >> v >> w;
        u--; v--; // 0-based index

        // Standard edge (0 tickets)
        dist[u][v][0] = min(dist[u][v][0], w);
        dist[v][u][0] = min(dist[v][u][0], w); // If undirected

        // Magic edge (1 ticket)
        // Using 1 ticket makes the cost 0
        if (k_limit >= 1) {
            dist[u][v][1] = 0;
            dist[v][u][1] = 0;
        }
    }

    // 2. Floyd-Warshall with Resource Knapsack
    for (int pivot = 0; pivot < n; pivot++) { // this pivot is our standard k 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                
                // We want to calculate dist[i][j][t] for all possible t
                for (int t = 0; t <= k_limit; t++) {
                    
                    // Optimization: If current best is already small, we keep it
                    // But we must try to improve it by splitting tickets
                    
                    // Split t tickets into 'taken' (for i->pivot) and 'rem' (for pivot->j)
                    for (int taken = 0; taken <= t; taken++) {
                        int rem = t - taken;
                        
                        if (dist[i][pivot][taken] != INF && dist[pivot][j][rem] != INF) {
                            dist[i][j][t] = min(dist[i][j][t], 
                                                dist[i][pivot][taken] + dist[pivot][j][rem]);
                        }
                    }
                }
            }
        }
    }

    // 3. Output
    // The answer for "at most K" is min(dist[i][j][0...K])
    cout << "Shortest path using AT MOST " << k_limit << " tickets:\n";
    
    // Example: Print specific pair (0 to N-1)
    ll final_ans = INF;
    for(int t = 0; t <= k_limit; t++) final_ans = min(final_ans, dist[0][n-1][t]);
    
    if(final_ans == INF) cout << "Unreachable\n";
    else cout << final_ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}