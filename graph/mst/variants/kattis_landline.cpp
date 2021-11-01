#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
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
        rank.assign(n, 1);
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
        rank[px]+= rank[py];
        return true;
    }
};
void solve() 
{
    // MST with some restrictions. First process all secure edges afterwards all edges, which have exactly one insecure endpoint;
    int n, m, p; cin >> n >> m >> p;
    vector<bool> insecure(n, false);
    FOR(i, p){
        int num; cin >> num;
        num--;
        insecure[num] = true;
    }
    if(p == n){
        // edge case: all buildings need to be connected
        vector<vector<int>> AM(n, vector<int>(n, INF));
        FOR(i, m){
            int a, b, c; cin >> a >> b >>c;
            a--; b--;
            AM[a][b] = min(AM[a][b], c);
            AM[b][a] = min(AM[b][a], c);
        }
        bool pos = true;
        ll ret = 0;
        FOR(i, n){
            for(int j=i+1; j<n; ++j){
                if(AM[i][j] == INF){
                    pos = false;
                    break;
                }else{
                    ret+= AM[i][j];
                }
            }
        }
        if(pos){
            cout << ret;
        }else{
            cout << "impossible";
        }
        return;
    }
    vector<tiii> edgesSecure;
    vector<tiii> edgesInsecure;
    FOR(i, m){
        int a, b, c; cin >> a >> b >>c;
        a--; b--;
        if(insecure[a] && insecure[b]){
            continue;
        }else if(insecure[a] || insecure[b]){
            edgesInsecure.push_back({c, a, b});
        }else{
            edgesSecure.push_back({c, a, b});
        }
    }
    sort(edgesSecure.begin(), edgesSecure.end());
    sort(edgesInsecure.begin(), edgesInsecure.end());

    ll ret = 0;
    DJS djs(n);
    FOR(i, edgesSecure.size()){
        auto [c, a, b] = edgesSecure[i];
        if(djs.unionfy(a, b)){
            ret+=c;
        }
    }
    int sec = n - p;
    if(djs.forrests > p + 1){
        // all secures need to be connected
        cout << "impossible";
        return;
    }
    FOR(i, edgesInsecure.size()){
        auto [c, a, b] = edgesInsecure[i];
        if(djs.unionfy(a, b)){
            ret+=c;
        }
    }
    if(djs.forrests == 1){
        cout << ret;
    }else{
        cout << "impossible";
    }

}

