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

int n, m;
map<pair<int, vector<int>>, ld> dpM;
ld dp(int damageLeftToDeal, vector<int> lifes){
    
    pair<int, vector<int>> key = {damageLeftToDeal, lifes};
    auto it = dpM.find(key);
    if(it != dpM.end()){
        return it->second;
    }
    int alive = 0;
    bool allMZero = true;
    int totalLifes = 0;
    for(int i =0; i<n+m; ++i){
        if(lifes[i]) alive++;
        if(i<n)
            totalLifes -= lifes[i];
        else
            totalLifes += lifes[i];

        if(i >= n && lifes[i]!=0){
            allMZero = false;
        }
    }
    // abort if all will die anyway or are already dead
    if(totalLifes <= damageLeftToDeal || allMZero){
        dpM[key] = 1;
        return 1;
    }
    // abort if no damageLeftToDeal
    if(damageLeftToDeal == 0) return 0;
    
    ld prob = (ld)1/alive;
    ld ret = 0;
    for(int i = 0; i<lifes.size(); ++i){
        if(i<n){
            if(lifes[i]){
                vector<int> copy = lifes;
                copy[i]++;
                sort(copy.begin(), copy.end());
                ret += prob*dp(damageLeftToDeal-1, copy);
            }
        }else{
            if(lifes[i]){
                vector<int> copy = lifes;
                copy[i]--;
                sort(copy.begin(), copy.end());
                ret += prob*dp(damageLeftToDeal-1, copy);
            }
        }
    }
    dpM[key] = ret;
    return ret;
}



void solve() 
{
    int d; cin >> n >> m >> d;
    d = min(d, (n+m)*6);

    // problem: dp states are kind of difficult here. You have the demage you still need to deal and the lifes of all minions.
    // -> states: d * 6^10 -> huge
    // ideas:
    // 1. only few damageToDeal and minion life combinations could actually occur -> to top-down approach (still too slow)
    // 2. the life-states should be sorted: If i have 2 minons it doesn't matter if they have [2,1] lifes or [1, 2]. The result is the same.
    //    Calculate only one combinatin and sort all the time

    vector<int> lifes(n+m);
    FOR(i, n+m){
        int num; cin >> num;
        if(i<n)
            lifes[i] = -num;
        else
            lifes[i] = num;
    };
    sort(lifes.begin(), lifes.end());
    cout << setprecision(6) << fixed <<dp(d, lifes);

}

