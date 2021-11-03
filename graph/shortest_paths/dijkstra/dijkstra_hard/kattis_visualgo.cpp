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
    // A modifed dijsktra to get the total number of shortest paths
    // Note, the graph is a DAG, so simple dp would also be working
    int n, m; scanf("%d %d", &n, &m);
    vector<vector<pii>> AL(n, vector<pii>());
    FOR(i, m){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        AL[a].push_back({b, c});
    }
    int from, to; scanf("%d %d", &from, &to);




    // modified dijkstra
    vector<int> dis(n, INF);
    vector<int> paths(n, 0);
    dis[from] = 0;
    dis[from] = 1;
    priority_queue<vector<int>, vector<vector<int>>, ::greater<vector<int>>>pq;
    pq.push({0, from, 1});
    while(pq.size()){
        vector<int> top = pq.top(); pq.pop();
        int w = top[0];
        int cur = top[1];
        int p = top[2];
        while(pq.size()){
            // try to merge as many paths which go to the current node.
            // Note, this ensures, that we only touch each node once. Afterwards, this weight of the path to cur can only be higher
            if(pq.top()[0] == w && pq.top()[1] == cur){
                vector<int> alsoTake = pq.top(); pq.pop();
                p+=alsoTake[2];
            }else{
                break;
            }
        }
        if(w > dis[cur]) continue;
        if(w <= dis[cur]){
            dis[cur] = w;
            paths[cur] += p;
            for(auto [next, nextW]: AL[cur]){
                if(dis[next] >= dis[cur] + nextW){
                    pq.push({dis[cur] + nextW, next, p});
                }
            }
        }
    }
    printf("%d", paths[to]);


}

