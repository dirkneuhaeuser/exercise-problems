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

int dfs(int cur, vector<vector<int>> &AL, vector<int> &visited){
    visited[cur]=VISITED;
    int ans = 1;
    for(int next: AL[cur]){
        if(visited[next] == UNVISITED){
            ans += dfs(next, AL, visited);
        }
    }
    return ans;
}

void solve() 
{
    // basic connected components check: towards the city on the original graph and from city to interconnecting road: reversed Graph
    vector<vector<int>> AL(1000, vector<int>()),ALReversed(1000, vector<int>());
    vector<pair<int, int>> all;
    int n; cin >> n;
    FOR(i, n){
        int a, m; cin >> a >> m;
        all.push_back({i, a});
        FOR(j, m){
            int b; cin >> b;
            AL[a].push_back(b);
            ALReversed[b].push_back(a);
        }
    }
    sort(all.begin(), all.end());
    bool noProblem = true;

    // out of city
    vector<int> visited(1000, UNVISITED);
    dfs(0, ALReversed, visited);
    for(auto [idx, street]: all){
        if(street == 0) continue;
        if(visited[street] == UNVISITED){
            noProblem = false;
            cout << "TRAPPED " << street << endl;
        }
    }

    // into city
    visited.assign(1000, UNVISITED);
    dfs(0, AL, visited);
    for(auto [idx, street]: all){
        if(street == 0) continue;
        if(visited[street] == UNVISITED){
            noProblem = false;
            cout << "UNREACHABLE " << street << endl;
        }
    }
    if(noProblem){
        cout << "NO PROBLEMS" << endl;
    }



}

