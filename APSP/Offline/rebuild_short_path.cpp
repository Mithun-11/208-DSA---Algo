#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj;

void solve()
{
    ll n,m,q; cin>>n>>m>>q;

    vector<vector<ll>>mat(n+1,vector<ll>(n+1,INF));
    vector<vector<ll>>par(n+1,vector<ll>(n+1,-1));

    for(int i=1;i<=n;i++)  mat[i][i]=0;

    for(int i=0;i<m;i++)
    {
        ll u,v,w; cin>>u>>v>>w;
        // mat[u][v]=min(mat[u][v],w);
        // mat[v][u]=min(mat[v][u],w);

        if(w<mat[u][v])
        {
            mat[u][v]=w;
            par[u][v]=u;
        }

        if(w<mat[v][u])
        {
            mat[v][u]=w;
            par[v][u]=v;
        }
    }

    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
               { 
                if(mat[i][k]!=INF && mat[k][j]!=INF && mat[i][k]+mat[k][j]<mat[i][j])
                {
                    mat[i][j]=mat[i][k]+mat[k][j];
                    par[i][j]=par[k][j];
                }
                    
            }
        }
    }

    for(int i=0;i<q;i++)
    {
        ll u,v; cin>>u>>v;

        if(mat[u][v]==INF) cout<<-1;
        else cout<<mat[u][v];

        cout<<endl;
    }

    // building the path (assuming it exists) lets say from u=1 to v=n
    if(mat[1][n]==INF) cout<<"No path from 1 to n";

    else {
        ll cur=n;
        vector<ll>path;
        while(cur!=-1)
        {
            path.push_back(cur);
            cur=par[1][cur];
        }

        reverse(path.begin(),path.end());
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

