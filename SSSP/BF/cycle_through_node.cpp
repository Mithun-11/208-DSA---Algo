void solve(int target_node, int n, int m, vector<Edge>& edges)
{
    vector<ll> dist(n + 1, INF);
    vector<int> par(n + 1, -1);

    dist[target_node] = 0;
    int endpoint = -1;

    // Run up to N iterations (cycle length limit)
    for(int i = 0; i < n; i++)
    {
        for(auto [u, v, w] : edges)
        {
            if(dist[u] == INF) continue;

            // Standard Relaxation
            if(dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                par[v] = u;

                // SPECIAL CHECK: Did we just relax the target node?
                if(v == target_node) 
                {
                    endpoint = target_node;
                    goto FOUND; // Break out of all loops immediately
                }
            }
        }
    }

    FOUND:
    if(endpoint == -1)
    {
        cout << "No negative cycle passing through " << target_node << endl;
    }
    else
    {
        cout << "Negative cycle found: ";
        vector<int> path;
        int curr = endpoint;
        
        // Reconstruct path backwards until we loop back to start
        while(true)
        {
            path.push_back(curr);
            curr = par[curr];
            if(curr == endpoint && path.size() > 1) break;
        }
        path.push_back(endpoint); // Close the loop
        
        reverse(path.begin(), path.end());
        for(auto node : path) cout << node << " ";
        cout << endl;
    }
}