#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj;

void solve()
{
    int n; cin>>n;
    map<string,int>id;
    vector<string>names(n);

    for(int i=0;i<n;i++)
    {
        string currency; cin>>currency;
        id[currency]=i;
        names[i]=currency;
    }

    vector<vector<double>>dist(n,vector<double>(n,0));
    vector<vector<int>>par(n,vector<int>(n,-1));

    for(int i=0;i<n;i++)
    {
         dist[i][i]=1;
         par[i][i]=i;
    }

    int m; cin>>m;

    for(int i=0;i<m;i++)
    {
        string to,from; double rate;
        cin>>from>>rate>>to;

        int u=id[from];
        int v=id[to];

        // dist[u][v]=max(dist[u][v],rate);
        if(dist[u][v]<rate)
        {
            dist[u][v]=rate;
            par[u][v]=u;
        }
    }

    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                // dist[i][j]=max(dist[i][j],dist[i][k]*dist[k][j]);
                if(dist[i][k]*dist[k][j]>dist[i][j])
                {
                    dist[i][j]=dist[i][k]*dist[k][j];
                    par[i][j]=par[k][j];
                }
        }
    }

    bool is_possible=false;
    int best_node=-1;
    double max_arb=1.00;

    for(int i=0;i<n;i++)
    {
        if(dist[i][i]>max_arb)
        {
            best_node=i;
            is_possible=true;
        }
    }



    if(is_possible) 
    {
        cout<<"Yes"<<endl;
        int curr=best_node;
        vector<string>path;
        int safety = 0;
        
        while(true) {
            path.push_back(names[curr]);
            curr = par[best_node][curr];
            
            // If we returned to start or hit a dead end
            if (curr == best_node || curr == -1 || safety > n + 2) break;
            safety++;
        }
        
        // Add the start node to close the loop visually
        path.push_back(names[best_node]);

        reverse(path.begin(),path.end());
        for(auto p:path)
            cout<<p<<" ";

        cout<<endl;


    }
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

