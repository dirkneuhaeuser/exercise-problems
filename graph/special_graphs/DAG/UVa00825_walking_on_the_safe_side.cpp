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
        if(t) cout << endl;
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    // basic DP on DAG to count paths
    int n, m; cin >> n >> m;
    string line; getline(cin, line);
    vector<vector<bool>> AM(n, vector<bool>(m, false));
    FOR(i, n){
        getline(cin, line);
        stringstream ss; ss << line;
        int start; ss >> start;
        start--;
        int next;
        while(ss>>next){
            next--;
            AM[start][next] = true;
        }
    }
    int dp[n][m];
    memset(dp, 0, sizeof dp);
    for(int i=n-1; i>=0; --i){
        for(int j=m-1; j>=0; --j){
            if(i==n-1 && j == m-1){
                dp[i][j] = 1;
                continue;
            }
            else if(AM[i][j]) continue;
            if(i<n-1){
                dp[i][j] += dp[i+1][j];
            }
            if(j<m-1){
                dp[i][j] += dp[i][j+1];
            }
        }
    }
    cout << dp[0][0];


}

