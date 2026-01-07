#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
using pll=pair<ll,ll>;

void solve()
{
    ll n,m,k; cin>>n>>m>>k;
    vector<vector<pll>>g(n+1);
    for(int i=0;i<m;i++)
    {
        ll u,v,w; cin>>u>>v>>w;
        g[u].push_back({w,v});
        g[v].push_back({w,u});
    }

    using tlll=tuple<ll,ll,ll>; // length,type,city
    priority_queue<tlll,vector<tlll>,greater<tlll>>pq;
    pq.push({0,0,1});
    vector<ll>dist(n+1,INF);
    dist[1]=0;

    for(int i=0;i<k;i++)
    {
        ll s,m ;cin>>s>>m;
        pq.push({m,1,s});
    }

    vector<bool>vis(n+1,false);
    
    ll ans=0;

    while(!pq.empty())
    {
        auto[length,type,u]=pq.top();
        pq.pop();
        if(vis[u])
        {
            if(type==1) ans++;
            continue;
        }
        vis[u]=true;
        dist[u]=length; // jesob train er distance update hoyni jodio answer e impact felbe na


        for(auto [w,v]: g[u])
        {
          ll  new_w=w+length;
          if(new_w<dist[v])
          {
            dist[v]=new_w;
            pq.push({new_w,0,v});
          }
        }

    }

    cout<<ans<<endl;


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