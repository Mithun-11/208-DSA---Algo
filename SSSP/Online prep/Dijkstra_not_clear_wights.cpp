// link: https://acm.timus.ru/problem.aspx?space=1&num=1930

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e9;

struct State{
    int u; 
    int cost;
    int type;
    bool operator>(const State& other) const{
        return cost>other.cost;
    }
};

void solve()
{
    int n,m ; cin>>n>>m;
    vector<vector<pair<int,int>>>adj(n+1);
    for(int i=0;i<m;i++)
    {
        int u, v; cin>>u>>v;
        adj[u].push_back({v,0}) ; // uphill mode
        adj[v].push_back({u,1}); // downhill mode. 

    }

    int start, end; cin>>start>>end;
    vector<vector<int>>d(n+1,vector<int>(2,INF));

    priority_queue<State, vector<State>,greater<State>>pq;
    d[start][0]=0;
    d[start][1]=0;
    pq.push({start,0,0});
    pq.push({start,0,1});

    while(!pq.empty())
    {
        auto[u,cost,type]=pq.top();
        pq.pop();
        if(cost>d[u][type])continue;

        for(auto [v,t]: adj[u])
        {
            int next;
            if(type==t) next=0;
            else next=1;

            if(d[u][type]+next<d[v][t])
            {
                d[v][t]=d[u][type]+next;
                pq.push({v,d[v][t],t});
            }
        }
    }

    int ans= min(d[end][0],d[end][1]);

    cout<<ans;


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