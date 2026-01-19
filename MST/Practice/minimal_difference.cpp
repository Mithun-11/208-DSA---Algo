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

    ll min_diff=INF;

    for(int i=0;i<m;i++)
    {
        make_set(n);
        ll components=n;

        for(int j=i;j<m;j++)
        {
            auto[w,u,v]=edges[j];

            if(find_set(u)!=find_set(v))
            {
                union_sets(u,v);
                components--;

                if(components==1)
                {
                    ll curr_diff= get<0>(edges[j]) - get<0>(edges[i]);
                    min_diff=min(curr_diff,min_diff);
                    break;
                }
            }
        }
    }

    if(min_diff==INF) cout<<"NO";
    else {
        cout<<"YES"<<endl;
        cout<<min_diff<<endl;
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