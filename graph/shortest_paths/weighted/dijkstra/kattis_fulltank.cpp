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
const ll INF = 1<<30;


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

vector<vector<int>> faster_dijkstra(int start, vector<vector<pii>> &AL, int cap, vector<int> &prices, int end){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = AL.size();
    vector<vector<int>> dist(AL.size(), vector<int>(cap+1, INF));
    dist[start][0] = 0;
    set<tiii> pq;
    pq.emplace(dist[start][0], start, 0);
    while(pq.size()){
        auto [cost, cur, fuel] = *pq.begin(); // intotal O(V * log(V))
        if(cur == end) return dist;
        pq.erase(pq.begin());
        for(auto [next, w]: AL[cur]){
            if(w<= fuel){
                int nextFuel = fuel-w;
                if(dist[cur][fuel]>= dist[next][nextFuel]) continue;
                auto it = pq.find({dist[next][nextFuel], next, nextFuel});
                if(it != pq.end()){
                    pq.erase(it); // O(E * log(V));
                }
                dist[next][nextFuel] = dist[cur][fuel];
                pq.emplace(dist[next][nextFuel], next, nextFuel);
            }
        }
        if(fuel < cap){
            if(dist[cur][fuel] + prices[cur] >= dist[cur][fuel+1]) continue;
            auto it = pq.find({dist[cur][fuel+1], cur, fuel+1});
            if(it != pq.end()){
                pq.erase(it);
            }
            dist[cur][fuel+1] = dist[cur][fuel] + prices[cur];
            pq.emplace(dist[cur][fuel+1], cur, fuel+1);
        }
    }
    return dist;
}



void solve() 
{
    // Weighted SSSDSP Problem. Main Issue: Model the graph that dijkstra can minimize the cost for the fuel. Blow the distance graph to a state-space graph which also includes the fuel capacity at the current node.
    // Most important takeaway: Once you reach your destination, break in order to keep the timelimit
    int n, m; cin >> n >> m;
    vector<int> prices(n);
    FOR(i, n) cin >> prices[i];
    vector<vector<pii>> AL(n);
    FOR(i, m){
        int a, b, c;
        cin >> a >> b >> c;
        AL[a].push_back({b, c});
        AL[b].push_back({a, c});
    }
    int q; cin >> q;
    FOR(qq, q){
        int cap, a, b; cin >> cap >> a >> b;
        // V = 1000*100 = O(100'000)
        // E = 1000*100(fueling) + 10000*100 (next cities) = O(1'000'000)
        // --> Dijkstra -> O(1'000'000 * 16) = O(16KK);
        vector<vector<int>> dis = faster_dijkstra(a, AL, cap, prices, b);
        int ret = INF;
        for(int i=0; i<cap; ++i){
            ret = min(ret, dis[b][i]);
        }
        if(ret == INF){
            cout << "impossible" << endl;
        }else{
            cout << ret << endl;
        }
    }

}



