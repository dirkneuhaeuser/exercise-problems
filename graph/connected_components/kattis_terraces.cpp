#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                          // ld up to  10*10^307
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

enum {VISITED = -2, UNVISITED = -1};

bool dfsIsPool(int i, int j, vector<vector<int>> &v, vector<vector<int>> &grid){
    v[i][j] = VISITED;
    bool ans = true;
    int cur = grid[i][j];
    if(i>0){
        if(grid[i-1][j] < cur) ans = false;
        if(grid[i-1][j] == cur && v[i-1][j] == UNVISITED) ans = ans & dfsIsPool(i-1, j, v, grid);
    }
    if(i+1<grid.size()){
        if(grid[i+1][j] < cur) ans = false;
        if(grid[i+1][j] == cur && v[i+1][j] == UNVISITED) ans = ans & dfsIsPool(i+1, j, v, grid);
    }
    if(j>0){
        if(grid[i][j-1] < cur) ans = false;
        if(grid[i][j-1] == cur && v[i][j-1] == UNVISITED) ans = ans & dfsIsPool(i, j-1, v, grid);
    }
    if(j+1<grid[0].size()){
        if(grid[i][j+1] < cur) ans = false;
        if(grid[i][j+1] == cur && v[i][j+1] == UNVISITED) ans = ans & dfsIsPool(i, j+1, v, grid);
    }
    return ans;
}

int getSizeOfHeight(int i, int j, vector<vector<int>> &v, vector<vector<int>> &grid){
    v[i][j] = VISITED;
    int ans = 1;
    int cur = grid[i][j];
    if(i>0){
        if(grid[i-1][j] == cur && v[i-1][j] == UNVISITED) ans += getSizeOfHeight(i-1, j, v, grid);
    }
    if(i+1<grid.size()){
        if(grid[i+1][j] == cur && v[i+1][j] == UNVISITED) ans += getSizeOfHeight(i+1, j, v, grid);
    }
    if(j>0){
        if(grid[i][j-1] == cur && v[i][j-1] == UNVISITED) ans += getSizeOfHeight(i, j-1, v, grid);
    }
    if(j+1<grid[0].size()){
        if(grid[i][j+1] == cur && v[i][j+1] == UNVISITED) ans += getSizeOfHeight(i, j+1, v, grid);
    }
    return ans;
}


void solve() 
{
    // consider adjacent fields of the same height as a connected component. Count it only if no adjacent element of it is lower.
    int n, m; cin >> m >> n;
    vector<vector<int>> grid(n, vector<int>(m, -1));
    vector<vector<int>> v1(n, vector<int>(m, -1));
    vector<vector<int>> v2(n, vector<int>(m, -1));
    vector<vector<bool>> pool(n, vector<bool>(m, 0));
    FOR(i, n){
        FOR(j, m){
            cin >> grid[i][j];
        }
    }
    int ret = 0;
    FOR(i, n){
        FOR(j, m){
            if(v1[i][j] == UNVISITED){
                bool isPool = dfsIsPool(i, j, v1, grid);
                if(isPool){
                    ret += getSizeOfHeight(i,j, v2, grid);
                }

            }
        }
    }
    cout << ret;

}

