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

vector<vector<pii>> g = vector<vector<pii>>(15, vector<pii>());
map<vector<ll>, ll> memo;
vector<ll> nums(15);
ll NINF = 1ll << 63;
ll dp(vector<ll> nums){
    auto it = memo.find(nums);
    if(it != memo.end()) return it->second;
    ll ret = NINF;

    for(int j=0; j<15; ++j){
        if(nums[j] ==  0) continue;
        for(int i =0 ; i<g[j].size(); ++i){
            ll f = g[j][i].first; // to be overjumped and deleted
            ll s = g[j][i].second; // goal peg, needs to be empty
            if(nums[s] !=  0) continue;
            if(nums[f] ==  0) continue;
            ll mult = nums[j] * nums[f];
            swap(nums[j], nums[s]);
            ll cache = nums[f];
            nums[f] = 0;
            ret = max(ret, mult - dp(nums));
            swap(nums[j], nums[s]);
            nums[f] = cache;
        }
    }
    if(ret == NINF) ret = 0;
    return memo[nums] = ret;
    

}


void solve() 
{
    // note: can't use bottom up, as the order of the 0 will constantly swaps and therefore a bitmask needs higher and smaller numbers. Also the values for the vectors are constantly changing as well. So this is the actual state!

    g[0].push_back({1, 3});
    g[0].push_back({2, 5});

    g[1].push_back({3, 6});
    g[1].push_back({4, 8});

    g[2].push_back({4, 7});
    g[2].push_back({5, 9});

    g[3].push_back({1, 0});
    g[3].push_back({6, 10});
    g[3].push_back({7, 12});
    g[3].push_back({4, 5});

    g[4].push_back({7, 11});
    g[4].push_back({8, 13});

    g[5].push_back({2, 0});
    g[5].push_back({8, 12});
    g[5].push_back({9, 14});
    g[5].push_back({4, 3});

    g[6].push_back({3, 1});
    g[6].push_back({7, 8});

    g[7].push_back({4, 2});
    g[7].push_back({8, 9});
    
    g[8].push_back({4, 1});
    g[8].push_back({7, 6});

    g[9].push_back({5, 2});
    g[9].push_back({8, 7});

    g[10].push_back({6, 3});
    g[10].push_back({11, 12});

    g[11].push_back({7, 4});
    g[11].push_back({12, 13});

    g[12].push_back({7, 3});
    g[12].push_back({8, 5});
    g[12].push_back({11, 10});
    g[12].push_back({13, 14});

    g[13].push_back({8, 4});
    g[13].push_back({12, 11});

    g[14].push_back({9, 5});
    g[14].push_back({13, 12});


    FOR(i, 15){
        cin >> nums[i];
    }


    cout << dp(nums);


}

