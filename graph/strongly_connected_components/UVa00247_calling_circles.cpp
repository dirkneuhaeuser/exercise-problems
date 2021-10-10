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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

enum {VISITED = -2, UNVISITED = -1};
vector<int> visited, dfs_num, dfs_low, stackNodes;
int dfsExploreNumber;
unordered_map<string, int> name2idx;
vector<string> idx2name;
vector<vector<string>> ret;
int ssc;

void tarjan(int cur, vector<set<int>> &al){
    visited[cur] = true; // only to let us know that this node could be part of the next ssc. 
    // it is set to 0 if it is finally part of a ssc and cannot be used by single forward edge from different ssc

    dfs_low[cur] = dfs_num[cur] = dfsExploreNumber++;
    stackNodes.push_back(cur);
    for(int next: al[cur]){
        if(dfs_num[next] == UNVISITED){
            tarjan(next, al);
        }
        if(visited[next]){ // a forward edge to a different ssc with lower dfs_low is not allowed. It would be processed earlier and have visted set to 0
            dfs_low[cur] = min(dfs_low[cur], dfs_low[next]);
        }
    }
    if(dfs_low[cur] == dfs_num[cur]){
        ssc++;
        vector<string> ans;
        while(true){
            int node = stackNodes.back(); stackNodes.pop_back();
            ans.push_back(idx2name[node]);
            visited[node] = 0;
            if(node == cur) break;
        }
        ret.push_back(ans);
    }
}


void solve() 
{
    // Strongly connected components. Here with retrievel of solution.
    // Used algorithm: Tarjan. 
    //
    // The lowes dfs_low of a ssc is considered the root of the ssc.
    // With tarjan we use the dfs_num to navigate to unvisited nodes.
    // The visited array is just for letting us know about the current exploring SSC. If we find one, we will set all of the nodes within to zero. using a stack
    // So whenever we have only a forward edge towards this ssc we do not update our dfs_low;
    int cnt = 1;
    int n, m;
    while(cin >> n >> m){
        if(n==0 && m==0) break;
        if(cnt != 1){
            cout << endl;
        }
        visited.assign(n, 0);
        dfs_num.assign(n, UNVISITED);
        dfs_low.assign(n, UNVISITED);
        stackNodes.clear();
        dfsExploreNumber = 0;
        ssc = 0;
        ret.clear();

        int idx = 0;
        name2idx.clear();
        idx2name.clear();

        vector<set<int>> al(n, set<int>());
        FOR(j, m){
            string a, b; cin >> a >> b;
            if(name2idx.count(a) == 0){
                name2idx[a] = idx++;
                idx2name.push_back(a);
            }
            if(name2idx.count(b) == 0){
                name2idx[b] = idx++;
                idx2name.push_back(b);
            }
            al[name2idx[a]].insert(name2idx[b]);
        }
        FOR(i, n){
            if(dfs_num[i] == UNVISITED){
                tarjan(i, al);
            }
        }

        cout << "Calling circles for data set " << cnt++ << ":" <<endl; 
        FOR(i, ret.size()){
            FOR(j, ret[i].size()){
                cout << ret[i][j];
                if(j < ret[i].size() - 1) cout << ", ";
            }
            cout << endl;
        }


    }


}

