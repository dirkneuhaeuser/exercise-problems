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
const int MOD = 1'000'000'009;
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
    // problem: https://open.kattis.com/problems/cardmagic
    // about: basic knapsack
    int n,k,target; cin >> n >> k >> target;
    int dp[n+1][target+1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for(int i=1; i<=n; ++i){
        for(int j=0; j<= target;++j){
            for(int l=1; l<=k; ++l){
                if(j>=l){
                    dp[i][j] += dp[i-1][j-l];
                    dp[i][j] %= MOD;
                }
            }
        }
    }
    cout << dp[n][target];

}

