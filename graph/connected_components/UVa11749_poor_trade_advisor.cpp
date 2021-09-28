#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
// int up to 2*10^9 (2^31-1)
// ll up to 9*10^18 (2^63 -1)
typedef long long ll;  
// ull up to 18*10^18 (2^64-1)
typedef unsigned long long ull; 
// ld up to  10*10^307
typedef long double ld; 
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
ll smod(ll a, ll m){return((a%m) +m) %m;}
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;
const int INF = 1<<30;


void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/output.txt", "w", stdout); 
    #endif 
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

enum {UNVISITED = -1, VISITED = 1};
int dfs(int cur, vector<vector<pii>> &al, vector<int>&visited, int maxV){
    visited[cur] = VISITED;
    int ans = 1;
    for(auto [next, v]: al[cur]){
        if(visited[next] == UNVISITED && v == maxV){
            ans += dfs(next, al, visited, maxV);
        }
    }
    return ans;
}
    
void solve() 
{
    // basic connected components. Here connected by most valuable roads
    int n, m;
    while(cin >> n >> m && (n != 0 && m != 0)){
        vector<vector<pii>> al(n, vector<pii>());
        int maxPPA = 1<<31; // a very big negative number
        FOR(j, m){
            int a, b; cin >> a >> b;
            a--; b--;
            int v; cin >> v;
            maxPPA = max(maxPPA, v);
            al[a].push_back({b, v});
            al[b].push_back({a, v});
        }
        int ret = 0;
        vector<int>v(n, UNVISITED);
        for(int i=0; i<n; ++i){
            if(v[i] == UNVISITED){
                ret = max(ret, dfs(i, al, v, maxPPA));
            }
        }
        cout << ret << endl;
    }

}

