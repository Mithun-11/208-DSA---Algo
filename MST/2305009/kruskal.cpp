#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj;
using tiii=tuple<int,int,int>; // weight,u,v

vector<int> parent;
vector<int>rnk;

void make_set(int v) {
    parent[v] = v;
    rnk[v] = 0;
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
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}


void solve() // 0 based indexing for vertices
{
    int n,m; cin>>n>>m;
    parent.resize(n);
    rnk.resize(n);
    vector<tiii>edges;

    for(int i=0;i<m;i++)
    {
        int u,v,w; cin>>u>>v>>w;
        edges.push_back({w,u,v});
    }
    int root;
    cin>>root; //ignore for kruskal

    ll cost=0;
    vector<pair<int,int>>mst; //u,v

    for(int i=0;i<n;i++)
    {
        make_set(i);
    }

    sort(edges.begin(),edges.end());

    for(auto[w,u,v]: edges)
    {
        if(find_set(u)!=find_set(v))
        {
            cost+=w;
            mst.push_back({u,v});
            union_sets(u,v);
        }
    }

    cout<<"Total weight "<<cost<<endl;
    for(auto [u,v]: mst) cout<<u<<" "<<v<<endl;


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