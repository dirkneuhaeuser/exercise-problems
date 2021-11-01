#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef tuple<long double, int, int> tdii;
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

ld dis(ld ax, ld ay, ld bx, ld by){
    ld q = powl(abs(ax-bx), 2) + powl(abs(ay-by), 2);
    return powl(q, (ld)0.5);
}

vector<int> visited;
void dfs(int cur, vector<int> &inhabitants, vector<vector<pid>> &AL, ld maxDistance, ld &ans){
    visited[cur] = 1;
    ans += (ld)inhabitants[cur] * maxDistance;
    for(auto [next, w]: AL[cur]){
        if(visited[next] == 0){
            dfs(next, inhabitants, AL, max(maxDistance, w), ans);
        }
    }
}

void solve()
{
    // MST MiniMax problem. Crate the MST MiniMax Graph and then dfs through it to calculate the average connecting time
    int count = 1;
    int n; 
    while(cin >> n){
        if(n == 0) break;
        vector<pii> routers;
        vector<int> inhabitants;
        int total = 0;
        FOR(i, n){
            int a, b, c; cin >> a >> b >> c;
            total += c;
            routers.push_back({a, b});
            inhabitants.push_back(c);

        }
        vector<tdii> edges;
        FOR(i, n){
            auto [ax, ay] = routers[i];
            for(int j=i+1; j<n; ++j){
                auto [bx, by] = routers[j];
                ld d = dis(ax, ay, bx, by);
                edges.push_back({d, i, j});
            }
        }
        sort(edges.begin(), edges.end());
        DJS djs(n);
        vector<vector<pid>> AL (n, vector<pid>());
        FOR(i, edges.size()){
            auto [c, a, b] = edges[i];
            if(djs.unionfy(a, b)){
                AL[a].push_back({b, c});
                AL[b].push_back({a, c});
            }
        }
        visited.assign(n, 0);
        ld ans = 0;
        dfs(0, inhabitants, AL, 0, ans);
        ld ret = ans/total;
        cout << "Island Group: " << count++ << " Average " << setprecision(2)<< fixed << ret << endl << endl;

    }

}


