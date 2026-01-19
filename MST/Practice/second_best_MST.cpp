#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj;
using tiii=tuple<int,int,int>; // weight,u,v
#define endl '\n'

vector<int> parent;
vector<int>sze; 

void make_set(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    sze.assign(n, 1);
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}


void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sze[a] < sze[b])
            swap(a, b);
        parent[b] = a;
        sze[a] += sze[b];
     
    }
}


void solve() // 0 based indexing for vertices
{
    ll n,m; cin>>n>>m;
    vector<tiii>edges;

    for(int i=0;i<m;i++)
    {
        ll u,v,w; cin>>u>>v>>w;
        u--,v--;
        edges.push_back({w,u,v});
    }

    sort(edges.begin(),edges.end());

    // --- STEP 1: Find the Best MST ---
    make_set(n);
    ll mst_weight = 0;
    vector<int> mst_indices; // Store indices of edges used in the Best MST
    int edges_count = 0;

    for(int i=0; i<m; i++) {
        auto [w, u, v] = edges[i];
        if(find_set(u) != find_set(v)) {
            union_sets(u, v);
            mst_weight += w;
            mst_indices.push_back(i); // Save the index from the sorted list
            edges_count++;
        }
    }

    // Check if even the first MST is possible
    if(edges_count < n - 1) {
        cout << -1 << endl;
        return;
    }

    // --- STEP 2: Find Second Best MST ---
    // Iterate through every edge that was part of the Best MST,
    // remove it, and try to build a new MST.
    
    ll second_best_mst = INF;

    for(int skipped_index : mst_indices) {
        make_set(n); // Reset DSU for new attempt
        ll current_weight = 0;
        int current_count = 0;

        for(int i=0; i<m; i++) {
            if(i == skipped_index) continue; // CRITICAL: Skip one specific edge

            auto [w, u, v] = edges[i];
            if(find_set(u) != find_set(v)) {
                union_sets(u, v);
                current_weight += w;
                current_count++;
            }
        }

        // If we successfully formed a tree, update the minimum
        if(current_count == n - 1) {
            second_best_mst = min(second_best_mst, current_weight);
        }
    }

    if(second_best_mst == INF) cout << -1 << endl;
    else cout << second_best_mst << endl;
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