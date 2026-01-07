#include<bits/stdc++.h>
using namespace std;
#define nl '\n'
#define fr(i,a,b) for(long long i=a; i<(b); i++)
#define vi vector<int>
#define vll vector<long long>
#define vvll vector<vector<long long>>
#define vb vector<bool>
#define F first
#define S second
#define pb push_back
#define all(v) v.begin(),v.end()
using ll = long long ;
const int mod=1e9+7;
const long long INF=1e18+5;
template<class T> bool self_min(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool self_max(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
//---- Debugger ---- //
#define debarr(a,n) cout<<#a<<" : ";for(int i=0;i<n;i++) cerr<<a[i]<<" "; cerr<<endl;
#define debmat(mat,row,col) cout<<#mat<<" :\n";for(int i=0;i<row;i++) {for(int j=0;j<col;j++) cerr<<mat[i][j]<<" ";cerr<<endl;}
#define pr(...) dbs(#__VA_ARGS__, __VA_ARGS__)
template <class S, class T>ostream& operator <<(ostream& os, const pair<S, T>& p) {return os << "(" << p.first << ", " << p.second << ")";}
template <class T>ostream& operator <<(ostream& os, const vector<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const unordered_set<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const unordered_map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const set<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const multiset<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T> void dbs(string str, T t) {cerr << str << " : " << t << "\n";}
template <class T, class... S> void dbs(string str, T t, S... s) {int idx = str.find(','); cerr << str.substr(0, idx) << " : " << t << ","; dbs(str.substr(idx + 1), s...);}
template <class T> void prc(T a, T b) {cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}
ll binpow(ll b,ll p,ll mod){ll ans=1;b%=mod;for(;p;p>>=1){if(p&1)ans=ans*b%mod;b=b*b%mod;}return ans;}
long long sroot(long long a) {long long x = sqrt(a) + 2;while (x * x > a) x--;return x;}
template<typename T> void get_vector(T&a){for(auto&e:a)cin>>e;}
//----------------- //
int n,m; // number of vertices
vector<vector<int>> adj; // adjacency list of graph
vector<int> visited;
vector<int> ans;
bool has_cycle=false;

void dfs(int v) {
    visited[v] = 1;
    for (int u : adj[v]) {
        if(visited[u]==1)
        {
            has_cycle=true;
            return;
        }
       else if (!visited[u]) {
            dfs(u);
        }

    }
    visited[v]=2;
    ans.push_back(v);
}

void solve()
{
    cin>>n>>m;
    adj.resize(n+1);
    visited.assign(n+1, 0);
    ans.clear();
    for(int i=0;i<m;i++)
    {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
        if(has_cycle) 
        {
            cout<<-1;
            return;
        }
    }
    reverse(ans.begin(), ans.end());
    for(auto a: ans) cout<<a<<" ";
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