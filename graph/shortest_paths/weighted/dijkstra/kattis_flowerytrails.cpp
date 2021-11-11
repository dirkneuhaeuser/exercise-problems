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

void dfs(int cur, vector<vector<pii>> &AL, vector<int> &dis, int &ret){
    //cout << cur << endl;
    int n = AL.size();
    if(cur == n-1) {
        ret += dis[n-1];
        cout << cur << endl;
    }else{
        for(auto [next, w]: AL[cur]){
            if(dis[next] == dis[cur] + w){
                dfs(next, AL, dis, ret);
            }
        }
    }
}

vector<int> dijkstra(int start, vector<vector<pii>> al){ // O(E * log(V))
    // SSSP idea: Always take the next node with minimial distance
    // once taken a node with minimial distance, you can't correct it, as a detour over others will make it worse
    // al is weighted!
    vector<int> dist(al.size(), INF);
    priority_queue<pii, vector<pii>, ::greater<pii>> nodes;
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
    // Weighted SSSDSP. 
    // To know whether a node is part of the the shortest path:
    //      run dijstra twice from end and start, then the destFromStart + destFromEnd == destTowardsDest 
    // To check if en edge is part of the graph:
    //      Check if both nodes are part of the shortest path + check if the weight difference is matching
    int n, m; cin >> n >> m;
    vector<vector<pii>> AL(n, vector<pii>());
    vector<vector<pii>> ALNew(n, vector<pii>());
    priority_queue<pii, vector<pii>, greater<pii>>pq;
    FOR(j, m){
        int a, b,  c; cin >> a >> b >> c;
        AL[a].push_back({b, c});
        AL[b].push_back({a, c});
    }

    vector<int> disNormal = dijkstra(0, AL);
    vector<int> disBack = dijkstra(n-1, AL);
    int disTotal = disNormal[n-1];
    ll ret = 0;
    FOR(i, n){
        if(disNormal[i] + disBack[i] != disTotal) continue;
        for(auto [j, w]: AL[i]){
            if(disNormal[j] + disBack[j] == disTotal && disNormal[i] + w == disNormal[j] ){
                ret += w;
            }
        }
    }
    
    cout << 2*ret;




}

