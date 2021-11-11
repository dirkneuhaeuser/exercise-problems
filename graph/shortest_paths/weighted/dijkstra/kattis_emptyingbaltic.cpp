#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
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
#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)



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

void solve() 
{
    // Weighted SSSP. Go from drainer and spread the negative attitude. Only works with faster_dijkstra
    int n,m; cin >> n >> m;
    vector<vi> grid(n, vi(m, 0));
    FOR(i, n){
        FOR(j, m){
            cin >> grid[i][j];
        }
    }

    int iS, jS; cin >> iS >> jS;
    iS--; jS--;

    vector<vi> dis(n, vi(m, INF));
    dis[iS][jS] = grid[iS][jS];
    set<tiii>pq;
    vector<pii> dir{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    FOR(i, n) FOR(j, m) pq.insert({dis[i][j], i, j});
    ll ans = 0;
    while(pq.size()){
        auto [depth, i, j] = *pq.begin();;
        pq.erase(pq.begin());
        ans += max(0, -depth);
        for(auto [di, dj]: dir){
            int nextI = i+di;
            int nextJ = j+dj;
            if(nextI < 0 || nextJ < 0 || nextI > n-1 || nextJ > m-1) continue;
            int nextDepth = max(depth, grid[nextI][nextJ]);
            if(nextDepth < dis[nextI][nextJ]){
                pq.erase(pq.find({dis[nextI][nextJ], nextI, nextJ}));
                dis[nextI][nextJ] = nextDepth;
                pq.emplace(nextDepth, nextI, nextJ);
            }
        }
    }
    cout << ans << endl;

}

