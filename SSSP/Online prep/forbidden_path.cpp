#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

// Types and Constants
using ll = long long;
const ll INF = 1e18;

struct Edge {
    int to;
    ll weight;
};

// Represents a state in the Dijkstra process
struct State {
    ll cost;
    int u;      // Current Node
    int prev;   // Previous Node

    // Priority Queue requires 'greater' for Min-Heap behavior
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    // 1. Graph Setup
    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // 2. Forbidden Triplets (Using Set for cleaner lookups)
    set<tuple<int, int, int>> forbidden;
    for (int i = 0; i < k; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        forbidden.insert({a, b, c});
    }

    // 3. Dijkstra Initialization
    // dist[current][previous] stores the min cost
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
    vector<vector<int>> parent(n + 1, vector<int>(n + 1, -1));

    priority_queue<State, vector<State>, greater<State>> pq;

    // Start at Node 1, assuming we came from a dummy Node 0
    dist[1][0] = 0;
    pq.push({0, 1, 0});

    ll final_cost = INF;
    int end_prev = -1;

    // 4. Main Loop
    while (!pq.empty()) {
        State top = pq.top();
        pq.pop();

        int u = top.u;
        int p = top.prev;
        ll d = top.cost;

        // Lazy Deletion: If we found a better way to this state, skip
        if (d > dist[u][p]) continue;

        // If we reached the target, record it and stop
        if (u == n) {
            final_cost = d;
            end_prev = p;
            break; 
        }

        // Explore neighbors
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            ll w = edge.weight;

            // Check if the sequence (p -> u -> v) is forbidden
            // Note: p=0 is the dummy start, so no triplet restriction applies
            if (p != 0 && forbidden.count({p, u, v})) {
                continue;
            }

            // Relaxation
            if (dist[u][p] + w < dist[v][u]) {
                dist[v][u] = dist[u][p] + w;
                parent[v][u] = p; // To reach v from u, we came from p
                pq.push({dist[v][u], v, u});
            }
        }
    }

    // 5. Output Result
    if (final_cost == INF) {
        cout << -1 << endl;
    } else {
        cout << final_cost << endl;

        // Path Reconstruction
        vector<int> path;
        int curr = n;
        int prev = end_prev;

        while (curr != 0) {
            path.push_back(curr);
            int temp = parent[curr][prev];
            curr = prev;
            prev = temp;
        }
        
        reverse(path.begin(), path.end());
        
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}