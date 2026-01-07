#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF= 1e18;

struct Edge
{
    int a,b,weight;
};

vector<Edge>g;
vector<ll>dist;
vector<bool>block;

bool bf(int n)
{
    for(int i=1;i<=n;i++)
    {
        bool any=false;
        for(Edge e: g)
        {
            if(dist[e.a]<INF && dist[e.a]+e.weight<dist[e.b])
            {
                if(i==n) return true;
                dist[e.b]=dist[e.a]+e.weight;
                any=true;
            }
        }
        if(!any) return false;
    }

    return false;
}


void solve()
{
    int n,m,k,b,e; cin>>n>>m>>k>>b>>e;
    g.clear();
    dist.resize(n+1,INF);
    block.resize(n+1,false);

    for(int i=0;i<k;i++)
    {
        int u;cin>>u;
        dist[u]=0;
    }

    for(int i=0;i<b;i++)
    {
        int b; cin>>b;
        block[b]=true;
    }

    vector<int>posts(e);
    for(int i=0;i<e;i++)
    {
        cin>>posts[i];
    }

    for(int i=0;i<m;i++)
{
    int u,v,w; cin>>u>>v>>w;

    if(!block[u] && !block[v])
    {
        g.push_back({u,v,w}); // use push_back cause you are skipping some of the n edges 
    }
}

    bool has_cycle=bf(n);

    if(has_cycle) 
    {
        cout<<"Abyss Detected"<<endl;
        return;
    }

    for(auto u:posts)
    {
        if(dist[u]==INF) cout<<"INF"<<endl;
        else cout<<dist[u]<<endl;
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