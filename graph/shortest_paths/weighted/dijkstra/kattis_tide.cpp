#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<ld, int, int> tdii;
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
    int count = 1;
    while(t--) 
    { 
        cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

bool canGo(int curFloor, int curCeil, int curWater, int nextFloor, int nextCeil){
    int maxFloor = max(curFloor, max(nextFloor, curWater));
    int minCeil = min(curCeil, nextCeil);
    return maxFloor + 50 <= minCeil;
}
ld timeUntilGo(int curFloor, int curCeil, ld curWater, int nextFloor, int nextCeil){
    if (canGo(curFloor, curCeil, curWater, nextFloor, nextCeil)) return 0;
    int maxFloor = max(curFloor, nextFloor);
    int minCeil = min(curCeil, nextCeil);
    if(maxFloor > minCeil -50) return -1;
    int target = minCeil - 50;
    if(target < 0) return -1;
    ld targetLD = (ld)target;
    if(curWater > targetLD) return ((ld)curWater - target)/10;
    if(curWater <= targetLD) return 0;
    return -1;
}

vector<pii> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
vector<vector<bool>> visited;
void dfs(int iCur, int jCur, vector<vector<pii>> &cells, int water){
    visited[iCur][jCur] = true;
    int n =  cells.size();
    int m =  cells[0].size();
    for(auto [di, dj]: dir){
        int nextI = iCur+di;
        int nextJ = jCur+dj;
        if(nextI < 0 || nextJ < 0 || nextI >=n || nextJ >= m) continue;
        if(visited[nextI][nextJ]) continue;
        auto [curCeil, curFloor] = cells[iCur][jCur];
        auto [nextCeil, nextFloor] = cells[nextI][nextJ];
        if(!canGo(curFloor, curCeil, water, nextFloor, nextCeil)) continue;
        dfs(nextI, nextJ, cells, water);
    }
}


vector<vector<ld>> faster_dijkstra(vector<pii> &starts, vector<vector<pii>> &cells, int water){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = cells.size();
    int m = cells[0].size();
    vector<vector<ld>> dist(n, vector<ld>(m, INF));
    set<tdii> pq;
    for(auto [i, j]: starts){
        dist[i][j] = 0;
        pq.emplace(0, i, j);
    }
    while(pq.size()){
        auto [cost, i, j] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [di, dj]: dir){
            int nextI = i+di;
            int nextJ = j+dj;
            if(nextI < 0 || nextJ < 0 || nextI >=n || nextJ >= m) continue;
            ld waterLevel = (ld)water  - 10*cost;
            auto [curCeil, curFloor] = cells[i][j];
            auto [nextCeil, nextFloor] = cells[nextI][nextJ];
            ld timeToWait = timeUntilGo(curFloor, curCeil, waterLevel, nextFloor, nextCeil);
            if(timeToWait +0.001 < 0) continue;
            ld waterLevelNext = waterLevel - timeToWait*10;
            ld nextTime;
            if(waterLevelNext - curFloor>= 20){
                nextTime = cost + timeToWait + 1; // move with kayak
            }else{
                nextTime = cost + timeToWait + 10;
            }

            if(dist[nextI][nextJ] <= nextTime) continue;
            auto it = pq.find({dist[nextI][nextJ], nextI, nextJ});
            if(it != pq.end()){
                pq.erase(it); // O(E * log(V));
            }
            dist[nextI][nextJ] = nextTime;
            pq.emplace(dist[nextI][nextJ], nextI, nextJ);
        }
    }
    return dist;
}




void solve() 
{
    // Weighted MSSDSP Problem. Major Problem are the many restrictions. When to go from one to another field -> new method
    // Then, another takeaway is, that the speed you can go to next field depends on the waterlevel, which depends on the time/cost. These can be checked during dijkstra:
    // Note this only works as the kayak speed bonus is kind of monoton (lower time, will result to higher/equal speed)
    int water, n, m; cin >> water >> n >> m;
    vector<vector<pii>> cells(n, vector<pii>(m)); // height & floor
    FOR(i, n){
        FOR(j, m){
            int a; cin >> a;
            cells[i][j].first = a;
        }
    }
    FOR(i, n){
        FOR(j, m){
            int a; cin >> a;
            cells[i][j].second = a;
        }
    }
    visited.assign(n, vector<bool>(m, false));
    dfs(0, 0,cells, water);
    vector<pii> starts;
    FOR(i, n){
        FOR(j, m){
            if(visited[i][j]) starts.push_back({i, j});
        }
    }
    vector<vector<ld>> dist = faster_dijkstra(starts, cells, water);
    cout << setprecision(10) << fixed << dist[n-1][m-1];
}

