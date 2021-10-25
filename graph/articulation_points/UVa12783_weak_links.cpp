#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
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

enum {UNVISITED=-1};
vector<int> dfs_low, dfs_num, parent;
vector<pii> bridges;
int dfs_idx;

void dfsBridges(int cur, vector<vector<int>> &AL){
    dfs_num[cur] = dfs_low[cur] = dfs_idx++;
    for(int next: AL[cur]){
        if(dfs_num[next] == UNVISITED){
            parent[next] = cur;
            dfsBridges(next, AL);
            if(dfs_low[next] > dfs_num[cur]){ // bc of bridges here strictly greater
                if(next < cur){
                    bridges.push_back({next, cur});
                }else{
                    bridges.push_back({cur, next});
                }
            }
            dfs_low[cur] = min(dfs_low[cur], dfs_low[next]);

        }else{
            if(parent[cur] != next){
                dfs_low[cur] = min(dfs_low[cur], dfs_num[next]); // bc of u, I am 
            }
        }
    }
}



void solve() 
{
    int n, m; 
    // finding all articulation bridges
    while(cin >> n >> m && n !=0 && m != 0){
        vector<vector<int>> AL(n, vector<int>());
        FOR(i, m){
            int a, b; cin >> a >> b;
            AL[a].push_back(b);
            AL[b].push_back(a);
        }
        dfs_low.assign(n, UNVISITED);
        dfs_num.assign(n, UNVISITED);
        parent.assign(n, UNVISITED);
        bridges.clear();
        dfs_idx = 0;
        FOR(i, n){
            if(dfs_num[i] == UNVISITED){
                dfsBridges(i, AL);
            }
        }
        sort(bridges.begin(), bridges.end());
        cout << bridges.size();
        FOR(i, bridges.size()){
            cout << " " << bridges[i].first << " " << bridges[i].second;
        }
        cout << endl;
    }

}

