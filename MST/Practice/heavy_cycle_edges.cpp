#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
vector<vector<pair<int, int>>> adj;
using tiii = tuple<int, int, int>; // weight,u,v
#define endl '\n'

vector<int> parent;
vector<int> sze;

void make_set(int n)
{
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    sze.assign(n, 1);
}

int find_set(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        if (sze[a] < sze[b])
            swap(a, b);
        parent[b] = a;
        sze[a] += sze[b];
    }
}

void solve() // 0 based indexing for vertices
{
    ll n, m;
    
    while (true)
    {
        cin >> n >> m;
        if(n==0 and m==0) break;
        vector<tiii> edges;

        for (int i = 0; i < m; i++)
        {
            ll u, v, w;
            cin >> u >> v >> w;
            edges.push_back({w, u, v});
        }

        sort(edges.begin(), edges.end());

        make_set(n);
        bool has_cycle = false;
        bool first_output = true;

        for (int i = 0; i < m; i++)
        {
            auto [w, u, v] = edges[i];
            if (find_set(u) != find_set(v))
            {
                union_sets(u, v);
            }

            else
            {
                has_cycle = true;
                if (!first_output) cout << " "; 
                cout << w;
                first_output = false;
            }
        }
        if (!has_cycle)
            cout << "forest";
        cout << endl;
    }
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