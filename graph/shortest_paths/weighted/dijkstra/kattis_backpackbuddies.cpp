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




vector<pii> faster_dijkstra_knight(int start, vector<vector<pii>> al){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = al.size();
    pii ph  = {INF, INF};
    vector<pii> dist(n, ph);
    dist[start].first = 0;
    dist[start].second = 0;
    set<tiii> pq;
    FOR(i, n) pq.emplace(dist[i].first, dist[i].second, i);
    while(pq.size()){
        auto [costD,costH, cur] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [next, w]: al[cur]){
            int d = costD;
            int h = costH;
            h+=w;
            if(h > 12){
                d++;
                h-=12;
            }
            pii nextTime = {d, h};

            if(nextTime >= dist[next]) continue;
            pq.erase(pq.find({dist[next].first, dist[next].second, next})); // O(E * log(V));
            dist[next] = nextTime;
            pq.emplace(dist[next].first, dist[next].second, next);
        }
    }
    return dist;
}

vector<pii> faster_dijkstra_day(int start, vector<vector<pii>> al){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = al.size();
    pii ph  = {INF, INF};
    vector<pii> dist(n, ph);
    dist[start].first = 0;
    dist[start].second = 0;
    set<tiii> pq;
    FOR(i, n) pq.emplace(dist[i].first, dist[i].second, i);
    while(pq.size()){
        auto [costD,costH, cur] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [next, w]: al[cur]){
            //cout << cur << " -> " << next << endl;
            int d = costD;
            int h = costH;
            h+=w;
            if(h > 12){
                d++;
                h=w;
            }
            pii nextTime = {d, h};
            if(nextTime >= dist[next]) continue;
            pq.erase(pq.find({dist[next].first, dist[next].second, next})); // O(E * log(V));
            dist[next] = nextTime;
            pq.emplace(dist[next].first, dist[next].second, next);
        }
    }
    return dist;
}


void solve() 
{
    // For both Mr. Day and Mr. Knight do a weighted SSSP (Dijkstra)
    int n,m;cin >> n >>m;
    vector<vector<pii>> AL(n);
    FOR(i, m){
        int a, b, c; cin >> a >> b >> c;
        AL[a].push_back({b, c});
        AL[b].push_back({a, c});
    }
    vector<pii> knight = faster_dijkstra_knight(0, AL);
    vector<pii> day = faster_dijkstra_day(0, AL);
    int timeKnight = knight.back().first * 24 + knight.back().second;
    int timeDay = day.back().first * 24 + day.back().second;
    cout <<  timeDay - timeKnight;



}

