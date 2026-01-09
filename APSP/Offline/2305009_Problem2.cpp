#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj;

void solve()
{
    int n; cin>>n;
    map<string,int>id;

    for(int i=0;i<n;i++)
    {
        string currency; cin>>currency;
        id[currency]=i;
    }

    vector<vector<double>>dist(n,vector<double>(n,0));

    for(int i=0;i<n;i++) dist[i][i]=1;

    int m; cin>>m;

    for(int i=0;i<m;i++)
    {
        string to,from; double rate;
        cin>>from>>rate>>to;

        int u=id[from];
        int v=id[to];

        dist[u][v]=max(dist[u][v],rate);
    }

    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                dist[i][j]=max(dist[i][j],dist[i][k]*dist[k][j]);
        }
    }

    bool is_possible=false;

    for(int i=0;i<n;i++)
    {
        if(dist[i][i]>1.00)
        {
            is_possible=true;
            break;
        }
    }

    if(is_possible) cout<<"Yes";
    else cout<<"No";


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

