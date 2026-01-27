#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

struct Edge{
    int u,v,cap,flow;
};

int iteration=1;
#define endl '\n'

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
    int n,m; // remember 0 based indexing for nodes here
    cin>>n;
    adj.clear();
    par_idx.clear();
    adj.resize(2*n+2);
    par_idx.resize(2*n+2);

    for(int i=0;i<n;i++) // adding internal edge
    {
        int node_cap=1;
        cin>>node_cap;
        add_edge(i,i+n,node_cap); 
    }
    cin>>m;

    for(int i=0;i<m;i++)
    {
        int u,v,c;
         cin>>u>>v>>c;
         u--,v--;
        add_edge(u+n,v,c);
        
    }
    int s,t; 
    s=2*n,t=2*n+1;
    int b,d; cin>>b>>d;

    for(int i=0;i<b;i++) 
    {
        int u; cin>>u;
        u--;
        add_edge(2*n,u,1e9);
    }

    for(int i=0;i<d;i++)
    {
        int u; cin>>u;
        u--;
        add_edge(u+n,2*n+1,1e9);
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

    cout<<"Case "<<iteration<<": "<<max_flow<<endl;
    iteration++;

    


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