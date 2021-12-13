#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef pair<int, string> pis;
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

vector<bool> visited;
void dfs(int cur, vector<vector<int>> &AL){
    visited[cur] =  true;
    for(int next: AL[cur]){
        if(!visited[next]){
            dfs(next, AL);
        }
    }

}

vector<int> hierholzer(int s, vector<vector<int>> &AL){
    // Finds the euler path within a graph in O(E).
    // The algorithm passes through the graph rather arbitrarily. 
    // Idea: If you start u and at some point come back to u, you either have each edge passed (save the progress in vi idx) or you can still have another detour starting from u.
    // With the stack you have this kind of post-order (similar to topological sort) -> REVERSE the result
    vector<int> ret, stack, idx(AL.size(), 0);
    stack.push_back(s);
    while(stack.size()){
        int cur = stack.back();
        if(idx[cur] < AL[cur].size()){
            stack.push_back(AL[cur][idx[cur]]);
            idx[cur]++;
        }else{
            int justFinishedCycle = stack.back(); stack.pop_back();
            ret.push_back(justFinishedCycle);
        }
    }
    return ret; // needs to be reversed.
}


void solve() 
{
    // problem: https://open.kattis.com/problems/eulerianpath
    // about: Find an Euler-Path on a directed graph. For the graph to have en euler cycle, it needs to be 1) connected and 2) all nodes need to have the same in-Degree as out-Degree. However, we need just a path, therefore, is also ok to have 1 node with inDegree +1 == outDegree and 1 node vice versa. Note if the 2) condition holfs, it is sufficient to pretent the edges are undirected and check if the graph is connected, instead of checking for strong conectivity.
    //
    int n, m;
    while(cin >> n >> m){
        if(n == 0 && m == 0)break;
        vi inDeg(n, 0), outDeg(n, 0);
        vector<vector<int>> AL(n, vector<int>());
        vector<vector<int>> ALUndirected(n, vector<int>());
        FOR(i, m){
            int a, b; cin >> a >> b;
            outDeg[a]++;
            inDeg[b]++;
            AL[a].push_back(b);
            ALUndirected[a].push_back(b);
            ALUndirected[b].push_back(a);
        }
        // check if euler path is possible:
        bool possible = true;

        // 1) connected
        visited.assign(n, false);
        int cc = 0;
        FOR(i, n){
            if((inDeg[i] || outDeg[i] ) && !visited[i]){
                dfs(i, ALUndirected);
                cc++;
            }
        }
        if(cc > 1){
            possible = false;
        }

        // 2) inDegree == outDegree with two exceptions
        int inDegMore=0, outDegMore=0;
        FOR(i, n){
            if(inDeg[i] == outDeg[i]) continue;
            if(inDeg[i] == outDeg[i] + 1){
                inDegMore++;
            }else if(inDeg[i] +1 == outDeg[i]){
                outDegMore++;
            }else{
                possible = false;
            }
        }
        if(!((inDegMore==0 && outDegMore == 0) || (inDegMore==1 && outDegMore == 1))){ // right the two exceptions
            possible = false;
        }

        if(!possible){
            cout << "Impossible" << endl;
            continue;
        }

        // euler path possible, retrieve solution with Hierholzer. If one node has outDegree == inDegree +1, start here (only euler path not cycle);
        vector<int> ans;
        int startIdx = -1;
        FOR(i, n){
            if(outDeg[i] >inDeg[i]){
                ans = hierholzer(i, AL);
                break;
            }
            if(outDeg[i]>0 && startIdx == -1){
                startIdx = i;
            }
        }
        if(ans.size() == 0){
            ans = hierholzer(startIdx, AL);
        }

        for(int i=m; i>=0; --i){
            cout << ans[i] << " ";
        }
        cout << endl;
    }

}

