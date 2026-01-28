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

// Helper struct for coordinates
struct Point {
    double x, y;
};

// Helper function for distance squared
double distSq(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

void solve()
{
    int M, H;
    double R;
    cin >> M >> H >> R;

    // Reset Globals
    edges.clear();
    adj.clear();
    par_idx.clear();
    
    // Nodes: Source=0, Mice=1..M, Holes=M+1..M+H, Sink=M+H+1
    int total_nodes = M + H + 5;
    adj.resize(total_nodes);
    par_idx.resize(total_nodes);

    vector<Point> mice(M);
    for(int i=0; i<M; i++) {
        cin >> mice[i].x >> mice[i].y;
    }

    struct Hole {
        double x, y;
        int cap;
    };
    vector<Hole> holes(H);
    for(int i=0; i<H; i++) {
        cin >> holes[i].x >> holes[i].y >> holes[i].cap;
    }

    int s = 0;
    int t = M + H + 1;

    // 1. Build Source -> Mice (Cap 1)
    for(int i=0; i<M; i++) {
        add_edge(s, i+1, 1);
    }

    // 2. Build Holes -> Sink (Cap = Hole Capacity)
    for(int i=0; i<H; i++) {
        // Hole nodes start after M. So Hole i is node (M + 1 + i)
        add_edge(M + 1 + i, t, holes[i].cap);
    }

    // 3. Build Mice -> Holes (Cap 1, if reachable)
    double RSq = R * R; // Compare squared distance for precision
    for(int i=0; i<M; i++) {
        for(int j=0; j<H; j++) {
            if(distSq(mice[i], {holes[j].x, holes[j].y}) <= RSq + 1e-9) { // 1e-9 for float tolerance
                add_edge(i+1, M + 1 + j, 1);
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