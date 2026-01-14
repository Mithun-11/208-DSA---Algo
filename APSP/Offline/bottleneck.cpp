#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Modified Floyd-Warshall for All Pairs Shortest Paths
// Find maximum bottleneck capacity between all pairs
void floydWarshall(vector<vector<int>>& capacity, int n) {
    // For each intermediate node k
    for (int k = 1; k <= n; k++) {
        // For each source i
        for (int i = 1; i <= n; i++) {
            // For each destination j
            for (int j = 1; j <= n; j++) {
                // Path through k: min capacity of i->k and k->j
                int pathThroughK = min(capacity[i][k], capacity[k][j]);
                // Take maximum of direct path vs path through k
                capacity[i][j] = max(capacity[i][j], pathThroughK);
            }
        }
    }
}

int main() {
    int n, m;
    int caseNum = 1;
    
    while (cin >> n >> m && (n || m)) {
        // Initialize capacity matrix with 0
        vector<vector<int>> capacity(n + 1, vector<int>(n + 1, 0));
        
        for (int i = 0; i < m; i++) {
            int u, v, cap;
            cin >> u >> v >> cap;
            // Bidirectional road, keep maximum capacity if multiple edges
            capacity[u][v] = max(capacity[u][v], cap);
            capacity[v][u] = max(capacity[v][u], cap);
        }
        
        int src, dest, tourists;
        cin >> src >> dest >> tourists;
        
        // Find maximum bottleneck paths for all pairs
        floydWarshall(capacity, n);
        
        // Get the maximum capacity path from src to dest
        int maxCap = capacity[src][dest];
        
        // Each trip can carry (maxCap - 1) tourists (guide takes 1 seat)
        int perTrip = maxCap - 1;
        
        // Calculate minimum trips needed (ceiling division)
        int trips = (tourists + perTrip - 1) / perTrip;
        
        cout << "Scenario #" << caseNum++ << endl;
        cout << "Minimum Number of Trips = " << trips << endl;
        cout << endl;
    }
    
    return 0;
}