#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

void solve()
{
    ll n; cin>>n;
    vector<vector<ll>> adj(n+1,vector<ll>(n+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>adj[i][j];
        }
    }

    vector<bool>active(n+1,false);
    vector<ll>res;
    vector<ll>x(n); 
    for(int i=0;i<n;i++) cin>>x[i];

    reverse(x.begin(),x.end());

    for(int s=0;s<n;s++)
    {
        int k=x[s];
        active[k]=true;

        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
            }
        }

        ll ans=0;
        for(int i=1;i<=n;i++)
        {
            if(!active[i])continue;
            for(int j=1;j<=n;j++)
            {
                if(!active[j])continue;
                ans+=adj[i][j];
            }
        }

        res.push_back(ans);
    }

    reverse(res.begin(),res.end());

    for(auto a: res) cout<<a<<" ";
    
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