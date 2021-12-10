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
const ll INF = 1ll<<60;


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
vector<ll> dijkstra(int start, vector<vector<pll>> &AL){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHT CYCLES
    ll n = AL.size();
    vector<ll> dist(AL.size(), INF);
    dist[start] = 0;
    set<pll> pq;
    pq.emplace(dist[start], start);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [next, w]: AL[cur]){
            if(dist[cur] + w >= dist[next]) continue;
            auto it = pq.find({dist[next], next});
            if(it != pq.end()){
                pq.erase(it); // O(E * log(V));
            }
            dist[next] = dist[cur] + w;
            pq.emplace(dist[next], next);

        }
    }
    return dist;
}


void solve() 
{
    // Hidden ASAP Problem. Model a new graph where you can only go from repair to repair stop (or home/school).
    // You can obtain this graph by running floyed-warshall ASAP to get the sortest distances between each pair of repair-stops.
    // Now, crate a new graph (in form of an AL) and only add these edges between repair stops which are smaller/equal to d;
    // Follow this by a simple dijkstra and you are good to go.
    //
    //
    // Learned: if numbers are big, also set INF to 1ll << 60
    ll n, m, t, d; cin >> n >> m >> t >> d;
    vector<int> repairs{0, (int)n-1};
    FOR(i, t){
        int r; cin >> r; r--;
        if(r == 0 || r==n-1)continue;
        repairs.push_back(r);
    }
    vector<vector<ll>> AM(n, vector<ll>(n, INF));
    FOR(j, m){
        int a, b, c; cin>> a >> b >> c;
        a--; b--;
        AM[b][a] = AM[a][b] = c;
    }
    // floyed-warshall O(V^3)
    FOR(k, n) FOR(i, n) FOR(j, n){
        AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
    }
    ll ret = INF;
    if(AM[0][n-1] <=d){
        ret = min(ret, AM[0][n-1]);
    }
    // constructing AL O(t^2)
    vector<vector<pll>> AL(repairs.size());
    for(int i=0; i<repairs.size(); ++i){
        for(int j=0; j<repairs.size(); ++j){
            if(i==j)continue;
            if(AM[repairs[i]][repairs[j]] <= d){
                AL[i].push_back({j, AM[repairs[i]][repairs[j]]});
            }
        }
    }
    // dijstra on reduced repair-staion graph: O((t+E)log(t))
    vector<ll> dist = dijkstra(0, AL);
    if(dist[1] == INF){
        cout << "stuck";
    }else{
        cout << dist[1];
    }





}

