#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

struct Edge
{
    int u,v,w; // from u to v with weight of w
};


void solve()
{
    int n,m; cin>>n>>m;
    vector<Edge>edges;
    vector<ll>dist(n+1,0);
    vector<int>par(n+1,-1);

    for(int i=0;i<m;i++)
    {
        int u,v,w; cin>>u>>v>>w;
        edges.push_back({u,v,w});
    }

    dist[1]=0;
    int x;
    for(int i=0;i<n;i++)
    {
        x=-1;
        for(auto[u,v,w] : edges)
        {
            if( dist[u]+w<dist[v])
            {
                dist[v]=dist[u]+w;
                par[v]=u;
                x=v;
            }
        }

    }

    if(x==-1)
    {
        cout<<-1;
    }

    else {
        for(int i=0;i<n;i++)
        {
            x=par[x];
        }

        vector<int>path;

        for(int cur=x; ; cur=par[cur])
        {
             if(cur==x && path.size()>1) break;
            path.push_back(cur);
           
        }

        reverse(path.begin(),path.end());

        for(auto u: path) cout<<u<<" ";
        cout<<endl;

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