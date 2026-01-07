#include<bits/stdc++.h>
using namespace std;
using ll= long long;
const long long INF=1e18;
int n,m;


struct city
{
    ll cost;
    int pos;
    bool used;

    bool operator>(const city& other) const{
        return cost>other.cost;
    }
    
};

pair<ll,ll> dijkstra(int source,int dest,vector<vector<pair<int,int>>>&adj) // 1st one without coupon,2nd one with coupon
{
    vector<vector<ll>>min_cost(n+1,{INF,INF});
    min_cost[source][0]=0;
    priority_queue<city, vector<city>, greater<city>>q;
    q.push({0,source,0}); // cost,pos,used

    while(!q.empty())
    {
        city curr=q.top();
        q.pop();

        if(curr.cost!=min_cost[curr.pos][curr.used])  continue;

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

    return{min_cost[dest][0],min_cost[dest][1]};
}


void solve()
{
    cin>>n>>m;
    vector<vector<pair<int,int>>>adj(n+1);
    for(int i=0;i<m;i++)
    {
        int u,v,w;cin>>u>>v>>w;
        adj[u].push_back({v,w}); 
          
    }
    ll x,y,w; cin>>x>>y>>w;
    auto[s_x_0,s_x_1]=dijkstra(1,x,adj);
    auto[y_f_0,y_f_1]=dijkstra(y,n,adj);

    ll ans=min({
        s_x_0+w+y_f_1,
        s_x_1+w+y_f_0,
        s_x_0+w/2+y_f_0
    });

    cout<<ans<<endl;

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