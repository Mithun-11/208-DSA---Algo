#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

void solve() {
    int n, m;
    cin >> n >> m;

    // Size is 2*N
    // Indices 0 to n-1: Even State
    // Indices n to 2n-1: Odd State
    int size = 2 * n;
    vector<vector<long long>> dist(size, vector<long long>(size, INF));

    // Distance to self (Even steps, 0 edges) is 0
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;           // Even -> Even (Cost 0)
        dist[i + n][i + n] = 0;   // Odd -> Odd (Cost 0)
    }

    for (int i = 0; i < m; i++) {
        int u, v; 
        long long w;
        cin >> u >> v >> w;
        // u--; v--; // If input is 1-based

        // Edge u -> v flips parity
        // From u(Even) -> v(Odd)
        dist[u][v + n] = min(dist[u][v + n], w);
        
        // From u(Odd) -> v(Even)
        dist[u + n][v] = min(dist[u + n][v], w);

        // If undirected, add v -> u
        dist[v][u + n] = min(dist[v][u + n], w);
        dist[v + n][u] = min(dist[v + n][u], w);
    }

    // Standard Floyd-Warshall on 2N nodes
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Queries
    int q; cin >> q;
    while(q--) {
        int u, v; cin >> u >> v;
        // u--; v--;
        
        long long evenPath = dist[u][v];
        long long oddPath = dist[u][v + n];

        cout << "Even Path: " << (evenPath == INF ? -1 : evenPath) << "\n";
        cout << "Odd Path:  " << (oddPath == INF ? -1 : oddPath) << "\n";
    }
}

int main() {
    solve();
    return 0;
}