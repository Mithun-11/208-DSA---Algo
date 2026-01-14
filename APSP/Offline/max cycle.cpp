#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Modified Floyd-Warshall to find maximum profit paths
// Returns true if there exists a positive cycle
bool hasPositiveCycleFloydWarshall(int n, vector<vector<double>>& dist) {
    // Floyd-Warshall for all pairs longest paths
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] > -1e18 && dist[k][j] > -1e18) {
                    dist[i][j] = max(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // Check if any node can reach itself with positive weight
    // This indicates a positive cycle
    for (int i = 0; i < n; i++) {
        if (dist[i][i] > 1e-9) {  // Use small epsilon for floating point comparison
            return true;
        }
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int tc = 1; tc <= T; tc++) {
        int N, R;
        double P;
        cin >> N >> R >> P;
        
        // Initialize distance matrix with -infinity
        vector<vector<double>> dist(N, vector<double>(N, -1e18));
        
        // Distance from a node to itself is 0 initially
        for (int i = 0; i < N; i++) {
            dist[i][i] = 0;
        }
        
        // Read edges and transform weights
        for (int i = 0; i < R; i++) {
            int A, B;
            double I, E;
            cin >> A >> B >> I >> E;
            
            // Transformed weight: Income - P * Expense
            double weight = I - P * E;
            
            // Keep maximum weight if multiple edges exist
            dist[A][B] = max(dist[A][B], weight);
        }
        
        cout << "Case " << tc << ": ";
        
        if (hasPositiveCycleFloydWarshall(N, dist)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}