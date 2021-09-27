#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
// 2**6 =  64                           // 4!  = 24                       
// 2**8 =  256                          // 5!  = 120                      
// 2**10 = 1,024                        // 6!  = 720
// 2**15 = 32,768                       // 7!  = 5,040
// 2**20 = 1,048,576                    // 8!  = 40,320
// 2**25 = 33,554,432                   // 9!  = 362,880
// 2**30 = 1,073,741,824                // 10! = 3,628,800
// 2**32 = 4,294,967,296                // 12! = 479,001,600
                                        // 14! = 87,178,291,200
// int up to  2*10^9 (2^31-1)           // 16! = 20,922,789,888,000
// ll up to   9*10^18 (2^63 -1)         // 18! = 6,402,373,705,728,000
// ull up to 18*10^18 (2^64-1)/         // 20! = 2,432,902,008,176,640,000                                                                    
// ld up to  10*10^307
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
    
    int t=1; 
    cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

void solve() 
{
    // very complex infinite coin-change with inclusion-exclusion
    // Instead of prohibitive finite-coin change (which would be if d1 = 10^5 and v = 10^5 -> 10^10)
    //
    // Instead: Infinite coin change and make use of inclusion/exlusion princible to account for overcounting. For example the possibility to have d1+1 times the c1 coin needs to be subtracted.
    // the same for d2 + 1times the c2 coin. However, then you need to add again when you have both (d1+1) times c1 and (d2+1) times c2...
    //
    vector<int> nums(4);

    FOR(i, 4){
        cin >> nums[i];
    }

    // infinite coin-change: from left to right -> each coin can use itself as often as it wants
    ll dp[100001];
    memset(dp, 0, sizeof dp);
    dp[0] = 1;

    for(int i=0; i<4;++i){
        for(int j=nums[i]; j<=100001; ++j){
            dp[j] += dp[j - nums[i]];
        }
    }


    int q; cin >> q;
    vector<int> freq(4);
    FOR(t, q){
        FOR(i, 4){
            cin >> freq[i];
        }
        int v; cin >> v;

        ll ret = 0;
        // Inclusion-exclusion:
        FOR(mask, (1<<4)){
            int cnt = 0, dv = v;
            FOR(j, 4){
                if((mask&(1<<j))){
                    cnt++;
                    dv -= (freq[j]+1) * nums[j]; // dp[v - (freq[i] + 1) *nums[i]] describes the ilegal possibilities, which we can only fulfil, if we choose freq[i]+1 times nums[i]
                }
            }
            if(dv>=0){// too much, didn't even contribute to v in the first place
                if(cnt&1){ // exclusion
                    ret -= dp[dv];
                }else{ // inclusion
                    ret += dp[dv];
                }
            }
        }
        cout << ret << endl;
    }

}

