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


map<int, int> memo;
int dp(int cur, vector<vector<int>> &AL){
    auto it = memo.find(cur);
    if(it != memo.end()) return it->second;
    int ret = 1;
    for(int next: AL[cur]){
         ret = max(ret, 1+dp(next, AL));
    }
    return memo[cur] = ret;
}

void solve() 
{
    // There are only <100 fibs up to 10^18. When jumping from one Fib to another, the underlying graph is a DAG -> use DP to count max Length path..
    int n, m; cin >> n >> m;
    memo.clear();
    vector<ull> fibs{1, 1};
    ull limit = 1000000000000000000ull;
    while(true){
        int s = fibs.size();
        ull next = fibs[s-1] + fibs[s-2];
        if(next > limit) break;
        fibs.push_back(next);
    }
    vector<bool> canStart(n, false);
    vector<bool> isFib(n, false);
    vector<int> heights(n);
    FOR(i, n){
        ull num; cin >> num;
        int idx = lower_bound(fibs.begin(), fibs.end(), num) - fibs.begin();
        if(idx<0 || idx >= fibs.size()){
            heights[i] = -1;
            continue;
        };
        if(fibs[idx] == num){
            heights[i] = idx;
            isFib[i] = true;
        }else{
            heights[i] = -1;
        }
    }
    vector<vector<int>> AL(n);

    FOR(j, m){
        int a, b; cin >> a >> b;
        a--; b--;
        int idxA = heights[a];
        int idxB = heights[b];
        if(idxA == -1 || idxB == -1) continue;
        if(idxA > idxB){
            swap(a, b);
            swap(idxA, idxB);
        }
        if(idxB-idxA == 1){
            AL[a].push_back(b);
        }else if(idxA == idxB && idxA == 0){
            canStart[a] = true;
            canStart[b] = true;
        }else if(idxB == 2 && idxA == 0){
            AL[a].push_back(b);
        }
    }
    int ret = 0;

    // when canStart is set, this node is a one and has a also a predessor 1, so add additional 1
    for(int i=0; i<n; ++i){
        if(canStart[i]) ret = max(ret, 1+dp(i, AL));
    }
    for(int i=0; i<n; ++i){
        if(isFib[i])ret = max(ret, dp(i, AL));
    }
    cout << ret;



}

