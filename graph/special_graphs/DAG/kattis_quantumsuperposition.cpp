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

int memo [1000][2001][2];

bool dp(int cur, int steps, vector<vi> &AL, bool uni1){
    int &ans = memo[cur][steps][uni1];
    if(ans != -1) return ans;
    int n = AL.size();
    if(steps == 0 && cur == n-1) return ans=1;
    if(steps == 0) return ans=0;
    for(int next: AL[cur]){
        if(dp(next, steps-1, AL, uni1)) return ans=1;
    }
    return ans=0;
}


void solve() 
{
    // problem: https://open.kattis.com/problems/quantumsuperposition
    // about: As graph is a DAG, use DP and try all possibilites
    int n1, n2, m1, m2; cin >> n1 >> n2 >> m1 >> m2;
    vector<vi> AL1(n1), AL2(n2);
    memset(memo, -1, sizeof memo);
    FOR(i, m1){
        int a, b; cin >> a >> b;
        a--; b--;
        AL1[a].push_back(b);
    }
    FOR(i, m2){
        int a, b; cin >> a >> b;
        a--; b--;
        AL2[a].push_back(b);
    }
    int q; cin >> q;
    FOR(i, q){
        bool possible = false;
        int num; cin >> num;
        FOR(l, num+1){
            int u1 = l;
            int u2 = num-l;
            if(dp(0, u1, AL1, true) && dp(0, u2, AL2, false)){
                possible = true;
                break;
            }
        }
        if(possible){
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }


}

