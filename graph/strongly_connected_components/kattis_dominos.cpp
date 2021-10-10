#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long, long> pll;
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
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

enum {UNVISITED = -1, VISITED=-2};
vector<int> dfs_num, dfs_low, dfs_stack, visited, roots;
int dfs_number;

void tarjan(int cur, vector<vector<int>> &al){
    dfs_num[cur] = dfs_low[cur] = dfs_number++;
    dfs_stack.push_back(cur);
    visited[cur] = true;
    for(int next: al[cur]){
        if(dfs_num[next] == UNVISITED){
            tarjan(next, al);
        }
        if(visited[next]){
            dfs_low[cur] = min(dfs_low[cur], dfs_low[next]);
        }
    }
    if(dfs_num[cur] == dfs_low[cur]){ // root of subtree
        while(1){
            int node = dfs_stack.back(); dfs_stack.pop_back();
            roots[node] = cur; // for reducing the graph
            visited[node] = 0;
            if(node == cur) break;
        }
    }
}


void solve() 
{
    // Reduce all strongly connected components to one node each. In this reduced graph find all nodes with inDegree == 0
    int n, m; cin >> n >> m;
    vector<vector<int>> al(n, vector<int>());
    FOR(i, m){
        int a, b; cin >> a >> b;
        a--; b--;
        al[a].push_back(b);
    }

    dfs_num.assign(n, UNVISITED);
    dfs_low.assign(n, UNVISITED);
    dfs_stack.clear();
    visited.assign(n, 0);
    dfs_number = 0;
    roots.assign(n, -1);

    // Tarjan: finding all strongly connected components. For each node, save its root (for each ssc we need a representative). 
    // in trajan, we conside the first node in the dfs spanntree we meet of a SSC to be the representative
    FOR(i, n){
        if(dfs_num[i] == UNVISITED){
            tarjan(i, al);
        }
    }
    // reduce: each strongly connected component will be reduced to one node only
    vector<set<int>> al2(n, set<int>());
    FOR(i, n){
        int start = roots[i];
        FOR(j, al[i].size()){
            int target = roots[al[i][j]];
            if(start != target){
                al2[start].insert(target);
            }
        }
    }
    // Finding inDegree = 0 (these you have to push)
    // Set all not used nodes (which has been merged to a different representative) to -1. we will ignore these
    // For the rest, update its in-degree according the the new reduces adjacency list
    vector<int> inDegree(n, -1);
    FOR(i, n){
        if(roots[i] == i){
            inDegree[i] = 0;
        }
    }
    FOR(i, n){
        for(int next: al2[i]){
            inDegree[next]++;
        }
    }
    int ret = 0;
    FOR(i, n){
        if(inDegree[i]==0){
            ret++;
        }
    }
    cout << ret;



}

