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



vector<int> faster_dijkstra(vector<int> &starts, int addStart, vector<vector<pii>> &AL){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = AL.size();
    vector<int> dist(AL.size(), INF);
    dist[addStart] = 0;
    for(int i: starts) dist[i] = 0;
    set<pii> pq;
    FOR(i, n) pq.emplace(dist[i], i);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [next, w]: AL[cur]){
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
    // Weighted MSSP Problem. As the numnber of nodes and edges are quite low, we can run dijkstra for each node (and also include all the existing stations) and see which node comes with the minimal max. distance
    int f, n; cin >> f >> n;
    vector<int> stations;
    vector<bool> already(n, false);
    FOR(i, f){
        int station; cin >> station;
        station--;
        stations.push_back(station);
        already[station] = true;
    }
    vector<vector<pii>> AL(n);
    string line; getline(cin, line);
    while(getline(cin, line) && line != ""){
        stringstream ss;
        ss << line;
        int a, b, c;
        ss >> a >> b >> c;
        a--; b--;
        AL[a].push_back({b, c});
        AL[b].push_back({a, c});
    }
    int maxIdx = 0;
    int minMaxDistance = INF;
    for(int i=0; i<n; ++i){
        if(already[i]) continue;
        vector<int> dist = faster_dijkstra(stations, i, AL);
        int idx = max_element(dist.begin(), dist.end()) - dist.begin();
        if(dist[idx] < minMaxDistance){
            maxIdx = i;
            minMaxDistance = dist[idx];
        }
    }
    cout  << maxIdx+1 << endl;

}

