#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef pair<int, ld> pid;
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

ld euclid(tiii a, tiii b){
    auto [az, ax, ay] = a;
    auto [bz, bx, by] = b;
    return powl(powl(abs((ld)az - bz), 2) + powl(abs((ld)ax - bx), 2) + powl(abs((ld)ay - by), 2), 0.5);
}


vector<ld> faster_dijkstra(ll start, vector<vector<pid>> &AL, int end, vector<int> &par){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    ll n = AL.size();
    vector<ld> dist(AL.size(), INF);
    dist[start] = 0;
    set<pll> pq;
    pq.emplace(dist[start], start);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V))
        if(cur == end) return dist;
        pq.erase(pq.begin());
        for(auto [next, w]: AL[cur]){
            if(dist[cur] + w >= dist[next]) continue;
            auto it = pq.find({dist[next], next});
            if(it != pq.end()){
                pq.erase(it); // O(E * log(V));
            }
            par[next] = cur;
            dist[next] = dist[cur] + w;
            pq.emplace(dist[next], next);

        }
    }
    return dist;
}


void solve() 
{
    // Basic weighted SSSP with Reconstruction of a single shortest path
    int n, m; cin >> n >> m;
    vector<tiii> coords;
    FOR(i, n){
        int a, b, c; cin >> a >> b >> c;
        a *= 5;
        coords.push_back({a, b, c});
    }
    vector<vector<pid>> AL(n);
    FOR(j, m){
        int a, b;
        string type;
        cin >> a >> b >> type;
        if(type == "walking" || type == "stairs"){
            ld w = euclid(coords[a], coords[b]);
            AL[a].push_back({b, w});
            AL[b].push_back({a, w});
        }
        if(type == "lift"){
            AL[a].push_back({b, 1});
            AL[b].push_back({a, 1});
        }
        if(type == "escalator"){
            ld w = euclid(coords[a], coords[b]);
            AL[a].push_back({b, 1});
            AL[b].push_back({a, 3*w});
        }
    }
    int q; cin >> q;
    FOR(i, q){
        int a, b; cin >> a >> b;
        vector<int> par(n); FOR(i, n) par[i] = i;
        vector<ld> dist = faster_dijkstra(a, AL, b, par);
        int cur = b;
        vector<int> route;
        while(true){
            route.push_back(cur);
            if(cur == par[cur]) break;
            cur = par[cur];
        }
        for(int i = route.size()-1; i>=0; --i){
            cout << route[i] << " ";
        }
        cout << endl;

    }



}

