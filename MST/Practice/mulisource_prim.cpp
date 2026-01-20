// https://www.codechef.com/problems/CHEFELEC?tab=statement

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj; // weight,v
using tii=tuple<int,int>; // weight,vertex(v);
string s;
#define endl '\n'

void prim(int n)
{
    priority_queue<tii,vector<tii>,greater<tii>>pq;
    vector<bool>vis(n,false);

    for(int i=0;i<n;i++)
    {
        if(s[i]=='1')
            pq.push({0,i});
    }
    ll cost=0;

    while(!pq.empty())
    {
        auto[w,u]=pq.top();
        pq.pop();
        if(vis[u]) continue;
        vis[u]=true;
        cost+=w;

        for(auto[w_v,v]:adj[u])
        {
            if(!vis[v]) pq.push({w_v,v});
        }
    }

    cout<<cost<<endl;


}

void solve()
{
    int n; cin>>n;
    cin>>s;
    adj.clear();
    adj.resize(n);
    vector<int>dist(n);
    for(int i=0;i<n;i++)
    {
        cin>>dist[i];
    }

    for(int i=0;i<n-1;i++)
    {
        int d= abs(dist[i]-dist[i+1]);
        adj[i].push_back({d,i+1});
        adj[i+1].push_back({d,i});
    }

    prim(n);
    
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int t=1;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        solve();
    }

}

//g++ -o program filename.cpp && ./program

// g++ -O2 -o program filename.cpp && ./program < input.txt > output.txt