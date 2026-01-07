#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, tuple<int, int, int>> pli; // {cost, {city, coupons_used, used_last}}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<vector<pair<int, ll>>> adj(n + 1);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    
    // dist[city][coupons_used][used_last]
    // used_last: 0 = didn't use coupon on last flight, 1 = used coupon on last flight
    vector<vector<vector<ll>>> dist(n + 1, vector<vector<ll>>(k + 1, vector<ll>(2, LLONG_MAX)));
    
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    
    // Start at city 1, 0 coupons used, didn't use coupon on "last" flight (no previous flight)
    dist[1][0][0] = 0;
    pq.push({0, {1, 0, 0}});
    
    while (!pq.empty()) {
        auto [cost, state] = pq.top();
        pq.pop();
        
        auto [u, coupons, used_last] = state;
        
        if (cost > dist[u][coupons][used_last]) continue;
        
        for (auto [v, w] : adj[u]) {
            // Option 1: Don't use coupon on this flight
            ll new_cost = cost + w;
            if (new_cost < dist[v][coupons][0]) {
                dist[v][coupons][0] = new_cost;
                pq.push({new_cost, {v, coupons, 0}});
            }
            
            // Option 2: Use coupon on this flight (if we have coupons left and didn't use one on last flight)
            if (coupons < k && used_last == 0) {
                ll discounted_cost = cost + w / 2;
                if (discounted_cost < dist[v][coupons + 1][1]) {
                    dist[v][coupons + 1][1] = discounted_cost;
                    pq.push({discounted_cost, {v, coupons + 1, 1}});
                }
            }
        }
    }
    
    // Find minimum cost to reach city n with any number of coupons used
    ll ans = LLONG_MAX;
    for (int i = 0; i <= k; i++) {
        ans = min(ans, dist[n][i][0]);
        ans = min(ans, dist[n][i][1]);
    }
    
    cout << ans << "\n";
    
    return 0;
}