// dist[node][hops][used]
// hops ranges from 0 to K+1
vector<vector<vector<ll>>> dist(n+1, vector<vector<ll>>(K + 2, vector<ll>(2, INF)));

auto [cost, u, hops, used] = pq.top(); // Struct needs 'hops'
pq.pop();

if (cost > dist[u][hops][used]) continue;

// Calculate next hop count (clamp at K+1 to avoid overflow)
int next_hops = min(hops + 1, K + 1);

for (auto [w, v] : adj[u]) {
    
    // 1. Normal Move (No Coupon)
    if (cost + w < dist[v][next_hops][used]) {
        dist[v][next_hops][used] = cost + w;
        pq.push({dist[v][next_hops][used], v, next_hops, used});
    }

    // 2. Coupon Move (Only if unused AND within first K edges)
    // Note: If we are at 'hops', this next edge is the (hops+1)-th edge.
    // So valid if (hops + 1) <= K, which simplifies to hops < K.
    if (used == 0 && hops < K && cost + w/2 < dist[v][next_hops][1]) {
        dist[v][next_hops][1] = cost + w/2;
        pq.push({dist[v][next_hops][1], v, next_hops, 1});
    }
}