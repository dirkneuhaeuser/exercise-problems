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
int dfsColor(int iCur, int jCur, vector<vector<char>> &grid, int col){
    int n = grid.size();
    int m = grid[0].size();
    v[iCur][jCur] = 1;
    int cur = grid[iCur][jCur];
    grid[iCur][jCur] = col;
    int ans = 1;

    // up
    if(iCur>0 && v[iCur-1][jCur] == -1 && grid[iCur-1][jCur] == '.'){
        ans += dfsColor(iCur-1, jCur, grid, col);
    }
    
    // left
    if(jCur>0 && v[iCur][jCur-1] == -1 && grid[iCur][jCur-1] == '.'){
        ans += dfsColor(iCur, jCur-1, grid, col);
    }

    // down
    if(iCur < n-1 && v[iCur+1][jCur] == -1 &&grid[iCur+1][jCur] == '.'){
        ans += dfsColor(iCur+1, jCur, grid, col);
    }
    
    // right
    if(jCur < m-1 && v[iCur][jCur+1] == -1 && grid[iCur][jCur+1] == '.'){
        ans += dfsColor(iCur, jCur+1, grid, col);
    }
    return ans;
}

void dfsColorCircle(int iCur, int jCur, vector<vector<char>> &grid, int col, bool hor){
    int n = grid.size();
    int m = grid[0].size();
    bool inter = grid[iCur][jCur] == 'I';
    if(!inter) {
        v[iCur][jCur] = 1;
        grid[iCur][jCur] = col;
    }
    if(inter){
        if(hor){
            // left
            if(jCur>0 && v[iCur][jCur-1] == -1 && (grid[iCur][jCur-1] == 'X'||grid[iCur][jCur-1] == 'I')){
                dfsColorCircle(iCur, jCur-1, grid, col, true);
            }

            // right
            if(jCur < m-1 && v[iCur][jCur+1] == -1 && (grid[iCur][jCur+1] == 'X'||grid[iCur][jCur+1] == 'I')){
                dfsColorCircle(iCur, jCur+1, grid, col, true);
            }
        }else{
            // up
            if(iCur>0 && v[iCur-1][jCur] == -1 && (grid[iCur-1][jCur] == 'X' ||grid[iCur-1][jCur] == 'I') ){
                dfsColorCircle(iCur-1, jCur, grid, col, false);
            }

            // down
            if(iCur < n-1 && v[iCur+1][jCur] == -1 && (grid[iCur+1][jCur] == 'X'||grid[iCur+1][jCur] == 'I')){
                dfsColorCircle(iCur+1, jCur, grid, col, false);
            }
            
        }
    }else{
        // up
        if(iCur>0 && v[iCur-1][jCur] == -1 && (grid[iCur-1][jCur] == 'X' ||grid[iCur-1][jCur] == 'I') ){
            dfsColorCircle(iCur-1, jCur, grid, col, false);
        }
        
        // left
        if(jCur>0 && v[iCur][jCur-1] == -1 && (grid[iCur][jCur-1] == 'X'||grid[iCur][jCur-1] == 'I')){
            dfsColorCircle(iCur, jCur-1, grid, col, true);
        }

        // down
        if(iCur < n-1 && v[iCur+1][jCur] == -1 && (grid[iCur+1][jCur] == 'X'||grid[iCur+1][jCur] == 'I')){
            dfsColorCircle(iCur+1, jCur, grid, col, false);
        }
        
        // right
        if(jCur < m-1 && v[iCur][jCur+1] == -1 && (grid[iCur][jCur+1] == 'X'||grid[iCur][jCur+1] == 'I')){
            dfsColorCircle(iCur, jCur+1, grid, col, true);
        }
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
    // connected components / flood fill: A bit more complicated. 
    // First: Mark the surroundings differently
    // Second Mark the Intersection differently
    // Third: Mark each cicle in its color. Note when going thorud intersections, you have to keep the same direction
    // Now you have 3 connected components, check if up/downleft/right there are borders of a or b and then make normal flood fill
    int n, m; cin >> n >> m;
    n+=2; 
    m+=2;
    vector<vector<char>> grid(n, vector<char>(m, '.'));
    FOR(i , n-2){
        FOR(j , m-2){
            cin >> grid[i+1][j+1];
        }
    }
    for(int i=2; i<n-2; ++i){
        for(int j=2; j<m-2; ++j){
            if(grid[i][j] == 'X' && grid[i-1][j] != '.' && grid[i+1][j] != '.'&& grid[i][j-1] != '.'&& grid[i][j+1] != '.'){
                grid[i][j] = 'I';
            }
        }
    }
    v.assign(n, vector<int>(m, -1));
    dfsColor(0, 0, grid, 'O');
    for(int i=1; i<n-1; ++i){
        for(int j=1; j<m-1; ++j){
            if(grid[i][j] == 'A'){
                dfsColorCircle(i, j, grid, 'A', true);
            }
            if(grid[i][j] == 'B'){
                dfsColorCircle(i, j, grid, 'B', true);
            }
        }
    }
    vector<int> ret{0, 0, 0};
    for(int i=1; i<n-1; ++i){
        for(int j=1; j<m-1; ++j){
            if(v[i][j] != -1) continue;
            if(grid[i][j] == '.'){
                bool aUp=0, aDown=0, aLeft=0, aRight=0, bUp=0, bDown=0, bLeft=0, bRight=0;
                for(int ii=0; ii<n; ++ii){
                    if(grid[ii][j] == 'A' || grid[ii][j] == 'I'){
                        if(ii < i) aUp=true;
                        if(ii > i) aDown=true;
                    }
                    if(grid[ii][j] == 'B' || grid[ii][j] == 'I'){
                        if(ii < i) bUp=true;
                        if(ii > i) bDown=true;
                    }
                }
                for(int jj=0; jj<m; ++jj){
                    if(grid[i][jj] == 'A' || grid[i][jj] == 'I'){
                        if(jj < j) aLeft=true;
                        if(jj > j) aRight=true;
                    }
                    if(grid[i][jj] == 'B' || grid[i][jj] == 'I'){
                        if(jj < j) bLeft=true;
                        if(jj > j) bRight=true;
                    }
                }
                int ans = dfsColor(i, j, grid, 'F');
                bool a = aUp && aDown && aLeft && aRight;
                bool b = bUp && bDown && bLeft && bRight;
                if(a&&b){
                    ret[2] += ans;
                }else if(a){
                    ret[0] += ans;
                }else{
                    ret[1] += ans;
                }
            }
        }
    }
    cout << ret[0] << " " << ret[1] << " " << ret[2] << endl;


}

