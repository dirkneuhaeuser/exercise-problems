#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
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
enum {VISITED=-2, UNVISITED=-1};
vector<int> visited;
int dfs(int cur,  vector<vector<int>> &AL, vector<int> &money){
    visited[cur] = VISITED;
    int ret = money[cur];
    for(int next: AL[cur]){
        if(visited[next] == UNVISITED){
            ret += dfs(next, AL, money);
        }
    }
    return ret;
}

void solve() 
{
    // The sum of all conected components needs to be 0.
    int n, m;
    cin >> n >> m;
    vector<int> money(n, 0);
    FOR(i, n){
        cin >> money[i];
    }
    vector<vector<int>> AL(n, vector<int>());
    FOR(i, m){
        int a, b; cin >> a >> b;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    visited.assign(n, UNVISITED);
    FOR(i, n){
        if(visited[i] == UNVISITED){
            int ans = dfs(i, AL, money);
            if(ans != 0){
                cout << "IMPOSSIBLE";
                return;
            }
        }
    }
    cout << "POSSIBLE";

}

