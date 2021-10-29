#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef tuple<long double, int, int> tdii;
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

ld dis(int ax, int ay, int bx, int by){
    int q = pow(abs(ax-bx), 2) + pow(abs(ay-by), 2);
    return powl((ld)q, (ld)0.5);
}

class DJS{
public:
    vector<int> rank, par;
    DJS(int n){
        par = vector<int>(n, 0);
        for(int i=0; i<n; ++i)par[i] = i;
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
        int px = getPar(x), py = getPar(y);
        if(rank[px] < rank[py]){
            swap(px, py);
        }
        par[py] = px;
        if(rank[px] == rank[py])  rank[px]++;
        return true;
    }
};

void solve() 
{
    // basic MST problem
    int n, r; cin >> n >> r;
    vector<pii> cities;
    FOR(i, n){
        int a, b; cin >> a >> b;
        cities.push_back({a, b});

    }
    vector<tdii> edges;
    FOR(i, n){
        auto [ax, ay] = cities[i];
        for(int j=i+1; j<n; ++j){
            auto [bx, by] = cities[j];
            ld d = dis(ax, ay, bx, by);
            edges.push_back({d, i, j});
        }
    }
    sort(edges.begin(), edges.end());
    DJS djs(n);
    int states = 1;
    ld extensionRoad = 0, extensionRail = 0;
    FOR(i, edges.size()){
        auto [c, a, b] = edges[i];
        if(djs.unionfy(a, b)){
            if(c >= r){
                states ++;
                extensionRail += c;
            }else{
                extensionRoad += c;
            }
        }
    }
    int d1 = extensionRoad + 0.5;
    int d2 = extensionRail + 0.5;
    cout << states << " " << d1 << " " << d2;



}

