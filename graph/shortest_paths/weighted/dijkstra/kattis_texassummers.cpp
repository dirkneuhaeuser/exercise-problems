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
ld euclid(int ai, int aj, int bi, int bj){
    ld dis = powl((ld)abs(ai-bi), 2)  + powl((ld)abs(aj-bj), 2); // not taking the squre root as stated in problem?
    return dis;
}
vector<int> faster_dijkstra(int start, vector<vector<pii>> al, vector<int> &pred){ // O(E * log(V))
    // SSSP idea: Always take the next node with minimial distance
    // once taken a node with minimial distance, you can't correct it, as a detour over others will make it worse
    // al is weighted!
    int n = al.size();
    vector<int> dist(al.size(), INF);
    dist[start] = 0;
    set<pii> pq;
    FOR(i, n) pq.emplace(dist[i], i);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V^2))
        pq.erase(pq.begin());
        for(auto [next, w]: al[cur]){
            if(dist[cur] + w >= dist[next]) continue;
            pq.erase(pq.find({dist[next], next}));
            dist[next] = dist[cur] + w;
            pred[next] = cur;
            pq.emplace(dist[next], next);

        }
    }
    return dist;
}

void solve() 
{
    // Weighted SSSP with Reconstruction (use parent array).
    // Note: as E == 2500^2, the slow implementation of dijkstra won't work. Use the set vairant. This is ok, because weights are not negative.
    int n; cin >> n;
    vector<pii> nodes;
    n+=2;
    FOR(i, n){
        int a, b; cin >> a >> b;
        nodes.emplace_back(a, b);
    }
    vector<vector<pii>> AL(n, vector<pii>());
    FOR(i, n){
        auto [ai, aj] = nodes[i];
        for(int j=i+1; j<n; ++j){
            auto [bi, bj] = nodes[j];
            ld d = euclid(ai, aj, bi, bj);
            AL[i].push_back({j, d});
            AL[j].push_back({i, d});
        }
    }
    vector<int> prev(n);
    FOR(i, n) prev[i] = i;
    vector<int> dis = faster_dijkstra(n-2, AL, prev);
    int cur = n-1;
    vector<int> ret;
    while(prev[cur] != cur){
        cur = prev[cur];
        if(cur != n-2){
            ret.push_back(cur);
        }
    }
    if(ret.size() == 0){
        cout << "-";
    }else{
        for(int i=ret.size()-1; i>=0; --i){
            cout << ret[i] << endl;
        }
    }

}

