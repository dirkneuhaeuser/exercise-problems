#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int, int, bool> state;
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

map<state, ll> memo;


ll dp(int cur, int stepOneLeft, int stepOneRight, int stepTwoLeft, int stepTwoRight, bool leftLeg){
    state par = {cur, stepOneLeft, stepOneRight, stepTwoLeft, stepTwoRight, leftLeg};
    auto it = memo.find(par);
    if(it != memo.end()) return it->second;

    int twos = stepTwoLeft+stepTwoRight;
    int ones = stepOneLeft+stepOneRight;
    if(cur == 0 && twos >= ones && stepOneLeft == stepOneRight && stepTwoLeft == stepTwoRight){
        return memo[par] =1;
    }else if(cur == 0){
        return memo[par] =-2;
    }
    // two-stride needs to be the same
    int difTwo = abs(stepTwoLeft - stepTwoRight);
    if(cur < difTwo * 2) return memo[par] =-2;

    // one-stide needs to be the same
    int difOne = abs(stepOneLeft - stepOneRight);
    if(cur < difOne) return memo[par] =-2;
    
    // twoStrideSteps > oneStideSteps
    if(twos + (cur >> 1)< ones) return memo[par] = -2;

    ll ans = 0;
    if(cur >=2 && leftLeg){
        ll sp = dp(cur-2, stepOneLeft, stepOneRight, stepTwoLeft+1, stepTwoRight, !leftLeg);
        if(sp != -2) ans+= sp;
    }
    if(cur >=2 && !leftLeg){
        ll sp = dp(cur-2, stepOneLeft, stepOneRight, stepTwoLeft, stepTwoRight+1, !leftLeg);
        if(sp != -2) ans+= sp;
    }
    if(cur >=1 && leftLeg){
        ll sp = dp(cur-1, stepOneLeft+1, stepOneRight, stepTwoLeft, stepTwoRight, !leftLeg);
        if(sp != -2) ans+= sp;
    }
    if(cur >=1 && !leftLeg){
        ll sp = dp(cur-1, stepOneLeft, stepOneRight+1, stepTwoLeft, stepTwoRight, !leftLeg);
        if(sp != -2) ans+= sp;
    }
    return memo[par] = ans;
}

void solve() 
{
    // DAG -> DP, here with several states, use map for memo
    int caseN, n; cin >> caseN >> n;
    ll ans = dp(n, 0,0, 0, 0, true);
    cout << caseN << " " << ans;

}

