#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj;
 // 0 based indexing
void solve()
{
    ll n,m,q; cin>>n>>m;

    vector<vector<ll>>mat(n+1,vector<ll>(n+1,INF));

    for(int i=0;i<=n;i++)  mat[i][i]=0;

    for(int i=0;i<m;i++)
    {
        ll u,v,w; cin>>u>>v>>w;
        mat[u][v]=min(mat[u][v],w);
        // mat[v][u]=min(mat[v][u],w);
    }

    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
               { 
                if(mat[i][k]!=INF && mat[k][j]!=INF)
                    mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
            }
        }
    }

    ll y,z; cin>>y>>z>>q;

    for(int i=0;i<q;i++)
    {
        ll u,v; cin>>u>>v;

        ll ans= min(mat[u][y]+mat[y][v],mat[u][z]+mat[z][v]);
        if(ans>=INF) cout<<-1;
        else cout<<ans;

        cout<<endl;
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

