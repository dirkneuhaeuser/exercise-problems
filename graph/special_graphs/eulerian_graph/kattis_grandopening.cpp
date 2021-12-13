#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
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

unordered_map<string, int> name2idx;
vector<string> idx2name;
int getIdx(string name){
    if(name2idx.count(name) ==0){
        name2idx[name] = idx2name.size();
        idx2name.push_back(name);
    }
    return name2idx[name];
}

vector<bool> visited;
void dfs(int cur, vector<vi> &AL){
    visited[cur] = true;
    for(int next: AL[cur]){
        if(!visited[next]){
            dfs(next, AL);
        }
    }
}

void solve() 
{
    // problem: https://open.kattis.com/problems/grandopening
    // about: Check if the underlying directed graph has an euler path (1). Connectivity + 2) inDegree == outDegree for all nodes, apart of the first and last)
    int n, m; cin >> n >> m;
    vi inD(n, 0), outD(n, 0);
    bool allGood = true;
    vector<vector<int>> ALUndirected(n, vi());
    FOR(i, n){
        string base; cin >> base;
        int baseIdx = getIdx(base);
        int k; cin >> k;
        FOR(j, k){
            string next; cin >> next;
            int nextIdx = getIdx(next);
            if(nextIdx != baseIdx){
                allGood = false;
                inD[nextIdx]++;
                outD[baseIdx]++;
                ALUndirected[nextIdx].push_back(baseIdx);
                ALUndirected[baseIdx].push_back(nextIdx);
            }
        }
    }
    if(allGood){
        cout << "FALSE ALARM";
        return;
    }

    bool possible = true;
    visited.assign(n, false);
    int cc = 0;
    // 1) Connectivity
    FOR(i, n){
        if(!visited[i] && (inD[i] > 0 || outD[i] > 0)){
            dfs(i, ALUndirected);
            cc++;
        }
    }
    if(cc>1) possible = false;

    // 2) Check Degrees
    int inDHigher = -1;
    int outDHigher = -1;
    FOR(i, n){
        if(inD[i] == outD[i]) continue;
        if(inD[i] == outD[i] + 1){
            if(inDHigher != -1) possible = false;
            inDHigher = i;
        }else if(inD[i] +1 == outD[i]){
            if(outDHigher != -1) possible = false;
            outDHigher = i;
        }else{
            possible = false;
        }
    }
    if(!possible){
        cout << "IMPOSSIBLE";
    }else{
        cout << "POSSIBLE";
    }
}

