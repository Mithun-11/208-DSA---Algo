#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj;
using tiii=tuple<int,int,int>; // weight,u,v

vector<int> parent;
vector<int>sze;
int comp_count;
int max_size=0;
#define endl '\n'

void make_set(int v) {
    parent[v] = v;
    sze[v] = 1;
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
        if(sze[a]>max_size) max_size=sze[a];
    }
}


void solve() // 0 based indexing for vertices
{
    
    int n,m; cin>>n>>m;
    parent.resize(n);
    sze.resize(n);
    comp_count=n;
    for(int i=0;i<n;i++) make_set(i);
    for(int i=0;i<m;i++)
    {
        int u,v; cin>>u>>v;
        u--,v--;
        if(find_set(u)!=find_set(v))
        {
            comp_count--;
            union_sets(u,v);
        }
        cout<<comp_count<<" "<<max_size<<endl;
    }


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