#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
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
    // Unweigted SSSP: basic level bfs. However, here at each level we need to prefer the lower cost variant. 
    // Or other way: Of all possible bfs spanning trees, take the minimum cost version
    int n, m; cin >> n >> m;
    unordered_map<string, int> lang2idx;
    int idx = 0;
    lang2idx["English"] = idx++;
    vector<int> targets;
    FOR(i, n){
        string s; cin >> s;
        if(lang2idx.count(s) == 0){
            lang2idx[s] = idx++;
        }
        targets.push_back(lang2idx[s]);
    }
    vector<vector<pii>> AL(n+1, vector<pii>());
    FOR(i, m){
        string s1, s2;
        cin >> s1 >> s2;
        int cost; cin >> cost;
        if(lang2idx.count(s1) == 0){
            lang2idx[s1] = idx++;
        }
        if(lang2idx.count(s2) == 0){
            lang2idx[s2] = idx++;
        }
        int idx1=lang2idx[s1];
        int idx2=lang2idx[s2];
        AL[lang2idx[s1]].emplace_back(lang2idx[s2], cost);
        AL[lang2idx[s2]].emplace_back(lang2idx[s1], cost);
    }
    vector<int> costs(n+1, INF);
    costs[0] = 0;
    vector<int>q;
    q.push_back(0);
    while(q.size()){
        vector<int> updatedCosts(n+1, INF);
        for(auto cur: q){
            for(auto [next, costNext]: AL[cur]){
                if(costs[next]==INF){
                    updatedCosts[next] = min(updatedCosts[next], costNext); // when the same shortest path, prefer lower cost
                }
            }
        }
        q.clear();
        for(int i =0; i<n+1; ++i){
            if(updatedCosts[i] < INF){
                costs[i] = updatedCosts[i];
                q.push_back(i);
            }
        }
    }
    int ret = 0;
    for(int i=0; i<n+1; ++i){
        if(costs[i] == INF){
            cout <<"Impossible";
            return;
        }
        ret += costs[i];
    }
    cout  << ret;


}

