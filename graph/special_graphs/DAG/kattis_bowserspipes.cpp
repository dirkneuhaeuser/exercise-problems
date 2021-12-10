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

const int maxN = 100'001;
int memo[maxN];
pii memoRev[maxN];
pii dpRev(int cur, vector<vi> &AL){ // from coin room it gets you {minDis, room}, which we try to minimise
    auto [ans, pipe] = memoRev[cur];
    if(ans != -1) return memoRev[cur];
    if(AL[cur].size() == 0) return memoRev[cur]= {0, cur};
    pii ret = {INF, -1};
    for(int next: AL[cur]){
        pii pot = dpRev(next, AL);
        pot.first+=1;
        ret = min(ret, pot);
    }
    return memoRev[cur] = ret;
    
}

int dp(int cur, vector<vi> &AL){ // gets the coin Room
    int &ans = memo[cur];
    if(ans != -1) return ans;
    if(AL[cur].size() == 0) return ans = cur;
    for(int next: AL[cur]){
        return ans = dp(next, AL);
    }
    assert(false);
    return ans = -1;
    
}



void solve() 
{
    // Graph is DAG, so DP seems obvious. First DP to get us the the coin room and then a reversed DP to get us the best pipe to jump into from the coin room.
    // Note: Here only these elements are pipes, which have in-degree == 0 (a bit confusing)
    int n; cin >> n;
    vi nums(n);
    FOR(i, n) cin >> nums[i];
    vector<vi> ALRev(n), AL(n);
    FOR(i, n){
        if(nums[i] != -1){
            ALRev[nums[i]].push_back(i);
            AL[i].push_back(nums[i]);
        }
    }
    memset(memo, -1, sizeof memo);
    FOR(i, n){
        memoRev[i] = {-1, -1};
    }
    int q; cin >> q;
    FOR(i, q){
        int num; cin >> num;
        int coinRoom = dp(num, AL);
        pii bestPipe = dpRev(goal, ALRev);
        cout << bestPipe.second <<endl;
    }


}

