#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int mod=1e9+7;
const ll INF=1e18;

void solve()
{
    int n,m; cin>>n>>m;
    vector<vector<pair<ll,int>>>g(n+1);
    for(int i=0;i<m;i++)
    {
        int u,v,w; cin>>u>>v>>w;
        g[u].push_back({w,v});
    }
    vector<ll>dist(n+1,INF);
    vector<ll>num(n+1,0);
    vector<int>minN(n+1,1e9);
    vector<int>maxN(n+1,-1e9);

    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>q;
    dist[1]=0;
    num[1]=1;
    minN[1]=maxN[1]=0;
    q.push({0,1});

    while(!q.empty())
    {
        auto[cost,u]=q.top();
        q.pop();

        if(cost>dist[u]) continue;

        for(auto [vc,v]: g[u])
        {
            ll new_cost=vc+cost;
            if(new_cost==dist[v])
            {
                num[v]=(num[u]+num[v])%mod;
                minN[v]=min(minN[v],minN[u]+1);
                maxN[v]=max(maxN[v],maxN[u]+1);
            }

            else if(new_cost<dist[v])
            {
                num[v]=num[u];
                minN[v]=minN[u]+1;
                maxN[v]=maxN[u]+1;
                dist[v]=new_cost;
                q.push({new_cost,v});
            }
        }
    }

    cout<<dist[n]<<" "<<num[n]<<" "<<minN[n]<<" "<<maxN[n]<<endl;

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