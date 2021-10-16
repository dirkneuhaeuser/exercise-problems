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

bool isTrapNear(int i, int j, vector<vector<char>> &grid){
    return (grid[i-1][j] == 'T' || grid[i+1][j] == 'T' || grid[i][j-1] == 'T' || grid[i][j+1] == 'T');
}

vector<vector<int>> v;
int dfs(int iCur, int jCur, vector<vector<char>> &grid){
    int n = grid.size();
    int m = grid[0].size();
    int ans = 0;
    if(grid[iCur][jCur] == 'G') ans++;
    v[iCur][jCur] = 1;
    if(isTrapNear(iCur, jCur, grid)) return ans;
    // up
    if(iCur>0 && v[iCur-1][jCur] == -1 && (grid[iCur-1][jCur] == '.' || grid[iCur-1][jCur] == 'G')){
        ans+=dfs(iCur-1, jCur, grid);
    }
    
    // left
    if(jCur>0 && v[iCur][jCur-1] == -1 && (grid[iCur][jCur-1] == '.' || grid[iCur][jCur-1] == 'G')){
        ans+=dfs(iCur, jCur-1, grid);
    }

    // down
    if(iCur < n-1 && v[iCur+1][jCur] == -1 && (grid[iCur+1][jCur] == '.' || grid[iCur+1][jCur] == 'G')){
        ans+=dfs(iCur+1, jCur, grid);
    }
    
    // right
    if(jCur < m-1 && v[iCur][jCur+1] == -1 && (grid[iCur][jCur+1] == '.' || grid[iCur][jCur+1] == 'G')){
        ans+=dfs(iCur, jCur+1, grid);
    }
    return ans;
}

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
    // basic connected components / flood fill
    int n, m; cin >> m >> n;
    int cnt = 1;
    vector<vector<char>> grid(n, vector<char>(m, 'c'));
    int iP, jP;
    FOR(i, n){
        FOR(j, m){
            cin >> grid[i][j];
            if(grid[i][j] == 'P'){
                //cout << "dude " << i << " " << j  << " " << grid[i][j]<< endl;
                iP = i;
                jP = j;
            }
        }
    }
    //dbg(grid);
    //cout << iP << " " << jP << endl;

    v.assign(n, vector<int>(m, -1));
    int ret = dfs(iP, jP, grid);
    cout << ret;

}

