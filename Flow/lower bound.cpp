#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

struct Edge{
    int u,v,cap,flow;
    int id; // To store original edge index
};

vector<Edge>edges;
vector<vector<int>>adj;
vector<int>par_idx;
vector<ll> balance; 
vector<int> lower_bounds; // To store L for final output

void add_edge(int u, int v, int c, int id = -1)
{
    adj[u].push_back(edges.size());
    edges.push_back({u, v, c, 0, id}); 
    adj[v].push_back(edges.size());
    edges.push_back({v, u, 0, 0, -1}); 
}

ll bfs(int s,int t)
{
    fill(par_idx.begin(),par_idx.end(),-1);
    queue<pair<int,ll>>q;
    q.push({s,INF});
    par_idx[s]=-2;

    while(!q.empty())
    {
        auto[u,cur_flow]=q.front();
        q.pop();

        for(int id: adj[u])
        {
            auto[_,v,cap,flow, _id]=edges[id]; // struct unpacking
            ll residual= cap-flow;
            if(residual>0 && par_idx[v]==-1)
            {
                par_idx[v]=id;
                ll new_flow=min(cur_flow,residual);
                if(v==t) return new_flow;
                q.push({v,new_flow});                           
            }
        }
    }
    return 0;
}

void solve()
{
    int n, m; 
    cin >> n >> m;
    
    // Nodes 1..N
    // Super Source (SS) = N+1, Super Sink (TT) = N+2
    int ss = n + 1;
    int tt = n + 2;

    edges.clear();
    adj.clear();
    par_idx.clear();
    balance.assign(n + 5, 0); 
    lower_bounds.clear();
    
    adj.resize(n + 5);
    par_idx.resize(n + 5);

    // 1. Build Graph with Capacity (High - Low)
    for(int i=0; i<m; i++) {
        int u, v, low, high;
        cin >> u >> v >> low >> high;
        
        // Add edge with "wiggle room" capacity
        add_edge(u, v, high - low, i);
        
        // Update demands
        balance[u] -= low;
        balance[v] += low;
        
        // Store 'low' to reconstruct actual flow later
        lower_bounds.push_back(low);
    }

    // 2. Connect Super Source/Sink based on Balance
    ll total_demand = 0;
    for(int i=1; i<=n; i++) {
        if(balance[i] > 0) {
            // Node needs flow -> Connect SS to Node
            add_edge(ss, i, balance[i]);
            total_demand += balance[i];
        } else if(balance[i] < 0) {
            // Node has extra flow -> Connect Node to TT
            add_edge(i, tt, -balance[i]);
        }
    }

    // 3. Run Max Flow (SS -> TT)
    ll max_flow = 0;
    ll path_flow;
    while((path_flow = bfs(ss, tt))) {
        int cur = tt;
        while(cur != ss) {
            int id = par_idx[cur];
            edges[id].flow += path_flow;
            edges[id^1].flow -= path_flow;
            cur = edges[id].u;
        }
        max_flow += path_flow;
    }

    // 4. Check Feasibility & Print
    if(max_flow != total_demand) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        // Output flow for each original edge
        // We iterate through 'edges'. The original edges are at indices 0, 2, 4...
        // We check 'id' to ensure we only print the original M edges.
        
        vector<int> result(m);
        for(auto e : edges) {
            if(e.id != -1) { // It's one of the input edges
                result[e.id] = e.flow + lower_bounds[e.id];
            }
        }
        
        for(int x : result) {
            cout << x << endl;
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
}