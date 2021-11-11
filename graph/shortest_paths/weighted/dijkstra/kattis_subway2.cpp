#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef pair<int, ld> pid;
typedef pair<ld, int> pdi;
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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

int idx;
map<pii, int> coord2idx;
vector<pii> idx2coord;
int getIdx(int a, int b){
    if(coord2idx.count({a, b}) == 0){
        coord2idx[{a, b}] = idx++;
        idx2coord.push_back({a, b});
    }
    return coord2idx[{a, b}];
}

ld euclid(int ai, int aj, int bi, int bj){
    return powl(powl((ld)abs(ai-bi), 2) + powl((ld)abs(aj-bj), 2), 0.5);
}


vector<ld> faster_dijkstra(int start, vector<vector<pid>> al){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = al.size();
    vector<ld> dist(al.size(), (ld)INF);
    dist[start] = 0;
    set<pdi> pq;
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
    // Weighted SSSDSP: Basic Dijkstra, with some tedious distances:
    // add each subway station as a node (integer)
    // between stations of the same line, calcuate the ld time to travel
    // for the remaining, add all O(n^2) distances by walk (no problem, if we have more edges between the same two nodes, we take the lowest)
    idx = 0;
    int a, b, c , d; cin >> a >> b >> c >> d;
    getIdx(a, b);
    getIdx(c, d);
    ll prevAi=-1, prevAj=-1, curAi=-1, curAj=-1;
    vector<vector<pid>> AL(2, vector<pid>());
    ld meterProHSubway = (ld)40000;
    ld meterProHMe = (ld)10000;

    while(cin >> curAi >> curAj){
        if(curAi == -1 && curAj == -1){
            prevAi = -1;
            prevAj = -1;
            curAi = -1;
            curAj = -1;
        }else{
            int cur = getIdx(curAi, curAj);
            if(AL.size() <= cur){
                AL.push_back({});
            }
            if(prevAi != -1){
                int prev = getIdx(prevAi, prevAj);
                ld dist = euclid(prevAi, prevAj, curAi, curAj);
                AL[prev].push_back({cur, dist*60/meterProHSubway});
                AL[cur].push_back({prev, dist*60/meterProHSubway});
            }
            prevAi = curAi;
            prevAj = curAj;
        }
    }
    int n = AL.size();
    FOR(i, n){
        auto [ai, aj] = idx2coord[i];
        for(int j=i+1; j<n; ++j){
            auto [bi, bj] = idx2coord[j];
            ld dist = euclid(ai, aj, bi, bj);
            ld speed = meterProHMe;
            ld needed = dist/speed;
            AL[j].push_back({i, dist*60/meterProHMe});
            AL[i].push_back({j, dist*60/meterProHMe});
        }
    }
    vector<ld>dist = faster_dijkstra(0, AL);
    ll timeNeededInt = (dist[1] + 0.5);
    cout << timeNeededInt << endl;




}

