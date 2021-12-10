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

ll smod(ll a, ll m=MOD){return((a%m) +m) %m;}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m=MOD){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
ll modPow(ll b, ll p, ll m=MOD){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
ll invFerm(ll a, ll m=MOD){ return modPow(a, m-2,m);}
ll modAdd(ll a, ll b, ll m=MOD){return smod(a+b, m);};
ll modSub(ll a, ll b, ll m=MOD){return smod(a-b, m);};
ll modMul(ll a, ll b, ll m=MOD){return smod(a*b, m);};
ll modDiv(ll a, ll b, ll m=MOD){return smod(a*invEea(a, m), m);};

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
int dp[10001][101]; // dp[i][j] := the Nr. of possibilities when having i ribbon left before processing the j horizontal-idx;
void solve() 
{
    // basic DP problem. First compute the total number of scenes, including flat scenes and then subtracting the flat ones
    int n, w, h; cin >> n >> w >>h;
    memset(dp, 0, sizeof dp);

    FOR(i, n+1) dp[i][w] = 1; // does not matter how much ribbon is left

    for(int j=w-1; j>=0; j--){
        for(int i=0; i<=n; ++i){
            for(int l=0; l <= min(h,i); ++l){
                dp[i][j] = ((ll)dp[i][j] + dp[i-l][j+1]) % MOD;
            }
        }
    }
    int ans = dp[n][0]; // number of scenes possible with n ribbon lenth ( and when starting from the left)
    // subtract the possibilities for a flat scenes
    for(int i=0; i<=h; ++i){
        int needed = w*i;
        if(needed <=n ) ans--;
        else break;
    }
    ans = smod(ans);
    cout << ans << endl;

}

