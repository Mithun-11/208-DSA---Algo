#include<bits/stdc++.h>
using namespace std;
#define endl '\n'


vector<int> parent;
vector<int> sze;
void make_set(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    sze.assign(n, 1);
}
int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sze[a] < sze[b]) swap(a, b);
        parent[b] = a;
        sze[a] += sze[b];
    }
}


struct Edge {
    int u, v, w, id;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

void solve() {
    int n, m; 
    cin >> n >> m;
    vector<Edge> edges(m);
    for(int i = 0; i < m; i++) {
        int u, v, w; 
        cin >> u >> v >> w;
        edges[i] = {u-1, v-1, w, i};
    }
    
    make_set(n);
    sort(edges.begin(), edges.end());
    vector<bool> results(m,false);
    
    // Group edges by weight
    map<int, vector<Edge>> batches;
    for(auto& e : edges) {
        batches[e.w].push_back(e);
    }
    
    // Process each batch
    for(auto& [weight, batch] : batches) {
        // Check phase
        for(auto& [u, v, w, id] : batch) {
            if(find_set(u)!=find_set(v)) results[id]=true;
        }
        // Union phase
        for(auto& [u, v, w, id] : batch) {
            union_sets(u, v);
        }
    }
    
    for(int i=0;i<m;i++) 
    {
        if(results[i]) cout<<"YES";
        else cout<<"NO";
        cout<<endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
}