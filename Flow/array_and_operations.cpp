#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

struct Edge{
    int u,v,cap,flow;
};

// GLOBAL VARIABLES
vector<Edge> edges;
vector<vector<int>> adj;
vector<int> par_idx;

// YOUR TEMPLATE FUNCTIONS
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
    queue<pair<int,ll>> q;
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

ll get_max_flow(int s, int t) {
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
    return max_flow;
}

// HELPER: Get prime factors of a number
// Returns a map: Prime -> Count (e.g., 12 -> {2:2, 3:1})
map<int, int> get_factors(int n) {
    map<int, int> f;
    for(int i=2; i*i<=n; i++) {
        while(n % i == 0) {
            f[i]++;
            n /= i;
        }
    }
    if(n > 1) f[n]++;
    return f;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    // Store factors for each number: factors[i][prime] = count
    vector<map<int, int>> node_factors(n + 1);
    set<int> all_primes;

    for(int i=1; i<=n; i++) {
        cin >> a[i];
        node_factors[i] = get_factors(a[i]);
        // Collect all unique primes involved in the problem
        for(auto const& [p, count] : node_factors[i]) {
            all_primes.insert(p);
        }
    }

    vector<pair<int, int>> good_pairs;
    for(int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        // CRITICAL: Always direct flow from ODD index to EVEN index
        // If u is even, swap so u is odd.
        if(u % 2 == 0) swap(u, v); 
        good_pairs.push_back({u, v});
    }

    int s = 0, t = n + 1;
    ll total_operations = 0;

    // --- MAGIC LOOP: Solve Max Flow separately for each Prime ---
    for(int p : all_primes) {
        
        // 1. Reset the Graph for this prime
        edges.clear();
        adj.assign(n + 2, vector<int>());
        par_idx.resize(n + 2);

        // 2. Build Edges based on THIS prime 'p'
        
        // Source -> Odd Indices (Capacity = exponent of p)
        // Even Indices -> Sink (Capacity = exponent of p)
        for(int i=1; i<=n; i++) {
            if(node_factors[i].count(p)) {
                int capacity = node_factors[i][p];
                if(i % 2 != 0) add_edge(s, i, capacity); // Odd connects to Source
                else add_edge(i, t, capacity);           // Even connects to Sink
            }
        }

        // Connect Good Pairs (Odd -> Even) with INFINITE capacity
        // This allows the flow (prime factors) to move between numbers
        for(auto pair : good_pairs) {
            add_edge(pair.first, pair.second, 1e9);
        }

        // 3. Add the result of this prime to total
        total_operations += get_max_flow(s, t);
    }

    cout << total_operations << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
}