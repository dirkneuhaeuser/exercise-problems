#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, bool> pib;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
const int MOD = 1'000'003;
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

int memo[301][50001];
char grid[301][50001];
int n, m;

bool dfs(int i, int j){
    if(memo[i][j] != -1)  return memo[i][j];
    if(grid[i][j] == '#') return false;
    if(grid[i][j] == '@') return true;
    bool poss = false;
    if(grid[i][j] == '>' && j< m){
        poss = poss | dfs(i, j+1);
    }
    if(grid[i][j] == '<' && j>0){
        poss = poss | dfs(i, j-1);
    }
    if(i >0){
        poss = poss | dfs(i-1, j);
    }
    return memo[i][j]=poss;

}

int dp(int i, int j){
    int &ans = memo[i][j];
    if(ans != -1) return ans;
    if(grid[i][j] == '@') return ans = 1;
    if(grid[i][j] == '#') return ans = 0;
    ans = 0;
    if(grid[i][j] == '>' && j < m ){
        ans += dp(i, j+1);
        ans = ans % MOD;
    }
    if(grid[i][j] == '<' && j > 0){
        ans += dp(i, j-1);
        ans = ans % MOD;
    }
    if(i>0){
        ans += dp(i-1, j);
        ans = ans % MOD;
    }
    return ans;
}
void solve() 
{
    // Basic DP problem with (too) strong timeconstraint/memory constraints: If our dp returns a pair<int, bool> which gives the {possibilities%Mod, isPossible} then this triggeres MLE.
    // So we need to do a DFS upfront to check if its possible and only then find the possibilities
    int r; 
    cin >> n >> m >> r;

    FOR(i, n){
        FOR(j, m){
            cin >> grid[i][j];
        }
    }
    memset(memo, -1, sizeof memo);
    bool poss = dfs(n-1, r);
    if(!poss){
        cout << "begin repairs";
    }else{
        memset(memo, -1, sizeof memo);
        int ans = dp(n-1,r);
        cout << ans;
    }
}


