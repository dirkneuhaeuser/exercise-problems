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
    int count = 1;
    while(t--) 
    { 
        cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
unordered_map<string, int> name2idx;
vector<string> idx2name;
int getIdx(string name){
    if(name2idx.count(name) ==0){
        name2idx[name] = idx2name.size();
        idx2name.push_back(name);
    }
    return name2idx[name];
}
void solve() 
{
    // Basic DP problem
    int n; cin >> n;
    name2idx.clear();
    idx2name.clear();
    string line; getline(cin, line);
    FOR(i, n){
        string line; getline(cin, line);
        getIdx(line);
    }
    int q; cin >> q;
    getline(cin, line);
    int dp[q+1][n];
    fill_n(&dp[0][0], (q+1)*n, INF);
    FOR(i, n){
        dp[q][i] = 0;
    }
    for(int k=q-1; k>=0; --k){
        getline(cin, line);
        int qIdx=getIdx(line);
        FOR(i, n){
            if(i == qIdx){
                dp[k][i] = INF;
                continue;
            }
            FOR(j, n){
                if(i == j){
                    if(dp[k+1][j] != INF) dp[k][i] = min(dp[k][i], dp[k+1][j]);
                }else{
                    if(dp[k+1][j] != INF) dp[k][i] = min(dp[k][i], 1+dp[k+1][j]);
                }
            }
        }
    }
    int ret = INF;
    FOR(i, n){
        ret = min(ret, dp[0][i]);
    }
    cout << ret;

}

