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
int LSOne(int num){
    return num & (-num);
}

const int maxN = 1<<16;
int memo[maxN];
int dp(int mask, vector<int> nums){
    int n = nums.size();
    int &ans = memo[mask];
    if(ans != -1) return ans;
    if(mask == 0) return ans = 0;
    bool isAtGate = (LSOne(mask) == 1);
    mask^=1;
    if(isAtGate){
        // At the gate, check all 2-er combinations to go to the dorms
        int ret = INF;
        int maskCopy = mask;
        while(maskCopy){
            int firstPerson = LSOne(maskCopy);
            maskCopy^= firstPerson;
            int m = maskCopy;
            while(m){
                int secondPerson = LSOne(m);
                m = m^secondPerson;
                int idx1 = __builtin_ctz(firstPerson);
                int idx2 = __builtin_ctz(secondPerson);
                int maxCost = max(nums[idx1-1], nums[idx2-1]);
                ret = min(ret, maxCost + dp(mask ^ firstPerson ^ secondPerson, nums));

            }
        }
        return ans = ret;
    }else{
        // send the fastest back to the gate
        for(int i=1; i<=n;++i){
            if((mask &(1<<i)) == 0){
                return ans = nums[i-1] + dp(mask^(1<<i), nums);
            }

        }
    }
    assert(false);
    return ans = INF;
}


void solve() 
{
    // Problem is a DAG, and so DP is good here. Use bitset as n<15 + 1 bit for where the robe is -> 64K states. For each state 15*15  steps to compute
    int n; cin >> n;
    vector<int> nums(n);
    FOR(i, n){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    int mask = 0;
    for(int i=0; i<=nums.size(); ++i){
        mask |= (1 << i); // 0 bit set == currently robe at gate. All other bits mean: ith dude is at the gate.
    }
    memset(memo, -1, sizeof memo);
    int ret = dp(mask, nums);
    cout << ret << endl;

}

