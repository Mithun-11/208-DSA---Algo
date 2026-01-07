#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
void solve()
{
    ll n,m,k; cin>>n>>m>>k;
    vector<vector<pair<ll,ll>>>adj(n+1); // cost,v
    for(int i=0;i<m;i++)
    {
        ll u,v,w; cin>>u>>v>>w;
        adj[u].push_back({w,v});
    }
    
    set<ll>special;
    for(int i=0;i<k;i++)
    {
        ll x; cin>>x;
        special.insert(x);
    }
    
    vector<vector<ll>>dist(n+1,vector<ll>(2,INF));
    using tlll=tuple<ll,ll,ll>; //cost,state,city
    // state: 0 = no discount available, 1 = discount available for next flight
    priority_queue<tlll,vector<tlll>,greater<tlll>>pq;
    
    // Check if node 1 is special
    if(special.count(1))
    {
        dist[1][1]=0;
        pq.push({0,1,1});
    }
    else
    {
        dist[1][0]=0;
        pq.push({0,0,1});
    }
    
    while(!pq.empty())
    {
        auto [cost,state,city]=pq.top();
        pq.pop();
        if(cost>dist[city][state])continue;
        
        for(auto[w,v]:adj[city])
        {
            if(state==0) // no discount available
            {
                ll new_cost=cost+w;
                int new_state=(special.count(v)?1:0);
                
                if(new_cost<dist[v][new_state])
                {
                    dist[v][new_state]=new_cost;
                    pq.push({dist[v][new_state],new_state,v});
                }
            }
            else // discount available (state==1)
            {
                // Option 1: Use discount on this flight
                ll new_cost=cost+w/2;
                int new_state=(special.count(v)?1:0);
                
                if(new_cost<dist[v][new_state])
                {
                    dist[v][new_state]=new_cost;
                    pq.push({dist[v][new_state],new_state,v});
                }
                
                
            }
        }
    }
    
    cout<<min(dist[n][0],dist[n][1]);
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
```

**Key changes:**

1. **Input format**: Added `k` (number of special airports) and read them into a `set<ll>special`

2. **State meaning changed**:
   - `state = 0`: No discount available for next flight
   - `state = 1`: Discount available for next flight (because we just arrived at a special airport)

3. **Initial state**: Check if node 1 is special. If yes, start with state 1 (discount available), otherwise state 0

4. **Transition logic**:
   - **From state 0** (no discount): Take the flight at full cost, arrive at destination with new_state based on whether destination is special
   - **From state 1** (discount available): 
     - Option 1: Use the discount (pay w/2)
     - Option 2: Don't use it (pay full w) - you lose the discount
   - After arriving at any city, check if it's special to determine the new state

5. **Answer**: Take minimum of `dist[n][0]` and `dist[n][1]` since we might end at node n with or without a discount available

**Input format expected:**
```
n m k
u1 v1 w1
u2 v2 w2
...
um vm wm
s1 s2 ... sk  (special airports)