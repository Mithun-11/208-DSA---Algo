// https://lightoj.com/problem/getting-a-t-shirt

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

struct Edge{
    int u,v,cap,flow;
};

int itr=1;

vector<Edge>edges;
vector<vector<int>>adj;
vector<int>par_idx;

void add_edge(int u,int v,int c)
{
    adj[u].push_back(edges.size());
    edges.push_back({u,v,c,0}); // forward edge (real)
    adj[v].push_back(edges.size());
    edges.push_back({v,u,0,0}); // residual back edge (not real) so capacity is 0
}

ll bfs(int s,int t)
{
    fill(par_idx.begin(),par_idx.end(),-1);
    queue<pair<int,ll>>q;
    q.push({s,INF});
    par_idx[s]=-2;

    while(!q.empty())
    {
        auto[u,cur_flow]=q.front();
        q.pop();

        for(int id: adj[u])
        {
            auto[_,v,cap,flow]=edges[id];
            ll residual= cap-flow;
            if(residual>0 && par_idx[v]==-1)
            {
                par_idx[v]=id;
                ll new_flow=min(cur_flow,residual);

                if(v==t) return new_flow;

                q.push({v,new_flow});                          
            }
        }
    }

    return 0;
}

void solve()
{
    int n,m;
    cin>>n>>m;
    edges.clear();
    adj.clear();
    par_idx.clear();
    adj.resize(10+m);
    par_idx.resize(10+m);
    vector<string> sizes = {"XS", "S", "M", "L", "XL", "XXL"};
    int s,t; 
    s=m+7,t=m+8;

    for(int i=1;i<=m;i++)
    {
        string a,b; cin>>a>>b;
        int u = (find(sizes.begin(), sizes.end(), a) - sizes.begin()) + m + 1;
        int v = (find(sizes.begin(), sizes.end(), b) - sizes.begin()) + m + 1;
        add_edge(s,i,1);
        add_edge(i,u,1);
        add_edge(i,v,1);
        
    }

    for(int i=1;i<=6;i++)
    {
        add_edge(m+i,t,n);
    }
    

    ll max_flow=0;
    ll path_flow;

    while((path_flow=bfs(s,t)))
    {
        int cur=t;
        while(cur!=s)
        {
            int id=par_idx[cur];
            edges[id].flow+=path_flow;
            edges[id^1].flow-=path_flow;
            cur=edges[id].u;
        }
        max_flow+=path_flow;
    }


    string ans;
    if(max_flow==m) ans="YES";
    else ans="NO";

    cout<<"Case "<<itr<<": "<<ans<<endl;
    itr++;


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