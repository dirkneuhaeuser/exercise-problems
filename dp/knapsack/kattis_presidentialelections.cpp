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
const ll INF = 1ll<<62;


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
void solve() 
{
    // Classical knapsack: items: states, weight: delegates, value to min.: votes
    int s; cin >> s;
    int delegatesC = 0;
    int delegatesF = 0;
    int delegatesTotal = 0;
    vector<pii> toFightFor;
    FOR(i, s){
        int d, vc, vf, vu; cin >> d >> vc  >> vf >> vu;
        int total = vc + vf + vu;
        if(2*vf>= total){
            delegatesF += d;
        }else if(2*vc > total){
            delegatesC += d;
        }else{
            int needed = (total - 2*vc  )/2  + 1;
            toFightFor.push_back({d, needed});
        }
        delegatesTotal+=d;
    }
    // check if you already won or already lost
    if(delegatesF*2 >= delegatesTotal){
        cout << "impossible" << endl;
        return;
    }
    if(delegatesC*2 >= delegatesTotal + 1){
        cout << 0 << endl;
        return;
    }

    // now classical knapsack: items: states, weight: delegates, value to min.: votes, 
    int needed = ((delegatesTotal) >> 1) + 1 - delegatesC;
    int maxDelegates = delegatesTotal + 1;
    int newS = toFightFor.size();


    ll dp[newS+1][maxDelegates];
    fill_n(&dp[0][0], (newS+1)*maxDelegates, INF);
    dp[0][0] = 0;

    for(int i = 1; i<=newS; ++i){
        int v = toFightFor[i-1].first;
        int w = toFightFor[i-1].second;
        for(int j = 0; j<maxDelegates; ++j){
            dp[i][j] = dp[i-1][j]; // omiting current state
            if(j >= v){
                dp[i][j] = min(dp[i][j], dp[i-1][j-v] + w);  // check if current state might be better
            }
        }
    }
    ll ret = INF;
    for(int i=needed; i<maxDelegates; ++i){
        ret =min(ret, dp[newS][i]);
    }
    if(ret == INF){
        cout << "impossible";
    }else{
        cout << ret;
    }


}

