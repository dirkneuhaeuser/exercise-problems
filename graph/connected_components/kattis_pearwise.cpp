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

int dfs_number;
vector<int> dfs_low, dfs_num, visited, dfs_stack, root;

void tarjan(int cur, vector<vector<int>> &AL){
    dfs_num[cur] = dfs_low[cur] = dfs_number++;
    visited[cur] = 1;
    dfs_stack.push_back(cur);
    for(int next: AL[cur]){
        if(dfs_num[next] == UNVISITED){
            tarjan(next, AL);
        }
        if(visited[next] == 1){
            dfs_low[cur] = min(dfs_low[cur], dfs_low[next]);
        }
    }
    if(dfs_num[cur] == dfs_low[cur]){ // root of a scc;
        while(dfs_stack.size()){
            int next = dfs_stack.back();
            visited[next] = 0;
            dfs_stack.pop_back();
            root[next] = cur;
            if(next == cur) break; // very important: do not break via: if(dfs_low[cur] != dfs_low[next]) -> this would be wrong
        }
    }
}



void solve() 
{
    // Strongly Connected Component Problem.
    // 1. Create directed graph: a->b means a will beat b;
    // 2. reduce strongly connected components (if its just them, each of them has a chance of winning, depending on the order)
    // The reduced nodes with indegree == 0 can win

    int n, ballots; cin >> n >> ballots;
    vector<vector<int>> votes(n, vector<int>(n, 0)); //votes[i][j] is the number of ballots in which i > j;
    FOR(i, ballots){
        int num; cin >> num;
        string pref; cin >> pref;
        FOR(j, n){
            int better = pref[j] - 'A';
            for(int k=j+1; k<n; ++k){
                int worse = pref[k] - 'A';
                votes[better][worse]+= num;
            }
        }
    }
    vector<vector<int>> AL(n, vector<int>());
    FOR(i, n){
        for(int j=i+1; j<n; ++j){
            int pro = votes[i][j];
            int con = votes[j][i];
            if(pro > con){
                AL[i].push_back(j);
            }else{
                AL[j].push_back(i);
            }
        }
    }
    dfs_low.assign(n, UNVISITED);
    dfs_num.assign(n, UNVISITED);
    visited.assign(n, -1);
    root.assign(n, -1);
    dfs_number = 0;
    FOR(i, n){
        if(dfs_low[i] == UNVISITED){
            tarjan(i, AL);
        }
    }
    vector<set<int>> adjustedAL(n, set<int>());
    FOR(i, n){
        int rootI = root[i];
        for(int next: AL[i]){
            int rootNext = root[next];
            if(rootNext == rootI) continue;
            adjustedAL[rootI].insert(rootNext);
        }
    }
    vector<int> inDegree(n, 0);
    FOR(i, n){
        for(int next: adjustedAL[i]){
            inDegree[next]++;
        }
    }
    set<int> allReducedNodes(root.begin(), root.end());
    vector<bool> possible(n, false);
    for(int reduced: allReducedNodes){
        if(inDegree[reduced] == 0){
            for(int i=0; i<root.size(); ++i){
                if(root[i] == reduced){
                    possible[i] = true;
                }
            }
        }
    }
    FOR(i, n){
        char iChar = 'A' + i;
        cout << iChar << ": ";
        if(possible[i]){
            cout << "can win";
        }else{
            cout << "can't win";
        }
        cout << endl;
    }
    

}

