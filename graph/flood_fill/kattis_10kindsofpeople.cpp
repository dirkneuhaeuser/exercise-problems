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


vector<vector<int>> v;
vector<vector<int>> cols;
void dfs(int iCur, int jCur, vector<vector<int>> &grid, int col){
    int n = grid.size();
    int m = grid[0].size();
    v[iCur][jCur] = 1;
    int cur = grid[iCur][jCur];
    cols[iCur][jCur] = col;

    // up
    if(iCur>0 && v[iCur-1][jCur] == -1 && grid[iCur-1][jCur] == cur){
        dfs(iCur-1, jCur, grid, col);
    }
    
    // left
    if(jCur>0 && v[iCur][jCur-1] == -1 && grid[iCur][jCur-1] == cur){
        dfs(iCur, jCur-1, grid, col);
    }

    // down
    if(iCur < n-1 && v[iCur+1][jCur] == -1 &&grid[iCur+1][jCur] == cur){
        dfs(iCur+1, jCur, grid, col);
    }
    
    // right
    if(jCur < m-1 && v[iCur][jCur+1] == -1 && grid[iCur][jCur+1] == cur){
        dfs(iCur, jCur+1, grid, col);
    }
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
    int n, m; 
    while(cin >> n >> m){
        vector<vector<int>> grid(n, vector<int>(m, 0));
        FOR(i, n){
            FOR(j, m){
                char c; cin >> c;
                int cInt = c - '0';
                grid[i][j] = cInt;
            }
        }
        v.assign(n, vector<int>(m, -1));
        cols.assign(n, vector<int>(m, -1));
        int col = 0;
        FOR(i, n){
            FOR(j, m){
                if(v[i][j] == -1){
                    dfs(i, j, grid, col++);
                }
            }
        }
        int queries; cin >> queries;
        FOR(i, queries){
            int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
            r1--; c1--; r2--; c2--;
            if(cols[r1][c1] == cols[r2][c2]){
                if(grid[r1][c1] == 0) {
                    cout <<"binary" <<endl;
                }else{
                    cout <<"decimal" <<endl;
                }
            }else{
                cout <<"neither" <<endl;
            }
        }
    }

}

