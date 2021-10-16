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
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

bool allSame(vector<vector<int>> &grid){
    return true;
}

vector<vector<int>> v;
int dfs(int iCur, int jCur, int colOrg, int colNext, vector<vector<int>> &grid){
    int n = grid.size();
    int ans = 0;
    v[iCur][jCur] = 1;

    if(grid[iCur][jCur] == colNext) ans++;

    // up
    if(iCur>0 && v[iCur-1][jCur] == -1 && (grid[iCur-1][jCur] == colNext || (grid[iCur][jCur] == colOrg && grid[iCur-1][jCur] == colOrg))){
        ans+=dfs(iCur-1, jCur, colOrg, colNext, grid);
    }
    
    // left
    if(jCur>0 && v[iCur][jCur-1] == -1 && (grid[iCur][jCur-1] == colNext || (grid[iCur][jCur] == colOrg && grid[iCur][jCur-1] == colOrg))){
        ans+=dfs(iCur, jCur-1, colOrg, colNext,  grid);
    }

    // down
    if(iCur < n-1 && v[iCur+1][jCur] == -1 && (grid[iCur+1][jCur] == colNext || (grid[iCur][jCur] == colOrg && grid[iCur+1][jCur] == colOrg))){
        ans+=dfs(iCur+1, jCur, colOrg, colNext,  grid);
    }
    
    // right
    if(jCur < n-1 && v[iCur][jCur+1] == -1 && (grid[iCur][jCur+1] == colNext || (grid[iCur][jCur] == colOrg && grid[iCur][jCur+1] == colOrg))){
        ans+=dfs(iCur, jCur+1, colOrg, colNext,  grid);
    }
    return ans;
}
void dfsColor(int iCur, int jCur, int colOrg, int colNext, vector<vector<int>> &grid){
    int n = grid.size();
    v[iCur][jCur] = 1;

    grid[iCur][jCur] = colNext;

    // up
    if(iCur>0 && v[iCur-1][jCur] == -1 && (grid[iCur-1][jCur] == colOrg)){
        dfsColor(iCur-1, jCur, colOrg, colNext, grid);
    }
    
    // left
    if(jCur>0 && v[iCur][jCur-1] == -1 && (grid[iCur][jCur-1] == colOrg)){
        dfsColor(iCur, jCur-1, colOrg, colNext,  grid);
    }

    // down
    if(iCur < n-1 && v[iCur+1][jCur] == -1 && (grid[iCur+1][jCur] == colOrg)){
        dfsColor(iCur+1, jCur, colOrg, colNext,  grid);
    }
    
    // right
    if(jCur < n-1 && v[iCur][jCur+1] == -1 && (grid[iCur][jCur+1] == colOrg)){
        dfsColor(iCur, jCur+1, colOrg, colNext,  grid);
    }

}



void solve() 
{
    // basic connected components / flood fill
    int n;cin >>n;
    vector<vector<int>> grid(n, vector<int>(n, 1));
    FOR(i, n){
        FOR(j, n){
            char c; cin >> c;
            int cInt = c-'0';
            grid[i][j] = cInt;
        }
    }
    vector<int> frequencies(6, 0);
    int cnt = 0;
    while(true){
        int curCol = grid[0][0];
        int maxE = 0;
        int maxC = 0; 
        for(int i=1; i<= 6; ++i){
            if(i == curCol) continue;
            v.assign(n, vector<int>(n, -1));
            int ans = dfs(0, 0, curCol, i, grid);
            if(ans > maxE){
                maxE = ans;
                maxC = i;
            }
        }
        if(maxC == 0) break;
        cnt++;
        frequencies[maxC-1]++;
        v.assign(n, vector<int>(n, -1));
        dfsColor(0, 0, curCol, maxC, grid);
    }
    cout << cnt << endl;
    FOR(i, 6){
        cout << frequencies[i];
        if(i < 5) cout << " ";
    }


}

