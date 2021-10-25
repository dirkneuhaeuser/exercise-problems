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

enum{UNVISITED = -1};
vector<vector<int>> ALBridges;
vector<int> dfs_low, dfs_num, parent;
int dfs_idx;

void dfsArtBridges(int cur, vector<vector<int>> &AL){
    dfs_low[cur] = dfs_num[cur] = dfs_idx++;
    for(int next: AL[cur]){
        if(dfs_num[next] == UNVISITED){
            parent[next] = cur;
            // normally: if cur == root -> rootChildren++ BUT here not needed
            dfsArtBridges(next, AL);
            if(dfs_low[next] > dfs_num[cur]){
                ALBridges[cur].push_back(next);
                ALBridges[next].push_back(cur);
            }
            dfs_low[cur] = min(dfs_low[cur], dfs_low[next]);
        }else{
            if(parent[cur] != next){
                dfs_low[cur] = min(dfs_low[cur], dfs_num[next]);
            }
        }
    }
}
vector<bool> v;
bool dfs(int cur, int goal){
    v[cur] = true;
    if(cur == goal) return true;
    for(int next: ALBridges[cur]){
        if(v[next] == false && dfs(next, goal)){
            return true;
        }
    }
    return false;
}


void solve() 
{
    // Articulation Bridge Problem.                                                                                      │ 13 9 1  
120                 pigeonValue[i] += ans;                                                               
    // Simple Path: Each vertex will be used at max one time.
    // Task here: Check if there exist exactly ONE simple path.
    // We can reduce this problem to a graph of only articulation bridges. If at some point we would take a non-articulation bridge, that means, that there is also an other corridor,
    // hence: The simple path is not unique.
    // For a simple path from a to b to be unique, it must consist of only artiulation bridges.
    int r, c, q;
    while(cin >> r >> c >> q){
        if(r == 0 && c == 0 && q == 0) return;
        vector<vector<int>> AL(r, vector<int>());
        FOR(i, c){
            int a, b; cin >> a >> b;
            a--; b--;
            AL[a].push_back(b);
            AL[b].push_back(a);
        }
        ALBridges.assign(r, vector<int>());
        dfs_low.assign(r, UNVISITED);
        dfs_num.assign(r, UNVISITED);
        parent.assign(r, UNVISITED);
        dfs_idx = 0;
        FOR(i, r){
            if(dfs_num[i] = UNVISITED){
                dfsArtBridges(i, AL);
            }
        }
        FOR(i, q){
            v.assign(r, false);
            int a, b; cin >> a >> b;
            a--; b--;
            if(dfs(a, b)){
                cout << "Y" << endl;
            }else{
                cout << "N" << endl;
            }
        }
        cout <<"-" << endl;
    }

}

