#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Using long long for the sum to prevent overflow.
// Weights are up to 1000, N up to 300. Max path ~300,000.
// Sum of all pairs ~ 300*300 * 300,000 ~ 2.7 * 10^10, which fits in long long.
long long dist[305][305];

void solve() {
    int n;
    if (!(cin >> n)) return;

    // 1. Read the initial shortest distance matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> dist[i][j];
        }
    }

    int k;
    cin >> k;

    // 2. Process each new road
    for (int q = 0; q < k; q++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        // Optimization: Before running the N^2 loop, we can try to improve
        // the new edge weight itself using existing paths.
        // Actually, the N^2 loop handles everything, but we must treat the new edge
        // as a bridge.
        
        // We iterate through every pair (i, j) to see if the new road (u, v) helps.
        long long current_sum = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // Try route: i -> ... -> u -> v -> ... -> j
                long long route1 = dist[i][u] + w + dist[v][j];
                
                // Try route: i -> ... -> v -> u -> ... -> j
                long long route2 = dist[i][v] + w + dist[u][j];
                
                // Relaxation
                dist[i][j] = min(dist[i][j], min(route1, route2));
                
                // Add to sum only if i < j to avoid double counting and self-loops
                if (i < j) {
                    current_sum += dist[i][j];
                }
            }
        }
        
        cout << current_sum << (q == k - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}