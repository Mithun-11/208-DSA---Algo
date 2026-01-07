#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

void solve()
{
    int n,m; cin>>n>>m;
    vector<vector<pair<int,int>>>g(n+1);
    vector<ll>dist(n+1,INF);
    vector<int>par(n+1,-1);
    for(int i=0;i<m;i++)
    {
        int u,v,w; cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>q;
    dist[1]=0;
    q.push({0,1});

    while(!q.empty())
    {
        auto [cost,u]=q.top();
        q.pop();
        if(cost>dist[u]) continue;

        for(auto [v,vc]: g[u])
        {
            if(vc+cost<dist[v])
            {
                dist[v]=vc+cost;
                q.push({dist[v],v});
                par[v]=u;
            }
        }
    }

    if(par[n]==-1) cout<<-1;
    else {
        vector<int>ans;
        int cur=n;
        while(cur!=-1)
        {
            ans.push_back(cur);
            cur=par[cur];
        }

        reverse(ans.begin(),ans.end());
        for(auto v: ans) cout<<v<<" ";
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