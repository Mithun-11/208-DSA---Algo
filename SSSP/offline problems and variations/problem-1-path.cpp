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
    vector<vector<pair<ll,ll>>>parent(n+1,vector<pair<ll,ll>>(2,{-1,-1})); // {parent_city, parent_state}
    
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
                parent[v][state]={city,state};
                pq.push({dist[v][state],state,v});
            }
            if(state==0 && cost+w/2<dist[v][1])
            {
                dist[v][1]=cost+w/2;
                parent[v][1]={city,0};
                pq.push({dist[v][1],1,v});
            }
        }
    }
    
    cout<<dist[n][1]<<"\n";
    
    // Reconstruct path
    vector<ll>path;
    ll curr_city=n, curr_state=1;
    
    while(curr_city!=-1)
    {
        path.push_back(curr_city);
        auto [prev_city,prev_state]=parent[curr_city][curr_state];
        curr_city=prev_city;
        curr_state=prev_state;
    }
    
    reverse(path.begin(),path.end());
    
    for(int i=0;i<path.size();i++)
    {
        cout<<path[i];
        if(i<path.size()-1)cout<<" ";
    }
    cout<<"\n";
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