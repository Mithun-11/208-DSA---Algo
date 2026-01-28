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

struct Person {
    int height;
    int age;
    int divorced; // 1 if divorced, 0 if not
};

void solve()
{
    int m, n;
    cin >> m >> n;

    // Reset Globals
    edges.clear();
    adj.clear();
    par_idx.clear();
    
    // Nodes: 
    // Source = 0
    // Men = 1 to m
    // Women = m+1 to m+n
    // Sink = m+n+1
    int total_nodes = m + n + 5;
    adj.resize(total_nodes);
    par_idx.resize(total_nodes);

    vector<Person> men(m);
    for(int i=0; i<m; i++) {
        cin >> men[i].height >> men[i].age >> men[i].divorced;
    }

    vector<Person> women(n);
    for(int i=0; i<n; i++) {
        cin >> women[i].height >> women[i].age >> women[i].divorced;
    }

    int s = 0;
    int t = m + n + 1;

    // 1. Source -> Men
    for(int i=0; i<m; i++) {
        add_edge(s, i+1, 1);
    }

    // 2. Women -> Sink
    for(int i=0; i<n; i++) {
        add_edge(m + 1 + i, t, 1);
    }

    // 3. Men -> Women (Based on Compatibility)
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            bool height_ok = abs(men[i].height - women[j].height) <= 12;
            bool age_ok = abs(men[i].age - women[j].age) <= 5;
            bool status_ok = (men[i].divorced == women[j].divorced);

            if(height_ok && age_ok && status_ok) {
                // Connect Man i (node i+1) to Woman j (node m+1+j)
                add_edge(i+1, m + 1 + j, 1);
            }
        }
    }

    // 4. Run Max Flow
    ll max_flow = 0;
    ll path_flow;

    while((path_flow = bfs(s, t)))
    {
        int cur = t;
        while(cur != s)
        {
            int id = par_idx[cur];
            edges[id].flow += path_flow;
            edges[id^1].flow -= path_flow;
            cur = edges[id].u;
        }
        max_flow += path_flow;
    }

    cout << "Case " << itr << ": " << max_flow << endl;
    itr++;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int t = 1;
    cin >> t;
    for(int i=0; i<t; i++)
    {
        solve();
    }
}