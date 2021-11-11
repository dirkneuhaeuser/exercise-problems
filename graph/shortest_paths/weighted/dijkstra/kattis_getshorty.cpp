#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef pair<int, ld> pid;
typedef pair<ld, ld> pdi;
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

vector<ld> faster_dijkstra(int start, vector<vector<pid>> al){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = al.size();
    vector<ld> dist(al.size(), 0);
    dist[start] = 1;
    set<pdi> pq;
    FOR(i, n) pq.emplace(dist[i], i);
    while(pq.size()){
        auto [cost, cur] = *(prev(pq.end())); // intotal O(V * log(V))
        //cout << cur << " " << cost <<endl;
        pq.erase(prev(pq.end()));
        //cout << cur << " " << cost <<endl;
        for(auto [next, w]: al[cur]){
            if(dist[cur] * w <= dist[next]) continue;
            pq.erase(pq.find({dist[next], next})); // O(E * log(V));
            dist[next] = dist[cur] * w;
            pq.emplace(dist[next], next);

        }
    }
    return dist;
}




void solve() 
{
    int n, m; 
    while(cin >> n >>m){
        if(n == 0 && m == 0)break;
        vector<vector<pid>> AL(n, vector<pid>());
        FOR(j, m){
            int a, b; cin >> a >> b;
            ld f; cin >> f;
            AL[a].push_back({b, f});
            AL[b].push_back({a, f});
        }
        vector<ld> dis = faster_dijkstra(0, AL);
        cout << setprecision(4) << fixed << dis.back() << endl;
        //dbg(dis);
    }

}

