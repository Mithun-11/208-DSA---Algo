#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
const ll MOD = 1e9 + 7; // Optional: Use if counts get very large

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    vector<vector<ll>> count(n, vector<ll>(n, 0));

    // 1. Initialization
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        count[i][i] = 1; // 1 way to stay at start (do nothing)
    }

    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        u--; v--; // Assuming 1-based input

        if (w < dist[u][v]) {
            dist[u][v] = w;
            count[u][v] = 1;
        } else if (w == dist[u][v]) {
            count[u][v]++;
        }
    }

    // 2. Floyd-Warshall with Counting
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                
                // Avoid overflow checks with INF
                if (dist[i][k] == INF || dist[k][j] == INF) continue;

                ll new_dist = dist[i][k] + dist[k][j];

                if (new_dist < dist[i][j]) {
                    // Found a strictly better path
                    dist[i][j] = new_dist;
                    count[i][j] = (count[i][k] * count[k][j]) % MOD;
                } 
                else if (new_dist == dist[i][j]) {
                    // Found another path of the same length
                    ll additional_ways = (count[i][k] * count[k][j]) % MOD;
                    count[i][j] = (count[i][j] + additional_ways) % MOD;
                }
            }
        }
    }

    // Output
    cout << "Shortest Path Counts (0 -> " << n-1 << "): " << count[0][n-1] << endl;
}

signed main() {
    solve();
    return 0;
}