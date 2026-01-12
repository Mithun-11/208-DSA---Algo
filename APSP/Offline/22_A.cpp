#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

void solve()
{
    ll n,m,k,x; cin>>n>>m>>k>>x;
    vector<vector<ll>>mat(n+1,vector<ll>(n+1,INF));
    vector<vector<ll>>par(n+1,vector<ll>(n+1,-1));
    vector<ll>cur(k);
    vector<ll>rate(k);
    for(int i=0;i<k;i++) cin>>cur[i];
    for(int i=0;i<k;i++) cin>>rate[i];

    for(int i=1;i<=n;i++)  mat[i][i]=0;

    for(int i=0;i<m;i++)
    {
        ll u,v,w; cin>>u>>v>>w;
        // Bidirectional edges
        if(w<mat[u][v])
        {
            mat[u][v]=w;
            par[u][v]=u; // Predecessor of v from u is u
        }
        if(w<mat[v][u])
        {
            mat[v][u]=w;
            par[v][u]=v; // Predecessor of u from v is v
        }
    }

    // Floyd-Warshall
    for(int K=1;K<=n;K++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            { 
                if(mat[i][K]!=INF && mat[K][j]!=INF) // Check INF to avoid overflow
                {
                    if(mat[i][j] > mat[i][K]+mat[K][j]) 
                    {
                        mat[i][j] = mat[i][K]+mat[K][j];
                        par[i][j] = par[K][j]; // Predecessor Logic: Inherit from K->j path
                    }
                }
            }
        }
    }

    ll m_city=-1, total_cost=INF, last=-1;

    // Find best city
    for(int i=1;i<=n;i++)
    {
        ll cost=0;
        bool is_possible=true;
        ll max_time=0;
        for(ll l=0;l<k;l++)
        {
            ll from=cur[l];
            ll time=mat[from][i];

            if(time==INF || time>x)
            {
                is_possible=false;
                break;
            }

            cost += time*rate[l];
            max_time = max(max_time, time);
        }

        if(is_possible && cost < total_cost)
        {
            m_city = i;
            total_cost = cost;
            last = max_time;
        }
    }

    if(m_city==-1)
    {
        cout<<"No meeting\n";
        return;
    }

    cout<<m_city<<" "<<total_cost<<" "<<last<<"\n";

    // --- MODIFIED OUTPUT SECTION ---
    for(int i=0; i<k; i++) // Iterate by index to get rate[i]
    {
        ll u = cur[i];
        ll cur_i = m_city;
        vector<ll> path;
        
        // Reconstruct path backwards from m_city to u
        while(cur_i != -1)
        {
            path.push_back(cur_i);
            if(cur_i == u) break; // Reached source
            cur_i = par[u][cur_i];
        }

        reverse(path.begin(), path.end());

        // Print formatted path
        for(int j=0; j<path.size(); j++)
        {
            cout << path[j];
            if(j < path.size() - 1) cout << " -> ";
        }
        
        // Print cost for this specific lord
        cout << " " << mat[u][m_city] * rate[i] << endl;
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t=1;
    for(int i=0;i<t;i++) solve();
}