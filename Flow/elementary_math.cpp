//https://open.kattis.com/problems/elementarymath



#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

struct Edge{
    int u,v,cap,flow;
};

vector<Edge>edges;
vector<vector<int>>adj;
vector<int>par_idx;

void add_edge(int u,int v,int c)
{
    adj[u].push_back(edges.size());
    edges.push_back({u,v,c,0}); 
    adj[v].push_back(edges.size());
    edges.push_back({v,u,0,0}); 
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

struct InputPair {
    ll a, b;
};

void solve()
{
    int n;
    if(!(cin >> n)) return;

    // Reset Globals
    edges.clear();
    adj.clear();
    par_idx.clear();
    
    vector<InputPair> inputs(n);
    // Map actual large values to small IDs (0, 1, 2...)
    map<ll, int> val_to_id;
    // Map IDs back to actual values (for printing)
    map<int, ll> id_to_val;
    
    int val_counter = 0;

    // 1. Read Input and Collect All Potential Values
    for(int i=0; i<n; i++) {
        cin >> inputs[i].a >> inputs[i].b;
        
        ll options[3] = {
            inputs[i].a + inputs[i].b,
            inputs[i].a - inputs[i].b,
            inputs[i].a * inputs[i].b
        };

        for(ll val : options) {
            if(val_to_id.find(val) == val_to_id.end()) {
                val_to_id[val] = val_counter;
                id_to_val[val_counter] = val;
                val_counter++;
            }
        }
    }

    // Nodes Construction:
    // Source = 0
    // Pairs = 1 to n
    // Values = n + 1 to n + val_counter
    // Sink = n + val_counter + 1
    
    int s = 0;
    int t = n + val_counter + 1;
    int total_nodes = t + 5;
    
    adj.resize(total_nodes);
    par_idx.resize(total_nodes);

    // 2. Build Graph
    
    // Source -> Pairs
    for(int i=0; i<n; i++) {
        add_edge(s, i+1, 1);
    }

    // Pairs -> Values
    for(int i=0; i<n; i++) {
        ll a = inputs[i].a;
        ll b = inputs[i].b;
        ll options[3] = {a + b, a - b, a * b};
        
        for(ll val : options) {
            int v_id = val_to_id[val];
            // Connect Pair (i+1) to Value Node (n + 1 + v_id)
            add_edge(i+1, n + 1 + v_id, 1);
        }
    }

    // Values -> Sink
    for(int i=0; i<val_counter; i++) {
        add_edge(n + 1 + i, t, 1);
    }

    // 3. Run Max Flow
    ll max_flow = 0;
    ll path_flow;
    while((path_flow = bfs(s, t))) {
        int cur = t;
        while(cur != s) {
            int id = par_idx[cur];
            edges[id].flow += path_flow;
            edges[id^1].flow -= path_flow;
            cur = edges[id].u;
        }
        max_flow += path_flow;
    }

    // 4. Output Logic
    if(max_flow < n) {
        cout << "impossible" << endl;
    } else {
        // Reconstruct solution
        // Iterate over Pair nodes (1 to n)
        for(int i=1; i<=n; i++) {
            ll a = inputs[i-1].a;
            ll b = inputs[i-1].b;
            
            // Check outgoing edges to find the one with flow == 1
            for(int id : adj[i]) {
                if(edges[id].flow == 1 && edges[id].v != s) {
                    // This is the chosen assignment
                    // Convert Node ID back to Value ID, then to Actual Value
                    int val_node_idx = edges[id].v;
                    int val_id = val_node_idx - (n + 1);
                    ll result = id_to_val[val_id];
                    
                    // Determine which operation produced this result
                    if(a + b == result) {
                        cout << a << " + " << b << " = " << result << endl;
                    } else if(a - b == result) {
                        cout << a << " - " << b << " = " << result << endl;
                    } else {
                        cout << a << " * " << b << " = " << result << endl;
                    }
                    break; // Move to next pair
                }
            }
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
}