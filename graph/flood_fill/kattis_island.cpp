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
int horiBridges(int iCur, int jCur, vector<string> &grid){
    int n = grid.size();
    int m = grid[0].size();
    v[iCur][jCur] = 1;
    int ans = grid[iCur][jCur] == 'B';
    
    // left
    if(jCur>0 && v[iCur][jCur-1] == -1 && grid[iCur][jCur-1] == 'B'){
        ans += horiBridges(iCur, jCur-1, grid);
    }
    
    // right
    if(jCur < m-1 && v[iCur][jCur+1] == -1 && grid[iCur][jCur+1] == 'B'){
        ans += horiBridges(iCur, jCur+1, grid);
    }
    return ans;
}
int vertBridges(int iCur, int jCur, vector<string> &grid){
    int n = grid.size();
    int m = grid[0].size();
    v[iCur][jCur] = 1;
    int ans = grid[iCur][jCur] == 'B';

    // up
    if(iCur>0 && v[iCur-1][jCur] == -1 && grid[iCur-1][jCur] == 'B'){
        ans += vertBridges(iCur-1, jCur, grid);
    }
    
    // down
    if(iCur < n-1 && v[iCur+1][jCur] == -1 &&grid[iCur+1][jCur] == 'B'){
        ans += vertBridges(iCur+1, jCur, grid);
    }
    
    return ans;
}

void dfsIslands(int iCur, int jCur, vector<string> &grid){
    int n = grid.size();
    int m = grid[0].size();
    v[iCur][jCur] = 1;
    // up
    if(iCur>0 && v[iCur-1][jCur] == -1 && (grid[iCur-1][jCur] == 'X' || grid[iCur-1][jCur] == '#')){
        dfsIslands(iCur-1, jCur, grid);
    }
    
    // left
    if(jCur>0 && v[iCur][jCur-1] == -1 && (grid[iCur][jCur-1] == 'X' || grid[iCur][jCur-1] == '#')){
        dfsIslands(iCur, jCur-1, grid);
    }

    // down
    if(iCur < n-1 && v[iCur+1][jCur] == -1 &&(grid[iCur+1][jCur] == 'X' || grid[iCur+1][jCur] == '#')){
        dfsIslands(iCur+1, jCur, grid);
    }
    
    // right
    if(jCur < m-1 && v[iCur][jCur+1] == -1 && (grid[iCur][jCur+1] == 'X' || grid[iCur][jCur+1] == '#')){
        dfsIslands(iCur, jCur+1, grid);
    }
}

void dfsAll(int iCur, int jCur, vector<string> &grid, int col, bool hor){
    int n = grid.size();
    int m = grid[0].size();
    v[iCur][jCur] = 1;
    bool isBridge = grid[iCur][jCur]=='B';
    bool isPort = grid[iCur][jCur]=='X';
    grid[iCur][jCur] = col;
    if(isBridge){
        if(hor){
            // bridge left
            if(isBridge && jCur>0 && v[iCur][jCur-1] == -1 && (grid[iCur][jCur-1] == 'B' || grid[iCur][jCur-1] == 'X')){
                dfsAll(iCur, jCur-1, grid, col, hor);
            }
            // bridge right
            if(isBridge && jCur < m-1 && v[iCur][jCur+1] == -1 && (grid[iCur][jCur+1] == 'B' || grid[iCur][jCur+1] == 'X')){
                dfsAll(iCur, jCur+1, grid, col, hor);
            }
        }else{
            // bridge up
            if(isBridge && iCur>0 && v[iCur-1][jCur] == -1 && (grid[iCur-1][jCur] == 'B' || grid[iCur-1][jCur] == 'X')){
                dfsAll(iCur-1, jCur, grid, col, hor);
            }
            // bridge down
            if(isBridge && iCur < n-1 && v[iCur+1][jCur] == -1 && (grid[iCur+1][jCur] == 'B' || grid[iCur+1][jCur] == 'X')){
                dfsAll(iCur+1, jCur, grid, col, hor);
            }

        }
    }else{
        // up
        if(iCur>0 && v[iCur-1][jCur] == -1 && (grid[iCur-1][jCur] == 'X' || grid[iCur-1][jCur] == '#')){
            dfsAll(iCur-1, jCur, grid, col, false);
        }
        if(isPort && iCur>0 && v[iCur-1][jCur] == -1 && (grid[iCur-1][jCur] == 'B')){
            dfsAll(iCur-1, jCur, grid, col, false);
        }
        
        // left
        if(jCur>0 && v[iCur][jCur-1] == -1 && (grid[iCur][jCur-1] == 'X' || grid[iCur][jCur-1] == '#')){
            dfsAll(iCur, jCur-1, grid, col, true);
        }
        if(isPort && jCur>0 && v[iCur][jCur-1] == -1 && (grid[iCur][jCur-1] == 'B')){
            dfsAll(iCur, jCur-1, grid, col, true);
        }

        // down
        if(iCur < n-1 && v[iCur+1][jCur] == -1 &&(grid[iCur+1][jCur] == 'X' || grid[iCur+1][jCur] == '#' )){
            dfsAll(iCur+1, jCur, grid, col, false);
        }
        if(isPort && iCur < n-1 && v[iCur+1][jCur] == -1 &&(grid[iCur+1][jCur] == 'B')){
            dfsAll(iCur+1, jCur, grid, col, false);
        }
        
        // right
        if(jCur < m-1 && v[iCur][jCur+1] == -1 && (grid[iCur][jCur+1] == 'X' || grid[iCur][jCur+1] == '#')){
            dfsAll(iCur, jCur+1, grid, col, true);
        }
        if(isPort && jCur < m-1 && v[iCur][jCur+1] == -1 && (grid[iCur][jCur+1] == 'B')){
            dfsAll(iCur, jCur+1, grid, col, true);
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
    // connected components / flood fill: A bit more complicated. Note that bridges can only go horizontal or vertical. 
    int cnt = 1;
    while(true){
        vector<string> grid;
        while(true){
            string a; getline(cin, a);
            if(a=="")break;
            grid.push_back(a);
        }
        int n = grid.size();
        if(n==0) break;
        if(cnt != 1) cout << endl;
        int m = grid[0].size();
        int bridges = 0;
        v.assign(n, vector<int>(m, -1));
        FOR(i, n){
            FOR(j, m){
                if(grid[i][j] == 'X' && v[i][j] == -1){
                    int ans = vertBridges(i, j, grid);
                    if(ans > 0) bridges++;
                }
            }
        }
        v.assign(n, vector<int>(m, -1));
        FOR(i, n){
            FOR(j, m){
                if(grid[i][j] == 'X' && v[i][j] == -1){
                    int ans = horiBridges(i, j, grid);
                    if(ans > 0) bridges++;
                }
            }
        }
        int islands = 0;
        v.assign(n, vector<int>(m, -1));
        FOR(i, n){
            FOR(j, m){
                if((grid[i][j] == 'X' || grid[i][j] == '#') && v[i][j] == -1){
                    dfsIslands(i, j, grid);
                    islands++;
                }
            }
        }
        int buses = 0;
        int col = 0;
        v.assign(n, vector<int>(m, -1));
        FOR(i, n){
            FOR(j, m){
                if((grid[i][j] == 'X' || grid[i][j] == '#') && v[i][j] == -1){
                    char colChar = '0' + col++;
                    dfsAll(i, j, grid, colChar, false);
                    buses++;
                }
            }
        }
        cout << "Map " << cnt++ << endl;
        cout << "islands: " << islands << endl;
        cout << "bridges: " << bridges << endl;
        cout << "buses needed: " << buses << endl;

    }
}

