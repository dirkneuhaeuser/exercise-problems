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

vector<int> dist;
int faster_dijkstra(int start, vector<vector<pii>> &AL, int k){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int notSafeAnymore = 0;
    int n = AL.size();
    if(dist[start] >= k){
        notSafeAnymore++;
    }
    dist[start] = 0;
    set<pii> pq;
    pq.emplace(dist[start], start);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V))
        if(cost >= k) break;
        pq.erase(pq.begin());
        for(auto [next, w]: AL[cur]){
            if(dist[cur] + w >= dist[next]) continue;
            auto it = pq.find({dist[next], next});
            if(it != pq.end()){
                pq.erase(pq.find({dist[next], next})); // O(E * log(V));
            }
            if(dist[next] >= k && (dist[cur] + w) < k) notSafeAnymore++;
            dist[next] = dist[cur] + w;
            pq.emplace(dist[next], next);

        }
    }
    return notSafeAnymore;
}


void solve() 
{
    // Weighted MSSP Problem. For each added Alien station, just apply Dijkstra(with multiple sources) once more and also keep the dist-array globally
    int n, m, aliens, k; 
    while(cin >> n >> m >> aliens >> k){
        if(n == 0)break;
        vector<vector<pii>> AL(n);
        FOR(i, m){
            int a, b, c; cin >> a >> b >> c;
            a--; b--;
            AL[a].push_back({b, c});
            AL[b].push_back({a, c});
        }
        dist.assign(n, INF);
        int safeTowns = n;
        FOR(i, aliens){
            int t; cin >> t; t--;
            int inReachNow = faster_dijkstra(t, AL, k);
            safeTowns -= inReachNow;
            cout << safeTowns << endl;
        }
        cout << endl;
    }


}

