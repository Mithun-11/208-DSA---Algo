#include<bits/stdc++.h>
using namespace std;

vector<int> p, sz;
vector<pair<int,int>> hist;

int find(int v) {
    return v == p[v] ? v : find(p[v]);
}

// Persist=1 for graph edges (permanent), 0 for query edges (rollback-able)
bool unite(int a, int b, bool persist = 0) {
    a = find(a), b = find(b);
    if (a == b) return 0;
    if (sz[a] < sz[b]) swap(a, b);
    
    if (!persist) {
        hist.push_back({b, p[b]});      // Save old parent
        hist.push_back({~a, sz[a]});    // Save old size (using ~ to mark size op)
    }
    
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}

void rollback(size_t ckpt) {
    while (hist.size() > ckpt) {
        auto [x, v] = hist.back();
        hist.pop_back();
        // If x >= 0, it's a parent update. If x < 0, it's a size update.
        (x >= 0 ? p[x] : sz[~x]) = v;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m, q;
    cin >> n >> m >> q;
    
    p.resize(n); sz.assign(n, 1);
    iota(p.begin(), p.end(), 0);
    
    vector<array<int,3>> e(m); // Store original edges to lookup by index
    map<int, vector<pair<int,int>>> g; // Graph Edges grouped by Weight
    
    for (auto& [u, v, w] : e) {
        cin >> u >> v >> w;
        u--, v--;
        g[w].push_back({u, v});
    }
    
    // Store query edges: qe[query_id][weight] -> list of edges
    vector<map<int, vector<pair<int,int>>>> qe(q);
    // OPTIMIZATION: Map to jump directly to active queries for a weight
    map<int, vector<int>> active_queries; 
    
    for (int i = 0; i < q; i++) {
        int k; cin >> k;
        while (k--) {
            int idx; cin >> idx;
            auto [u, v, w] = e[--idx];
            qe[i][w].push_back({u, v});
            // Mark query 'i' as active for weight 'w'
            // We use the map property that inserting same key twice doesn't duplicate
            if (qe[i][w].size() == 1) { 
                active_queries[w].push_back(i);
            }
        }
    }
    
    vector<bool> ans(q, 1);
    
    // Combine all relevant weights (from graph and queries)
    set<int> wts;
    for (auto& [w, _] : g) wts.insert(w);
    for (auto& [w, _] : active_queries) wts.insert(w);
    
    for (int w : wts) {
        // 1. CHECK PHASE: Only iterate queries that actually have edges at this weight
        if (active_queries.count(w)) {
            for (int i : active_queries[w]) {
                if (!ans[i]) continue; // If already failed, skip
                
                size_t ckpt = hist.size();
                for (auto [u, v] : qe[i][w]) {
                    if (find(u) == find(v)) {
                        ans[i] = 0;
                        // Don't break immediately, we must finish simulating 
                        // this batch to keep DSU state consistent or just rollback now?
                        // Better to just flag and continue, rollback handles cleanup.
                    } else {
                        unite(u, v);
                    }
                }
                rollback(ckpt);
            }
        }
        
        // 2. UNION PHASE: Permanently add graph edges
        if (g.count(w)) {
            for (auto [u, v] : g[w])
                unite(u, v, 1); // persist = 1
        }
    }
    
    for (bool b : ans) cout << (b ? "YES\n" : "NO\n");
}