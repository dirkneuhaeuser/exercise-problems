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
    
    int t=1; 
    cin >> t;
    while(t--) 
    { 
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

enum {VISITED=-2, UNVISITED=-1};
int n;

tuple<int, int, int> moveUp(int curPointingBottom, int curPointingUp, int curPointingLeft){
    return {curPointingUp, 7-curPointingBottom, curPointingLeft};
}
tuple<int, int, int> moveBottom( int curPointingBottom, int curPointingUp, int curPointingLeft){
    return {7-curPointingUp, curPointingBottom, curPointingLeft};
}
tuple<int, int, int> moveLeft( int curPointingBottom, int curPointingUp, int curPointingLeft){
    return {curPointingLeft, curPointingUp, 7 - curPointingBottom};
}
tuple<int, int, int> moveRight( int curPointingBottom, int curPointingUp, int curPointingLeft){
    return {7-curPointingLeft, curPointingUp, curPointingBottom};
}

int visited[21][21][7][7][7];


void dfs(int i, int j, int curPointingBottom, int curPointingUp, int curPointingLeft, vector<vector<char>> &grid){
    visited[i][j][curPointingBottom][curPointingUp][curPointingLeft] = VISITED;
    
    if(i>0 && grid[i-1][j] != '*'){
        auto [nd, nf, nl] = moveUp(curPointingBottom, curPointingUp, curPointingLeft);
        if(visited[i-1][j][nd][nf][nl] == UNVISITED)  dfs(i-1, j, nd, nf, nl, grid);// up
    }
    if(j>0 && grid[i][j-1] != '*'){
        auto [nd, nf, nl] = moveLeft(curPointingBottom, curPointingUp, curPointingLeft);
        if(visited[i][j-1][nd][nf][nl] == UNVISITED)  dfs(i, j-1, nd, nf, nl, grid);//  left
    }
    if(i<n-1 && grid[i+1][j] != '*'){
        auto [nd, nf, nl] = moveBottom(curPointingBottom, curPointingUp, curPointingLeft);
        if(visited[i+1][j][nd][nf][nl] == UNVISITED)  dfs(i+1, j, nd, nf, nl, grid);// down
    }
    if(j<n-1 && grid[i][j+1] != '*'){
        auto [nd, nf, nl] = moveRight(curPointingBottom, curPointingUp, curPointingLeft);
        if(visited[i][j+1][nd][nf][nl] == UNVISITED)  dfs(i, j+1, nd, nf, nl, grid);// right
    }
}

void solve() 
{
    // basic dfs. Transititons of the dice might be awkward.
    cin >> n;
    vector<vector<char>> grid(n, vector<char>(n, '!'));
    int iHome, jHome, iStart, jStart;
    FOR(i, n){
        FOR(j, n){
            cin >> grid[i][j];
            if(grid[i][j] == 'H'){
                iHome = i;
                jHome = j;
            }
            if(grid[i][j] == 'S'){
                iStart = i;
                jStart = j;
            }
        }
    }
    memset(visited, -1, sizeof visited);
    dfs(iStart, jStart, 6, 4, 5, grid);
    for(int i=1; i<=6; ++i){
        for(int j=1; j<=6; ++j){
            if(visited[iHome][jHome][5][i][j] == VISITED){
                cout << "Yes";
                return;
            }
        }
    }
    cout << "No";


}

