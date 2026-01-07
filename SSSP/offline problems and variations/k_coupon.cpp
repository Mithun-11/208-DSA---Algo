// OLD
vector<vector<ll>> dist(n+1, vector<ll>(2, INF));

// NEW (Change 2 to k+1)
vector<vector<ll>> dist(n+1, vector<ll>(k+1, INF));


// OLD
if(state == 0 && cost + w/2 < dist[v][1])
{
    dist[v][1] = cost + w/2;
    pq.push({dist[v][1], 1, v});
}

// NEW
// Check if we haven't used max coupons yet (state < k)
if(state < k && cost + w/2 < dist[v][state+1])
{
    dist[v][state+1] = cost + w/2;
    pq.push({dist[v][state+1], state+1, v});
}