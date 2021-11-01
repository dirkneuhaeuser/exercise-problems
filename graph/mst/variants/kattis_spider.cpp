#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef tuple<long long, int, int> tiii;
typedef pair<int, int> pii;
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
class DJS{
public:
    vector<int> rank, par;
    int forrests;
    DJS(int n){
        par = vector<int>(n, 0);
        for(int i=0; i<n; ++i)par[i] = i;
        forrests = n;
        rank.assign(n, 0);
    }
    int getPar(int x){
        if(par[x] == x) return x;
        return par[x] = getPar(par[x]);
    }
    bool isSame(int x, int y){
        return getPar(x) == getPar(y);
    }
    bool unionfy(int x, int y){
        if(isSame(x, y)) return false;
        forrests--;
        int px = getPar(x), py = getPar(y);
        if(rank[px] < rank[py]){
            swap(px, py);
        }
        par[py] = px;
        if(rank[px] == rank[py])  rank[px]++;
        return true;
    }
};
vector<vector<int>> AM;
vector<bool> seen;
void dfs(int cur, int start, vector<vector<pii>>&AL, int maxDis){
    seen[cur] = true;
    AM[start][cur] = maxDis;
    for(auto [next, w]: AL[cur]){
        if(seen[next]==false){
            dfs(next, start, AL, max(maxDis, w));
        }
    }
}



void solve() 
{
    // One large edge rest small (part of the normal MST). Problem you cannot just try all "large" edges and then build the MST on top of it because M < 1KK;
    // Better: 
    // 1. Create MST O(E log E)
    // 2. DFS starting from each node inside the MST to get the max distance for each pair of nodes O(V^2), possible bc its a tree
    // 3. Go trough all edges again and see subtract the current edge and add the maxEdge insde mst between them O(E)
    int n, m; 
    while(cin >> n >> m){
        vector<tiii> edges;
        FOR(i, m){
            int a, b, c; cin >> a >> b >> c;
            a--;
            b--;
            edges.push_back({c, a, b});

        }
        sort(edges.begin(), edges.end());
        DJS djs(n);
        ll total = 0;
        vector<vector<pii>> AL(n, vector<pii>());
        FOR(i, m){
            auto [c, a, b] = edges[i];
            if(djs.unionfy(a, b)){
                total+=c;
                AL[a].push_back({b, c});
                AL[b].push_back({a, c});
            }
        }
        if(djs.forrests > 1){
            cout << "disconnected" << endl;
            continue;
        }
        AM.assign(n, vector<int>(n, 0));
        FOR(i, n){
            seen.assign(n, false);
            dfs(i, i, AL, 0);
        }
        ll ans = total;
        FOR(i, m){
            auto [c, a, b] = edges[i];
            ans = min(ans, total - AM[a][b] - c);
        }
        cout << ans << endl;
    }

}

