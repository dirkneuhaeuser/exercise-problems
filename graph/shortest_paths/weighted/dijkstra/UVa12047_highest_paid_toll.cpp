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
const ll INF = 1ll<<61;


void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/output.txt", "w", stdout); 
    #endif 
    
    int t=1; 
    cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

vector<ll> faster_dijkstra(int start, vector<vector<pii>> al){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = al.size();
    vector<ll> dist(al.size(), INF);
    dist[start] = 0;
    set<pll> pq;
    FOR(i, n) pq.emplace(dist[i], i);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [next, w]: al[cur]){
            if(dist[cur] + w >= dist[next]) continue;
            pq.erase(pq.find({dist[next], next})); // O(E * log(V));
            dist[next] = dist[cur] + w;
            pq.emplace(dist[next], next);
        }
    }
    return dist;
}



void solve() 
{
    // Weighted SSSP. To see if an edge is part of a path which cost in total no more than p, we can perform dijkstra from left and from right.
    // For each edge a->b we have now the lowest cost to go to s->a and b->t. Now simply check if this added up plus the weight is still smaller than p.
    int n, m, s, t, p;
    cin >> n >> m >> s >> t >> p;
    s--; t--;
    vector<vector<pii>> AL(n);
    vector<vector<pii>> ALRev(n);
    FOR(j, m){
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        AL[a].push_back({b, c});
        ALRev[b].push_back({a, c});
    }
    vector<ll> d1 = faster_dijkstra(s, AL);
    vector<ll> d2 = faster_dijkstra(t, ALRev);
    int ret = -1;
    FOR(i, n){
        for(auto [next, w]: AL[i]){
            if(d1[i] + w + d2[next] <= p){
                ret = max(ret, w);
            }
        }
    }
    cout << ret;
    



}

