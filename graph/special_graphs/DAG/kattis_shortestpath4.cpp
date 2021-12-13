#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<ll, ll, ll, ll> tiii;
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

int memo[1000][1000][31];

int dp(int cur, int tar, int k, vector<vector<pii>> &AL){
    if(k < 0) return INF;
    int &ans = memo[cur][tar][k];
    if(ans != -1) return ans;
    if(cur == tar && k>=0){
        return ans = 0;
    }
    ans = INF;
    
    for(auto [next, w]: AL[cur]){
        int pot = dp(next, tar, k-1, AL);
        if(pot == INF)  continue;
        ans = min(ans, pot + w);
    }
    return ans;
    
}


void solve() 
{
    // problem: https://open.kattis.com/problems/shortestpath4
    // about: Normally, on undirected Graphs you cannot do DP, as it cycles infinitely in cycles. Here, with the factor max-steps k, the graph however turns into a DAG. Therefore a simple DP to get the min time is sufficient.
    int n; cin >> n;
    vector<vector<pii>> AL(n);
    FOR(i, n){
        int m; cin >> m;
        FOR(j, m){
            ll next, w; cin >> next >> w;
            AL[i].push_back({next, w});
        }
    }
    int q; cin >> q;
    memset(memo, -1, sizeof memo);
    FOR(i, q){
        int s, t, k; cin >> s >> t >> k;
        int cost = dp(s, t, k-1, AL);
        if(cost == INF){
            cout << -1 << endl;
        }else{
            cout << cost << endl;
        }
    }

}

