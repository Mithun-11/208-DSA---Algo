#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const ll INF = 1e18;

struct Edges
{
    int to;
    int cost;
    int time;
};

ll k, n, x;
vector<vector<Edges>> graph;
vector<ll> total_time;
vector<ll> total_cost;
vector<int> parent;

void dijkstra(int s)
{
    total_cost[s] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> q;
    q.push({0, s});

    while (!q.empty())
    {
        ll u = q.top().second;
        ll du = q.top().first;
        q.pop();
        if (du > total_cost[u])
            continue;

        for (auto e : graph[u])
        {
            int v = e.to;
            int new_time = total_time[u] + e.time;
            if (u != s)
                new_time += 1;

            ll new_cost = total_cost[u] + e.cost + k * e.time;
            if (u != s)
                new_cost += k;

            if(new_cost<total_cost[v])
            {
                total_cost[v]=new_cost;
                total_time[v]=new_time;
                parent[v]=u;
                q.push({new_cost, v});
            }
        }
    }
}

void solve()
{
    cin >> k >> n >> x;
    graph.resize(n + 1);
    total_time.resize(n + 1, 0);
    total_cost.resize(n + 1, INF);
    parent.resize(n + 1, -1);

    for (int i = 0; i < x; i++)
    {
        int u, v, t, c;
        cin >> u >> v >> t >> c;
        graph[u].push_back({v, c, t});
        graph[v].push_back({u, c, t});
    }

    int s, d;
    cin >> s >> d;

    dijkstra(s);

    if(total_cost[d]==INF)
    {
        cout<<"Error"<<endl;
        return;
    }

    vector<int>path;
    int curr=d;
    while(curr!=-1)
    {
        path.push_back(curr);
        curr=parent[curr];
    }

    reverse(path.begin(),path.end());

    for(auto a: path) cout<<a<<"->";
    cout<<" "<<total_time[d]<<" "<<total_cost[d]<<endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin>>t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }
}