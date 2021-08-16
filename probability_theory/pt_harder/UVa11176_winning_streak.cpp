#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#define FORS(i, n) for(; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/templates/debug.h"
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
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*b,m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;


void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 
    
    int t=1; 
    //cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        //cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    int n;
    ld p;
    cout << setprecision(10) << fixed;
    while(cin >> n >> p){
        if(n==0) return;
        dp[0][0] = 1;
        if(p==1){
            cout << (ld)n << endl;
            continue;
        }
        if(p == 0){
            cout << (ld)0 << endl;
            continue;
        }
        ld l = 1-p;
        vector<ld> probs;
        for(int i =0; i<=n; ++i){
            probs.push_back(powl(p, i)*l);
        }
        vector<vector<ld>> dp(n+2, vector<ld>(n+1, 0)); // dp[i][j] denots prob that after the ith match, which you lost, the max Streak is j
        // note you could also do dp[i][j][k]: the prob. that after the ith match, the max streak is j and the current streak is k;
        // it boils all down to n**3
        for(int i=0; i<n; ++i){
            for(int j=0;j<=i;++j){
                for(int k = i+1; k<= n+1; ++k){
                    // next time losing eventually in the kth game. up to that everything is winning
                    int streak = k-(i+1);
                    int maxStreak = max(streak, j);
                    dp[k][maxStreak] += dp[i][j]*probs[streak];
                }
            }
        }
        ld ret = 0;
        for(int j=0; j<n+1; ++j){
            ret += j*(dp[n+1][j]/l); // last match won -> lost fictional n+1 th match
            ret += j*(dp[n][j]); // last match lost
        }
        cout <<ret << endl;
    }

}

