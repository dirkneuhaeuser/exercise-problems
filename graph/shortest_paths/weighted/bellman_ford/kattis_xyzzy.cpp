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
    dist[start] = -100;
    for(int i=0; i<n; ++i){ // O(V^3)
        for(int v=0; v<n; ++v){
            if(dist[v] != INF){
                for(auto [next, w]: AL[v]){
                    if(dist[v] + w < 0){
                        dist[next] = min(dist[next], dist[v] + w);
                    }
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
    int n = AL.size();
    vector<bool> isNINF = vector<bool>(n, false);
    for(int v=0; v<n; ++v){
        if(dist[v] != INF){
            for(auto [next, w]: AL[v]){
                if(dist[next] > dist[v] + w && dist[v] + w < 0){
                    dist[next] = dist[v] + w;
                    isNINF[next] = true;
                    isNINF[v] = true;
                }
            }
        }
    }
    return isNINF;
}


void solve() 
{
    // Bellmann Ford SSSP with negative cycles. 
    // 1. The energy level of each room can be considered the weight towards the edge
    // 2. We need to reverse the energy, as bellmann ford minimises
    // 3. If after v iterations, we can reach the nth node, we are done
    // 4. Else: If we can still relax, we have found a negative cycle and each element after this is also reachable.
    // Very important: Make an extra check each time you traverse to another node, s.t. dist[v] + w < 0
    // even if the next is a negative cycle, we need to ensure to be always over 0
    int n; 
    while(cin >> n && n!=-1){
        if(n == 0){
            cout << "winnable" << endl;
            continue;
        }
        vector<int> energyNeed(n);
        vector<vector<pii>> AL(n);
        FOR(i, n){
            int energy; cin >> energy;
            energyNeed[i] = -energy;
            int m; cin >> m;
            FOR(j, m){
                int adj; cin >> adj;
                adj--;
                AL[i].push_back({adj, -1});
            }
        }
        FOR(i, n){
            for(int j=0; j<AL[i].size(); ++j){
                AL[i][j].second = energyNeed[AL[i][j].first];
            }
        }

        vector<int> dist = bellmann_ford(0, AL);
        if(dist[n-1] < 0){
            cout <<  "winnable" << endl;
            continue;
        }
        vector<bool> cycleStarts = getNegativeCycleStarts(0, dist, AL);
        NINFS.assign(n, false);
        FOR(i, n){
            if(cycleStarts[i] && NINFS[i] == 0){
                dfsGetNINF(i, AL);
            }
        }
        if(NINFS[n-1]){
            cout <<  "winnable" << endl;
        }else{
            cout <<  "hopeless" << endl;
        }
    }
}

