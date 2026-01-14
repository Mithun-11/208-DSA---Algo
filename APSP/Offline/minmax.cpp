#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

void solve(int C, int S, int Q, int case_num) {
    // 1. Initialize Distance Matrix
    // dist[i][j] stores the "Minimax" sound level between i and j
    vector<vector<int>> dist(C + 1, vector<int>(C + 1, INF));

    for (int i = 1; i <= C; i++) dist[i][i] = 0;

    // 2. Read Edges
    for (int i = 0; i < S; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // Graph is undirected ("two-way roads")
        dist[u][v] = w;
        dist[v][u] = w;
    }

    // 3. Floyd-Warshall (Minimax Variation)
    for (int k = 1; k <= C; k++) {
        for (int i = 1; i <= C; i++) {
            for (int j = 1; j <= C; j++) {
                // If a path exists through k...
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    // The "cost" of path i->k->j is the LOUDEST edge on that path.
                    int max_sound_on_path = max(dist[i][k], dist[k][j]);
                    
                    // We want the path with the SMALLEST "loudest edge".
                    dist[i][j] = min(dist[i][j], max_sound_on_path);
                }
            }
        }
    }

    // 4. Output Formatting
    if (case_num > 1) cout << "\n"; // Blank line between test cases
    cout << "Case #" << case_num << "\n";

    for (int i = 0; i < Q; i++) {
        int u, v;
        cin >> u >> v;
        if (dist[u][v] == INF) {
            cout << "no path\n";
        } else {
            cout << dist[u][v] << "\n";
        }
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int C, S, Q;
    int case_num = 1;

    // Loop until input is 0 0 0
    while (cin >> C >> S >> Q && (C != 0 || S != 0 || Q != 0)) {
        solve(C, S, Q, case_num++);
    }

    return 0;
}