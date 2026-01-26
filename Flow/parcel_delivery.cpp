#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

struct Edge{
    int u,v,cap,flow,cost;
};

vector<Edge>edges;
vector<vector<int>>adj;
vector<int>par_idx;
vector<ll>dist;

void add_edge(int u,int v,int c,int cost)
{
    adj[u].push_back(edges.size());
    edges.push_back({u,v,c,0,cost}); // forward edge (real)
    adj[v].push_back(edges.size());
    edges.push_back({v,u,0,0,-cost}); // residual back edge (not real) so capacity is 0
}

bool spfa(int s,int t)
{
    int n=adj.size();
    fill(dist.begin(),dist.end(),INF);
    vector<bool>in_queue(n,false);
    fill(par_idx.begin(),par_idx.end(),-1);
    queue<int>q;
    q.push(s);
    dist[s]=0;
    in_queue[s]=true;

    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        in_queue[u]=false;

        for(int id: adj[u])
        {
            Edge e=edges[id];

            if(e.cap>e.flow && dist[e.v]>dist[u]+e.cost)
            {
                dist[e.v]=dist[u]+e.cost;
                par_idx[e.v]=id;

                if(!in_queue[e.v])
                {
                    q.push(e.v);
                    in_queue[e.v]=true;
                }
            }
        }
    }

    return dist[t]!=INF;
}


bool bf(int s, int t) {
    int n = adj.size();
    
    // 1. Reset Distances
    fill(dist.begin(), dist.end(), INF);
    fill(par_idx.begin(), par_idx.end(), -1);
    
    // 2. Initialize Source
    dist[s] = 0; 

    // 3. Relax edges (N-1) times
    bool any_update = false; // Optimization: Stop early if no changes
    for(int i = 0; i < n - 1; i++) {
        any_update = false;
        
        // Iterate over ALL edges in the graph
        for(int u = 0; u < n; u++) {
            
            // Optimization: Don't relax edges from unreachable nodes
            if(dist[u] == INF) continue; 

            for(int id : adj[u]) {
                Edge &e = edges[id]; // Use reference & for speed

                if(e.cap - e.flow > 0 && dist[e.v] > dist[u] + e.cost) {
                    dist[e.v] = dist[u] + e.cost;
                    par_idx[e.v] = id;
                    any_update = true;
                }
            }
        }
        
        // If no relaxation happened in this round, we are done
        if(!any_update) break; 
    }

    return dist[t] != INF;
}




void solve()
{
    int n,m,k; // remember 0 based indexing for nodes here
    cin>>n>>m>>k;
    adj.resize(n);
    par_idx.resize(n);
    dist.resize(n);

    for(int i=0;i<m;i++)
    {
        int u,v,cap,cost;
         cin>>u>>v>>cap>>cost;
         u--,v--;
        add_edge(u,v,cap,cost);
        
    }
    int s=0,t=n-1;

    ll max_flow=0; // max_flow is the total flow
    ll path_flow=0;
    ll min_cost=0;

    while((max_flow<k && bf(s,t)))
    {
        path_flow=k-max_flow;
        int cur=t;

        while(cur!=s)
        {
            int id=par_idx[cur];
            path_flow=min(path_flow,(ll)(edges[id].cap-edges[id].flow));
            cur=edges[id].u;
        }

        cur=t;
        while(cur!=s)
        {
            int id=par_idx[cur];
            edges[id].flow+=path_flow;
            edges[id^1].flow-=path_flow;
            cur=edges[id].u;
        }
        max_flow+=path_flow;
        min_cost+=path_flow*dist[t];
    }

    if(max_flow<k)cout<<-1;
    else cout<<min_cost;

    


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