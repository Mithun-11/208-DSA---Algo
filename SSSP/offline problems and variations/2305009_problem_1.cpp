#include<bits/stdc++.h>
using namespace std;
using ll= long long;
const long long INF=1e18;
int n,m;
vector<vector<pair<int,int>>>adj;

struct city
{
    ll cost;
    int pos;
    bool used;

    bool operator>(const city& other) const{
        return cost>other.cost;
    }
    
};


void solve()
{
    cin>>n>>m;
    adj.resize(n+1);
    for(int i=0;i<m;i++)
    {
        int u,v,w;cin>>u>>v>>w;
        adj[u].push_back({v,w});    
    }

    vector<vector<ll>>min_cost(n+1,{INF,INF});
    min_cost[1][0]=0;
    priority_queue<city, vector<city>, greater<city>>q;
    q.push({0,1,0}); // cost,pos,used(state) 0 means not used

    while(!q.empty())
    {
        city curr=q.top();
        q.pop();

        if(curr.cost!=min_cost[curr.pos][curr.used])  continue;
        if(curr.pos==n) break;

        for (auto [v,c] : adj[curr.pos])
        {
            ll curr_cost=min_cost[curr.pos][curr.used];

            if(curr_cost+c<min_cost[v][curr.used])
            {
                min_cost[v][curr.used]=curr_cost+c;
                q.push({min_cost[v][curr.used],v,curr.used});
            }

            if(!curr.used && curr_cost+c/2<min_cost[v][1])
            {
                min_cost[v][true]=curr_cost+c/2;
                q.push({min_cost[v][1],v,1});
            }

        }
    }

    cout<<min(min_cost[n][1],min_cost[n][0]);


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