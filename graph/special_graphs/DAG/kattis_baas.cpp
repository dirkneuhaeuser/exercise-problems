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
ll smod(ll a, ll m){return((a%m) +m) %m;}
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
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

int memo[400][400];

int dp(int cur, int toSkip, vi &times, vector<vi> &AL){
    int &ans = memo[cur][toSkip];
    if(ans != -1) return ans;
    int following = 0;
    for(int next: AL[cur]){
        following = max(following, dp(next, toSkip, times, AL));
    }
    if(cur == toSkip){
        return ans = following;
    }else{
        return ans = following + times[cur];
    }
}


void solve() 
{
    // DAG -> DP. Run n times to check the result when skipping the ith node
    int n; cin >> n;
    vi times(n);
    FOR(i, n) cin >> times[i];
    vector<vi> AL(n);
    FOR(i, n){
        int m; cin >> m;
        FOR(j, m){
            int dep; cin >> dep;
            AL[dep-1].push_back(i);
        }
    }
    memset(memo, -1, sizeof memo);
    int ret = INF;
    for(int i=0; i<n; ++i){
        int ans = dp(0, i, times, AL);
        ret = min(ret, ans);
    }
    cout << ret;

}

