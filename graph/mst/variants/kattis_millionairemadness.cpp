#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef tuple<int, int, int> tiii;
typedef pair<int, int> pii;
typedef pair<int, long double> pid;
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

void solve() 
{
    // MiniMax Path with Dijkstra
    int n, m; 
    while(cin >> n >> m){
        vector<vector<int>> grid(n, vector<int>(m, 0));
        FOR(i, n){
            FOR(j, m){
                cin >> grid[i][j];
            }
        }

        vector<pii> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        tiii start {0, 0, 0};
        priority_queue<tiii, vector<tiii>, greater<tiii>>pq;
        pq.push(start);
        while(pq.size()){
            auto [tc, ti, tj] = pq.top();pq.pop();
            if(ti == n-1 && tj == m-1){
                cout << tc << endl;
                return;
            }
            if(grid[ti][tj] == -1)continue;
            for(auto [di, dj]: directions){
                int nextI = ti+di;
                int nextJ = tj+dj;
                if(nextI >= 0 && nextI < n && nextJ >=0 && nextJ < m && grid[nextI][nextJ] != -1){
                    int dis = max(grid[nextI][nextJ] - grid[ti][tj], 0);
                    pq.push({max(dis, tc), nextI, nextJ});
                }
            }
            grid[ti][tj] = -1;
        }

    }
}



