struct Node {
    ll cost;
    int u;    // current city
    int cA;   // count of Type A coupons used
    int cB;   // count of Type B coupons used
    int cC;   // count of Type C coupons used

    // Priority Queue needs this to sort by smallest cost
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

// Inside solve():
priority_queue<Node, vector<Node>, greater<Node>> pq;

// Dimensions: [City][TypeA][TypeB][TypeC]
// Initialize all with INF
ll dist[n+1][k1+1][k2+1][k3+1]; 
memset(dist, 0x3f, sizeof(dist)); // or loop to fill with INF

// Pop the top element
Node curr = pq.top(); pq.pop();
ll cost = curr.cost;
int u = curr.u;
int a = curr.cA, b = curr.cB, c = curr.cC;

// Check stale state
if (cost > dist[u][a][b][c]) continue;

for (auto [w, v] : adj[u]) {
    
    // 1. Normal Path (No Coupon)
    if (cost + w < dist[v][a][b][c]) {
        dist[v][a][b][c] = cost + w;
        pq.push({dist[v][a][b][c], v, a, b, c});
    }

    [cite_start]// 2. Use Type A (Half Price) [cite: 86]
    if (a < k1 && cost + w/2 < dist[v][a+1][b][c]) {
        dist[v][a+1][b][c] = cost + w/2;
        pq.push({dist[v][a+1][b][c], v, a+1, b, c});
    }

    [cite_start]// 3. Use Type B (Minus D) [cite: 87]
    ll costB = max(0LL, w - D); // Ensure non-negative for Dijkstra
    if (b < k2 && cost + costB < dist[v][a][b+1][c]) {
        dist[v][a][b+1][c] = cost + costB;
        pq.push({dist[v][a][b+1][c], v, a, b+1, c});
    }

    [cite_start]// 4. Use Type C (Third Price) [cite: 88]
    if (c < k3 && cost + w/3 < dist[v][a][b][c+1]) {
        dist[v][a][b][c+1] = cost + w/3;
        pq.push({dist[v][a][b][c+1], v, a, b, c+1});
    }
}

// answers
ll ans = INF;
for(int i = 0; i <= k1; i++) {
    for(int j = 0; j <= k2; j++) {
        for(int k = 0; k <= k3; k++) {
            ans = min(ans, dist[n][i][j][k]);
        }
    }
}
cout << ans << endl;