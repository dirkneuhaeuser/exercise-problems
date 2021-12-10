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
const int NINF = 1<<31;


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

const int maxN = 400'000;
int memo[maxN];
int dp(int cur, vector<vi> &AL, string &s){
    int &ans = memo[cur];
    if(ans != -1) return ans;
    if(cur == s.size()-1) return 0;
    int ret = NINF;
    for(int next: AL[cur]){
        ret = max(ret, dp(next, AL, s));
    }
    if(ret==NINF) return ans = ret;
    if(s[cur] == 'X') ret++;
    if(cur != 0 && s[cur] == '.') ret--;
    return ans = ret;
}

void solve() 
{
    // graph is DAG -> basic top-down dp
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<vi> AL(n);
    FOR(j, m){
        int a, b;cin >> a>> b;
        AL[a].push_back(b);
    }
    memset(memo, -1, sizeof memo);
    cout << dp(0, AL, s);

}

