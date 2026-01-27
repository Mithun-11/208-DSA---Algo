#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

struct Edge{
    int u,v,cap,flow;
};

vector<Edge>edges;
vector<vector<int>>adj;
vector<int>par_idx;

void add_edge(int u,int v,int c)
{
    adj[u].push_back(edges.size());
    edges.push_back({u,v,c,0}); // forward edge (real)
    adj[v].push_back(edges.size());
    edges.push_back({v,u,0,0}); // residual back edge (not real) so capacity is 0
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
            auto[_,v,cap,flow]=edges[id];
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
    int n,m; // remember 0 based indexing for nodes here
    cin>>n>>m;
    adj.resize(2*n);
    par_idx.resize(2*n);

    for(int i=0;i<n;i++) // adding internal edge
    {
        int node_cap=1;
        if(i==0 || i== n-1) node_cap=1e9;
        add_edge(i,i+n,node_cap); 
    }

    for(int i=0;i<m;i++)
    {
        int u,v;
         cin>>u>>v;
         u--,v--;
        add_edge(u+n,v,1);
        
    }
    int s,t; 
    s=0,t=2*n-1;

    ll max_flow=0;
    ll path_flow;

    while((path_flow=bfs(s,t)))
    {
        int cur=t;
        while(cur!=s)
        {
            int id=par_idx[cur];
            edges[id].flow+=path_flow;
            edges[id^1].flow-=path_flow;
            cur=edges[id].u;
        }
        max_flow+=path_flow;
    }

    cout<<max_flow<<endl;

    // Path Reconstruction Logic
    for(int i = 0; i < max_flow; i++) {
        vector<int> path;
        path.push_back(1); // Start at Source (1-based)
        
        // Start searching from Source Output (0 + n)
        // We look for edges going to other nodes' Inputs
        int cur = n; 
        
        while(cur != 2 * n - 1) { // Until we reach Sink Output
            for(int id : adj[cur]) {
                Edge &e = edges[id];
                
                // We only care about EXTERNAL edges (u_out -> v_in)
                // In split graph: u_out is >= n, v_in is < n
                // So we look for neighbors < n
                if(e.flow == 1 && e.v < n) { 
                    e.flow = 0; // "Burn" this edge so next loop doesn't use it
                    
                    path.push_back(e.v + 1); // Add real node (1-based)
                    
                    // Jump to the output of the next node
                    // Current is v_in, we need to continue from v_out
                    cur = e.v + n; 
                    break;
                }
            }
        }
        
        // Print the path
        for(int j = 0; j < path.size(); j++) {
            cout << path[j] << (j == path.size() - 1 ? "" : " ");
        }
        cout << endl;
    }


}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int t=1;
    //cin>>t;
    for(int i=0;i<t;i++)
    {
        solve();
    }

}

//g++ -o program filename.cpp && ./program

// g++ -O2 -o program filename.cpp && ./program < input.txt > output.txt