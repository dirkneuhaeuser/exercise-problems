#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef tuple<long long, long long, long long> tll;
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
const ll INF = 1ll << 62;


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

vector<vector<pll>> AL;
vector<vector<pll>> ALRev;

vector<ll> dijkstra(ll start, vector<vector<pll>> al){ // O(E * log(V))
    // SSSP idea: Always take the next node with minimial distance
    // once taken a node with minimial distance, you can't correct it, as a detour over others will make it worse
    // al is weighted!
    vector<ll> dist(al.size(), INF);
    priority_queue<pll, vector<pll>, ::greater<pll>> nodes;
    nodes.push({0, start});
    while(nodes.size()){
        auto [d, u] = nodes.top(); nodes.pop(); // intotal O(V * log(V^2))
        if(dist[u] < INF) continue; // you have that node already 
        dist[u] = d;
        for(auto [v, w]: al[u]){
            if(dist[v] == INF){
                nodes.push({d + w, v}); // In total O(E * log(V^2)) -> we can add nodes multiple times, BUT: O(E * log(V^2)) = O(E * 2 * log(V)) = O(E * log(V))
            }
        }
    }
    return dist;
}



void solve() 
{
    // 1. Option: Find articultion point in SSSP DAG (apply dijstra two times from start and from end, then use once more dijstra and go from start to all points where
    // dist[end] == dist[x] + distReversed[x].
    // A node is an articulation point, if after poping it from the queue, there is no other node in the queue
    //
    // 2. Option: Reduce graph to only shortest paths (again two dijkstra)
    // Then on this graph, pretend you have an undirected graph(thats ok, as all possible ways (apart of backwards are shortest paths) and find articulation points

    int n, m; cin >> n >> m;
    AL.assign(n, vector<pll>());
    ALRev.assign(n, vector<pll>());
    FOR(i, m){
        ll a, b;
        ll w; 
        cin >> a >> b >> w;
        AL[a].push_back({b, w});
        ALRev[b].push_back({a, w});
    }
    ll start, end; cin >> start >> end;

    vector<ll> dist = dijkstra(start, AL);
    vector<ll> distRev = dijkstra(end, ALRev);


    priority_queue<pll, vector<pll>, ::greater<pll>> nodes;
    vector<ll> alr(n, false);
    alr[start] = true;
    nodes.push({0, start});
    vector<ll> ret;
    while(nodes.size()){
        auto [d, u] = nodes.top(); nodes.pop(); // intotal O(V * log(V^2))
        if(nodes.size() == 0) ret.push_back(u);
        for(auto [v, w]: AL[u]){
            if(alr[v] == false && dist[end] == dist[v] + distRev[v]){
                alr[v] = true;
                nodes.push({dist[v] + w, v});
            }
        }
    }
    sort(ret.begin(), ret.end());

    FOR(i, ret.size()){
        cout << ret[i];
        if(i < ret.size() -1) cout << " ";
    }
}

