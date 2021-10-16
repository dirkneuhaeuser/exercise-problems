#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long, long> pll;
typedef pair<int, int> pii;
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



void solve() 
{
    // Advanced Topological Sort: To minimise the maximum meeting time, do the topological sorting from behind and always add the current `smallest` available meeting. 
    // The `still big offset` will therefore be added to the smallest possible values.
    int n; cin >> n;
    vector<int> mostExpDependency(n, 0), waitTime(n, 0), inDegree(n, 0);
    vector<vector<int>> AL(n, vector<int>());
    
    FOR(i, n){
        int w; cin >> w;
        waitTime[i] = w;
        int m; cin >> m;
        FOR(j, m){
            int b; cin >> b;
            b--;
            AL[i].push_back(b);
            inDegree[b]++;

        }
    }
    priority_queue<pii, vector<pii>, ::greater<pii>> pq;
    FOR(i, n){
        if(inDegree[i] == 0){
            pq.push({waitTime[i], i});
        }
    }
    int offset = n-1;
    int ret = 0;
    while(pq.size()){
        auto [price, cur] = pq.top(); pq.pop();
        ret = max(ret, waitTime[cur] + offset);
        for(int next: AL[cur]){
            inDegree[next]--;
            if(inDegree[next] == 0){
                pq.push({waitTime[next], next});
            }
        }
        offset--;
    }
    cout << ret;




}

