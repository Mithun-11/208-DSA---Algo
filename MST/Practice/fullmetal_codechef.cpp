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
    vector<string>grid(n);
    for(int i=0;i<n;i++) cin>>grid[i];

    vector<tiii>edges;

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            int max_diff=-5;
            for(int k=0;k<m;k++) max_diff=max(max_diff,abs(grid[i][k]-grid[j][k]));

            edges.push_back({max_diff,i,j});
        }
    }

    sort(edges.begin(),edges.end());

    ll ans=0;
    make_set(n);

    for(auto[w,u,v]:edges)
    {
        if(find_set(u)!=find_set(v))
        {
            union_sets(u,v);
            ans=max(ans,ll(w)); // ans=w is fine as the list is sorted
        }
    }

    cout<<ans;
    


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

//g++ -o program filename.cpp && ./program

// g++ -O2 -o program filename.cpp && ./program < input.txt > output.txt