#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
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

int waitTime(int cur, int next, int curCost, int w, vector<vi> &timing){
    if(timing[cur][next] == -1) return 0;
    if(curCost < timing[cur][next]) return 0;
    if(curCost > timing[cur][next] + w) return 0;
    return timing[cur][next] + w-curCost;
}

vector<int> faster_dijkstra(int start, int startTime, vector<vector<pii>> al, vector<vi> &timing){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = al.size();
    vector<int> dist(al.size(), INF);
    dist[start] = startTime;
    set<pii> pq;
    FOR(i, n) pq.emplace(dist[i], i);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [next, w]: al[cur]){
            int wt = waitTime(cur, next, cost, w, timing);
            if(dist[cur] + w + wt >= dist[next]) continue;
            pq.erase(pq.find({dist[next], next})); // O(E * log(V));
            dist[next] = dist[cur] + w + wt;
            pq.emplace(dist[next], next);

        }
    }
    return dist;
}



void solve() 
{
    // Basic weighted SSSDSP. Dijsktra + extra waiting time at each node
    int n, m; cin >> n >> m;
    int startLuke, endLuke, diff, G; cin >> startLuke >> endLuke >> diff >> G;
    startLuke--;
    endLuke--;
    vector<int> route;
    FOR(i, G){
        int c; cin >> c;
        c--;
        route.push_back(c);
    }
    vector<vector<pii>> AL(n, vector<pii>());
    FOR(i, m){
        int a, b, c; cin >> a >> b >>c;
        a--; b--;
        AL[a].push_back({b, c});
        AL[b].push_back({a, c});
    }
    vi timingGeorge(n, -1);
    vector<vector<int>> timingG(n, vector<int>(n, -1));
    FOR(i, G){
        int cur =route[i];
        if(i > 0){
            int prev =route[i-1];
            for(auto[next, w]: AL[prev]){
                if(next == cur){
                    timingG[prev][next] = timingGeorge[prev];
                    timingG[next][prev] = timingGeorge[prev];
                    timingGeorge[cur] = timingGeorge[prev] + w;
                    break;
                }
            }

        }else{
            timingGeorge[cur] = 0;
        }
    }
    vector<int> dis = faster_dijkstra(startLuke, diff, AL, timingG);
    cout << dis[endLuke]-diff;



}

