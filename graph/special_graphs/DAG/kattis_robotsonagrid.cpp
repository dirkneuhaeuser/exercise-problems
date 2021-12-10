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
const ll MOD = (1ll<<31)-1;
const ll INF = 1ll<<60;


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

bool visited[1000][1000];
vector<pii> dir{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool dfs(int i, int j, vector<string> &grid){
    int n = grid.size();
    visited[i][j] = true;
    if(grid[i][j] == '#') return 0;
    if(i == n-1 && j == n-1){
        return 1;
    }
    bool ans = 0;
    for(auto [di, dj]: dir){
        int nexti = i +di;
        int nextj = j +dj;
        if(nexti < 0 || nexti >=n || nextj < 0 || nextj >=n ) continue;
        if(visited[nexti][nextj]) continue;
        ans = ans | dfs(nexti, nextj, grid);
    }
    return ans;
}



void solve() 
{
    ll n;cin>>n;
    vector<string> grid(n);
    FOR(i, n){
        cin >> grid[i];
    }
    ll dp[n][n];
    memset(dp, 0, sizeof dp);
    for(ll i=n-1; i>=0; --i){
        for(ll j=n-1; j>=0; --j){
            if(grid[i][j] == '#') continue;
            if(i == n-1 && j == n-1){
                dp[i][j] = 1;
                continue;
            }
            if(i<n-1){
                dp[i][j]+= dp[i+1][j];
            }
            if(j<n-1){
                dp[i][j]+= dp[i][j+1];
            }
            dp[i][j] %= MOD;
        }
    }
    if(dp[0][0] != 0){
        cout << dp[0][0];
        return;
    }
    memset(visited, 0, sizeof visited);
    bool poss = dfs(0, 0, grid);
    if(poss){
        cout <<"THE GAME IS A LIE";
    }else{
        cout <<"INCONCEIVABLE";
    }

}

