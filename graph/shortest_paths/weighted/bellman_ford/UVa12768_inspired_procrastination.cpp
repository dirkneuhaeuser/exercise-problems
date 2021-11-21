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

// BELOW FOR NEGATIVE CYCLES
vector<int> bellmann_ford(int start, vector<vector<pii>> &AL){ // O(V^3)
    // Get the distance from start node to all other nodes and works with negative cycles (no infinite queue)
    // Stops after n iterations, if afterwars still relaxations are possible -> negative cycle
    // Limit ~ V<450
    int n = AL.size();
    vector<int> dist = vector<int>(n, INF);
    dist[start] = 0;
    for(int i=0; i<n; ++i){ // O(V^3)
        for(int v=0; v<n; ++v){
            if(dist[v] != INF){
                for(auto [next, w]: AL[v]){
                    dist[next] = min(dist[next], dist[v] + w);
                }
            }
        }
    }
    return dist;
}

vector<bool> NINFS;
void dfsGetNINF(int cur, vector<vector<pii>> &AL){
    NINFS[cur] = true;
    for(auto [next,w]: AL[cur]){
        if(NINFS[next] == 0){
            dfsGetNINF(next, AL);
        }
    }
}

vector<bool> getNegativeCycleStarts(int start, vector<int> &dist, vector<vector<pii>> &AL){
    // Gets nodes which are part of a negtive cycle. BUT is does not return ALL nodes of this cycle. Do a dfs to get all nodes after this being detected.
    int n = AL.size();
    vector<bool> isNINF = vector<bool>(n, false);
    for(int v=0; v<n; ++v){
        if(dist[v] != INF){
            for(auto [next, w]: AL[v]){
                if(dist[next] > dist[v] + w){
                    dist[next] = dist[v] + w;
                    isNINF[next] = true;
                    isNINF[v] = true;
                }
            }
        }
    }
    return isNINF;
}

// vector<int> dist = bellmann_ford(0, AL);
// vector<bool> starts = getNegativeCycleStarts(0, dist, AL);
// NINFS.assign(n, false);
// FOR(i, n){
//     if(starts[i] && NINFS[i] == 0){
//         dfsGetNINF(i, AL);
//     }
// }
// // now if not NINFS[i] == true, dist[i] has the exact distance from 0 to i. Else we can say its negative INF.


void solve() 
{
    // If we take the weights as negative weights, then we want to minimize the distance from node 0 -> this is a normal SSSP problem. However,
    // there could be negative cycles. Therefore, instead of dijkstra, take bellmann_ford, to detect them.
    int n, m; 
    while(cin >> n >> m){
        if(n == 0 && m == 0) break;
        vector<vector<pii>> AL(n);
        FOR(j, m){
            int a, b, c; cin >> a >> b >> c;
            a--; b--;
            c = -c;
            AL[a].push_back({b, c});
        }
        vector<int> dist = bellmann_ford(0, AL);
        vector<bool> isStartCycle = getNegativeCycleStarts(0, dist, AL);
        int ret = 0;
        FOR(i, n){
            if(dist[i] == INF) continue;
            ret = max(-dist[i] ,ret);
            if(isStartCycle[i]) ret = INF;
        }
        if(ret == INF){
            cout << "Unlimited!" << endl;
        }else{
            cout << ret << endl;
        }

    }


}

