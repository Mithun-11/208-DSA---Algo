// link: https://acm.timus.ru/problem.aspx?space=1&num=1004
#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Use int for consistency with dist array
int n; 
vector<vector<pair<int,int>>> adj;
vector<int> dist;
vector<int> par;

struct Edge {
    int u, v, w;
};

// Dijkstra to find shortest path from start_node to target_node
// explicitly ignoring the direct edge between them
int dijkstra(int start_node, int target_node)
{
    dist.assign(n + 1, INF);
    par.assign(n + 1, -1);
    
    dist[start_node] = 0;
    
    // Min-heap: {cost, node}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, start_node}); // CORRECTED: {cost, node}

    while(!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if(d > dist[u]) continue;
        if(u == target_node) break; // Optimization

        // CORRECTED: Iterate adj[u] (current node), not adj[start_node]
        for(auto [w, v] : adj[u])
        {
            // Ignore the direct edge between start_node and target_node
            if((u == start_node && v == target_node) || (u == target_node && v == start_node)) continue;

            // CORRECTED: Use dist[u], not dist[start_node]
            if(dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[target_node];
}

void solve()
{
    // n is already read in main
    int m; 
    cin >> m;
    
    adj.assign(n + 1, vector<pair<int,int>>());
    vector<Edge> edges;
    
    for(int i = 0; i < m; i++)
    {
        int u, v, w; 
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
        edges.push_back({u, v, w});
    }

    int ans = INF;
    vector<int> final_path;

    for(auto [u, v, w] : edges)
    {
        int path_len = dijkstra(u, v);
        
        if(path_len != INF && path_len + w < ans)
        {
            ans = path_len + w;
            final_path.clear();
            
            // Reconstruct path: v -> ... -> u
            int curr = v;
            while(curr != -1) // CORRECTED: Loop logic
            {
                final_path.push_back(curr);
                curr = par[curr];
            }
            // Now final_path is v...u. The cycle is u-v...u.
            // But the problem wants the sequence of cities.
            // The list v...u is a valid sequence for the cycle.
        }
    }

    if(ans == INF)
    {
        cout << "No solution." << endl;
    }
    else 
    {
        // Timus output often requires the path in specific order.
        // Usually, just printing the nodes in the cycle is fine.
        for(auto a: final_path) cout<<a<<" ";
        cout<<endl;
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    // CORRECTED: Handle multiple test cases ending with -1
    while(cin >> n && n != -1)
    {
        solve();
    }
    return 0;
}