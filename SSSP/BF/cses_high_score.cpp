#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

struct Edge
{
    int u,v,w; // from u to v with weight of w
};

vector<vector<int>>rGraph;
vector<bool>vis;

void dfs(int u)
{
    vis[u]=true;
    for(auto v: rGraph[u])
    {
        if(!vis[v]) dfs(v);
    }
}


void solve()
{
    int n,m; cin>>n>>m;
    vector<Edge>edges;
    vector<ll>dist(n+1,INF);
    rGraph.resize(n+1);
    vis.resize(n+1,false);

    for(int i=0;i<m;i++)
    {
        int u,v,w; cin>>u>>v>>w;
        edges.push_back({u,v,-w});
        rGraph[v].push_back(u);
    }
    dfs(n);// perform dfs on reverse graph taking n as source node to find the nodes from which we can reach n

    dist[1]=0;
    int x;
    for(int i=0;i<n;i++)
    {
        x=-1;
        for(auto[u,v,w] : edges)
        {
            if(dist[u]!=INF && dist[u]+w<dist[v])
            {
                dist[v]=dist[u]+w;
                x=v;
                if(i==n-1 && vis[v]) // there is a negative cycle and you can reach n through that cycle
                {
                    cout<<-1; 
                    return;
                }
            }
        }
        if(x==-1) break;

    }

    cout<<-dist[n];
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