#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj; // weight,v
using tiii=tuple<int,int,int>; // weight,parent(u),vertex(v);

void prim(int root,int n)
{
    priority_queue<tiii,vector<tiii>,greater<tiii>>pq;
    pq.push({0,-1,root});
    vector<bool>visited(n,false);
    ll cost=0;

    vector<pair<int,int>>mst;
    while(!pq.empty())
    {
        auto [w,parent,u]=pq.top();
        pq.pop();

        if(visited[u]) continue;
        visited[u]=true;
        cost+=w;
        if(parent!=-1)
        {
            mst.push_back({parent,u});
        }

        for(auto [w_v,v]:adj[u])
        {
            if(!visited[v])
            {
                pq.push({w_v,u,v});
            }
        }
    }

    cout<<"Total weight "<<cost<<endl;
    cout<<"Root node "<<root<<endl;
    for(auto [u,v]: mst) cout<<u<<" "<<v<<endl;

}

void solve()
{
    int n,m; cin>>n>>m;
    adj.resize(n);
    for(int i=0;i<m;i++)
    {
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({w,v});
        adj[v].push_back({w,u});

    }

    int root; 
    cin>>root;
    prim(root,n);
    
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