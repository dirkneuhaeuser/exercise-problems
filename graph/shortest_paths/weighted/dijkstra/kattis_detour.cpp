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

vector<int> faster_dijkstra(int start, vector<vector<pll>> al, vector<int> &par){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    int n = al.size();
    vector<int> dist(al.size(), INF);
    dist[start] = 0;
    set<pii> pq;
    FOR(i, n) pq.emplace(dist[i], i);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [next, w]: al[cur]){
            if(dist[cur] + w >= dist[next]) continue;
            pq.erase(pq.find({dist[next], next})); // O(E * log(V));
            par[next] = cur;
            dist[next] = dist[cur] + w;
            pq.emplace(dist[next], next);

        }
    }
    return dist;
}
vector<bool> visited;
void dfs(int cur, vector<vector<pll>> &AL, vector<int> &fb, vector<int> &curPath, vector<int> &ans){
    visited[cur] = true;
    curPath.push_back(cur);
    if(cur == 1){
        ans = curPath;
        return;
    }
    for(auto [next, w]: AL[cur]){
        if(fb[cur] == next || visited[next]) continue;
        dfs(next, AL, fb, curPath, ans);
    }
    curPath.pop_back();
}


void solve() 
{
    // Weighted SSSP: From the end node apply dijkstra and record all paths taken. These are fordbidden to use in a normal dfs from start to end.
    //
    // takeaway: 
    // - To check if a certain edge/node is part of any shortest path: Apply Dijkstra twice (from end and from the beginning)
    // - To get an example of the shortest path, use the parent array and backtrack it from the end.
    int n, m;cin >> n >> m;
    vector<vector<pll>> AL(n);
    FOR(j, m){
        int a, b, c; cin >> a >> b >> c;
        AL[a].push_back({b, c});
        AL[b].push_back({a, c});
    }
    vector<int> forbidden(n); FOR(i, n) forbidden[i] = i;
    vector<int> dist = faster_dijkstra(1, AL, forbidden);
    visited.assign(n, false);
    vector<int> curPath, ans;
    dfs(0, AL, forbidden, curPath, ans);
    if(ans.size() == 0){
        cout << "impossible" <<endl;
    }else{
        cout << ans.size();
        for(int next: ans){
            cout << " " << next;
        }
    }


}

