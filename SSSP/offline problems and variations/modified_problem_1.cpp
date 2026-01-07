#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

void solve()
{
    ll n,m; cin>>n>>m;
    vector<vector<pair<ll,ll>>>adj(n+1); // cost,v

    for(int i=0;i<m;i++)
    {
        ll u,v,w; cin>>u>>v>>w;
        adj[u].push_back({w,v});
    }
    vector<vector<ll>>dist(n+1,vector<ll>(2,INF));
    using tlll=tuple<ll,ll,ll>; //cost,state,city
    priority_queue<tlll,vector<tlll>,greater<tlll>>pq;
    dist[1][0]=0;
    pq.push({0,0,1});

    while(!pq.empty())
    {
        auto [cost,state,city]=pq.top();
        pq.pop();

        if(cost>dist[city][state])continue;

        for(auto[w,v]:adj[city])
        {
            ll new_cost=cost+w;

            if(new_cost<dist[v][state])
            {
                dist[v][state]=new_cost;
                pq.push({dist[v][state],state,v});
            }

            if(state==0 && cost+w/2<dist[v][1])
            {
                dist[v][1]=cost+w/2;
                pq.push({dist[v][1],1,v});
            }
        }
    }

    cout<<dist[n][1];// coupon used will always be smaller than unused
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