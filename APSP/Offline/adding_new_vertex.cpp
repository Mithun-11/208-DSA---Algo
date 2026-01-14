#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
// Max N is usually around 300-500 for these problems
long long dist[505][505]; 

void solve() {
    int n;
    if (!(cin >> n)) return;

    // 1. Read existing Shortest Path Matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> dist[i][j];
        }
    }

    // 2. Read New City Connections
    int num_new_roads;
    cin >> num_new_roads;

    int new_city = n + 1;
    vector<pair<int, int>> new_edges; // Stores {neighbor, weight}

    // Initialize new row/col with INF
    for (int i = 1; i <= n; i++) {
        dist[new_city][i] = INF;
        dist[i][new_city] = INF;
    }
    dist[new_city][new_city] = 0;

    // Read edges and tentatively set direct weights
    for (int i = 0; i < num_new_roads; i++) {
        int u; 
        long long w;
        cin >> u >> w;
        new_edges.push_back({u, w});
        
        // It's possible multiple roads connect to the same city, take min
        dist[new_city][u] = min(dist[new_city][u], w);
        dist[u][new_city] = min(dist[u][new_city], w);
    }

    // 3. PHASE 1: Calculate full shortest paths TO/FROM the New City
    // We iterate through every existing city 'i' and check if we can reach it
    // faster by hopping through one of the new city's direct neighbors.
    
    for (int i = 1; i <= n; i++) {
        // Try entering/exiting via every connected neighbor 'u'
        for (auto edge : new_edges) {
            int u = edge.first;
            long long w = edge.second;

            // From New City -> Neighbor u -> City i
            dist[new_city][i] = min(dist[new_city][i], w + dist[u][i]);

            // From City i -> Neighbor u -> New City
            dist[i][new_city] = min(dist[i][new_city], dist[i][u] + w);
        }
    }

    // 4. PHASE 2: Use the New City as a Pivot to update existing pairs
    // Now that we know the cost to reach N+1 from anywhere, we check
    // if N+1 acts as a shortcut between any old cities i and j.
    
    long long total_sum = 0;

    // Loop includes the new city (up to n+1)
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n + 1; j++) {
            
            // Standard FW relaxation using the new node
            dist[i][j] = min(dist[i][j], dist[i][new_city] + dist[new_city][j]);

            // Calculate sum (only for i < j to avoid duplicates/self-loop)
            if (i < j) {
                total_sum += dist[i][j];
            }
        }
    }

    cout << total_sum << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}