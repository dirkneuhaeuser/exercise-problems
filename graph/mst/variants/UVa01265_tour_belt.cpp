#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef tuple<int, int, int> tiii;
typedef pair<int, int> pii;
typedef pair<int, long double> pid;
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
    while(t--) 
    { 
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
class DJS{
public:
    vector<int> rank, par, minW, updated;
    int forrests;
    DJS(int n){
        par = vector<int>(n, 0);
        for(int i=0; i<n; ++i)par[i] = i;
        forrests = n;
        rank.assign(n, 1);
        minW.assign(n, INF);
        updated.assign(n, 0);
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
        minW[px] = min(minW[px], minW[py]);
        par[py] = px;
        rank[px]+=rank[py];
        return true;
    }
};

void solve() 
{
    // Advanced variant of maximum spanntree. Sort edges in decreasing order. In DJU save minimum inside-edge weight over all edges already connected to same tree at parents side.
    // 1. Before adding new eges, go through the DJU and check for all parents, which have a higher minimum inside-edge and add its rank to the answer and save that it has been used already (djs.updated[j]  =0);
    // 2. When adding an edges and connecting two trees mark it as updated and make another O(m) loop and check for other edges inbetween two vetexes of the same tree and update the parent minimum inside-edge accordingly. 
    int n, m; cin >> n >> m;
    vector<tiii> edges;
    FOR(i, m){
        int a, b, c; cin >> a >> b >> c;
        a--;
        b--;
        edges.push_back({c, a, b});
    }
    sort(edges.rbegin(), edges.rend());
    DJS djs(n);
    int ret = 0;
    vector<bool> seen(edges.size(), false);
    FOR(i, edges.size()){
        if(seen[i])continue;
        seen[i]= true;
        auto [c, a, b] = edges[i];
        // update ret for all connected components which have a graeter synergy than current
        FOR(j, djs.updated.size()){
            if(djs.par[j] == j && djs.updated[j] == 1 &&  djs.minW[j] > c){
                djs.updated[j] = 0;
                ret += djs.rank[j];
            }
        }
        // add the current synergy and connect the forrests
        if(djs.unionfy(a, b)){
            int parX = djs.getPar(a);
            djs.minW[parX] = min(djs.minW[parX], c);
            djs.updated[parX] = 1;
        }
        // repair the connected components for all smaller edges
        FOR(j, edges.size()){
            if(seen[j]) continue;
            auto [cj, aj, bj] = edges[j];
            if(djs.isSame(aj, bj)){
                int parA = djs.getPar(aj);
                seen[j] = true;
                djs.minW[parA] = min(djs.minW[parA], cj);
            }
        }
    }
    FOR(j, djs.updated.size()){
        if(djs.par[j] == j && djs.updated[j] == 1){
            djs.updated[j] = 0;
            ret += djs.rank[j];
        }
    }
    cout << ret;



}


