#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pli = pair<ll, int>;

void solve()
{
    int n, m, k; 
    cin >> n >> m >> k;
    
    // Using vector<pair> is slightly faster than vector<vector<pair>>
    vector<vector<pli>> g(n + 1);
    for(int i = 0; i < m; i++)
    {
        int u, v, w; 
        cin >> u >> v >> w;
        g[u].push_back({w, v});
    }

    // Optimization: Track the 'K' best distances to every node.
    // We use a Max-Priority Queue so we can easily access (and remove) the largest cost.
    vector<priority_queue<ll>> best(n + 1);

    // Main Min-Priority Queue for Dijkstra
    priority_queue<pli, vector<pli>, greater<pli>> q;

    // Initial State
    q.push({0, 1});
    best[1].push(0);

    while(!q.empty())
    {
        auto [d, u] = q.top();
        q.pop();

        // Pruning Check:
        // If 'd' is greater than the worst of our top K paths, 
        // then this specific queue entry is "stale" and useless.
        if (d > best[u].top()) continue; 
        // Note: For typical inputs, the size check logic below handles most pruning,
        // but this check handles "stale" entries effectively.

        if (u == n && best[n].size() == k && d == best[n].top()) {
             // If we are at the destination and this is the K-th best, 
             // we might technically be done, but usually we just let the queue empty naturally
             // or print answers here.
        }

        for(auto [w, v] : g[u])
        {
            ll new_cost = d + w;

            // CRITICAL OPTIMIZATION:
            if (best[v].size() < k) {
                // If we haven't found K paths to 'v' yet, take this one.
                best[v].push(new_cost);
                q.push({new_cost, v});
            }
            else if (new_cost < best[v].top()) {
                // If we found a path better than the WORST of the current K paths:
                // 1. Remove the worst one (it's no longer top K).
                best[v].pop();
                // 2. Add the new better one.
                best[v].push(new_cost);
                // 3. Process it.
                q.push({new_cost, v});
            }
            // Else: The new path is worse than the K paths we already know. IGNORE IT.
        }
    }

    // Output: The 'best[n]' max-heap contains the answer, 
    // but in REVERSE order (Largest -> Smallest).
    // We need to extract them and print in correct order.
    vector<ll> ans;
    while(!best[n].empty()){
        ans.push_back(best[n].top());
        best[n].pop();
    }
    reverse(ans.begin(), ans.end());
    
    for(auto x : ans) cout << x << " ";
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
}