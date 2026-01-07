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


void solve()
{
    ll n,m,k; cin>>n>>m>>k;
    vector<tuple<ll,ll,ll>>g;
    fr(i,0,m)
    {
        ll u,v,w; cin>>u>>v>>w;
        g.pb({u,v,w});
    }

    vvll od(n+1,vll(2,INF));
    od[1][0]=0;
    ll ans=INF;

    fr(i,0,k)
    {
        vvll nd(n+1,vll(2,INF));
        for(auto[u,v,w]:g)
        {
            if(od[u][0]!=INF)
            {
                nd[v][0]=min(nd[v][0],od[u][0]+w);
                nd[v][1]=min(nd[v][1],od[u][0]+w/2);
            }

            if(od[u][1]!=INF)
            {
                nd[v][1]=min(nd[v][1],od[u][1]+w);
            }
        }
        od=nd;
        ans=min(ans,od[n][1]);
    }

    if(ans==INF) cout<<"Not possible";
    else cout<<ans;

    cout<<endl;
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