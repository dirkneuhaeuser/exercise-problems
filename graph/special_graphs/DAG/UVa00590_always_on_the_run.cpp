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
int memo[10][1001];
int dp(int curCity, int curTime, int k, vector<vector<vector<int>>> &schedule){
    int &ans = memo[curCity][curTime];
    if(ans != -1) return ans;
    int n = schedule.size();
    if(curTime == k && curCity == n-1) return ans = 0;
    if(curTime == k) return ans = INF;
    int cost = INF;
    FOR(i, n){
        if(i == curCity) continue;
        int m = schedule[curCity][i].size();
        int idx = curTime % m;
        int flightCost = schedule[curCity][i][idx];
        if(flightCost == 0) continue;
        int pot = dp(i, curTime+1, k, schedule);
        if(pot == INF) continue;
        cost = min(cost, pot + flightCost);
    }
    return ans = cost;
}
void solve() 
{
    // problem: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=531
    // about: Basic DP problem
    int n, k;
    int cnt = 1;
    while(cin >> n >> k && (n!=0 || k!=0)){
        cout << "Scenario #" << cnt++ << endl;
        vector<vector<vector<int>>> schedule(n, vector<vector<int>>(n, vector<int>()));
        FOR(i, n){
            FOR(j, n){
                if(j == i) continue;
                int times; cin >> times;
                FOR(l, times){
                    int a; cin >> a;
                    schedule[i][j].push_back(a);
                }
            }
        }
        memset(memo, -1, sizeof memo);
        int ans = dp(0, 0, k, schedule);
        if(ans == INF){
            cout << "No flight possible." << endl;
        }else{
            cout << "The best flight costs " << ans << "." << endl;
        }
        cout << endl;
    }

}

