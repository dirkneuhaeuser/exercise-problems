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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
vector<bool> visited;
int dfs(int cur, vector<vector<pii>> &AL){
    visited[cur] = true;
    int ret = 0;
    bool last = true;
    for(auto [next, w]: AL[cur]){
        if(visited[next]) continue;
        last = false;
        int cost = min(w, dfs(next, AL));
        ret += cost;
    }
    if(last) return INF;
    return ret;
}
void solve() 
{
    // problem: https://open.kattis.com/problems/frozenrose 
    // about: basic dfs
    int n, c;
    while(cin >> n >> c){
        vector<vector<pii>> AL(n);
        FOR(i, n-1){
            int a, b, cost; cin >> a >> b >> cost;
            a--;b--;
            AL[a].push_back({b, cost});
            AL[b].push_back({a, cost});
        }
        visited.assign(n, false);
        int ans = dfs(c-1, AL);
        if(ans == INF){
            cout << 0 << endl;
        }else{
            cout << ans << endl;
        }
    }


}

