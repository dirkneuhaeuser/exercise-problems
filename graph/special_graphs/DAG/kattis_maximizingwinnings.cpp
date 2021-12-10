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

int memo[50][5000];

int dpMax(int curRoom, int movesLeft, vector<vector<int>> &AM){
    int &ans = memo[curRoom][movesLeft];
    if(ans != -1) return ans;
    if(movesLeft == 0) return ans = 0;
    ans = 0;
    for(int i=0; i<AM.size(); ++i){
        ans = max(ans, AM[curRoom][i] + dpMax(i, movesLeft-1, AM));
    }
    return ans;
}
int dpMin(int curRoom, int movesLeft, vector<vector<int>> &AM){
    int &ans = memo[curRoom][movesLeft];
    if(ans != -1) return ans;
    if(movesLeft == 0) return ans = 0;
    ans = INF;
    for(int i=0; i<AM.size(); ++i){
        ans = min(ans, AM[curRoom][i] + dpMin(i, movesLeft-1, AM));
    }
    return ans;
}

void solve() 
{
    // problem: https://open.kattis.com/problems/maximizingwinnings
    // about: Baisc DP problem
    int n;
    while(cin >> n && n){
        vector<vector<int>> AM(n, vector<int>(n, 0));
        FOR(i, n){
            FOR(j, n){
                cin >> AM[i][j];
            }
        }
        int m; cin >> m;
        memset(memo, -1, sizeof memo);
        int ansMax = dpMax(0, m, AM);
        memset(memo, -1, sizeof memo);
        int ansMin = dpMin(0, m, AM);
        cout << ansMax << " "<< ansMin << endl;
    }

}

