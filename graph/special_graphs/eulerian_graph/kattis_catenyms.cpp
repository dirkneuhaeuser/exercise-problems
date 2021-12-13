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

vector<bool> visited;
void dfs(int cur, vector<vector<pair<int, string>>> &AL){
    visited[cur] =  true;
    for(auto [next, s]: AL[cur]){
        if(!visited[next]){
            dfs(next, AL);
        }
    }

}

vector<string> hierholzer(pis s, vector<vector<pair<int, string>>> &AL){
    // Finds the euler path within a graph in O(E).
    // The algorithm passes through the graph rather arbitrarily. 
    // Idea: If you start u and at some point come back to u, you either have each edge passed (save the progress in vi idx) or you can still have another detour starting from u.
    // With the stack you have this kind of post-order (similar to topological sort)
    vector<string> ret;
    vi idx(AL.size(), 0);
    vector<pis> stack;
    stack.push_back(s);
    while(stack.size()){
        pis cur = stack.back();
        auto [idxCur, s] = cur;
        if(idx[idxCur] < AL[idxCur].size()){
            stack.push_back(AL[idxCur][idx[idxCur]]);
            idx[idxCur]++;
        }else{
            pis justFinishedCycle = stack.back(); stack.pop_back();
            ret.push_back(justFinishedCycle.second);
        }
    }
    return ret;
}

void solve() 
{
    // problem: https://open.kattis.com/problems/catenyms
    // about: Find an Euler-Path on a directed graph (each word forms an edge, with start end end charcter the start/end node). For the graph to have en euler cycle, it needs to be 1) connected and 2) all nodes need to have the same in-Degree as out-Degree. However, we need just a path, therefore, is also ok to have 1 node with inDegree +1 == outDegree and 1 node vice versa. Note if the 2) condition holfs, it is sufficient to pretent the edges are undirected and check if the graph is connected, instead of checking for strong conectivity.
    //
    int n; cin >> n;
    vi inDeg(26, 0), outDeg(26, 0);
    vector<vector<pair<int, string>>> AL(26, vector<pair<int, string>>());
    vector<vector<pair<int, string>>> ALUndirected(26, vector<pair<int, string>>());
    FOR(i, n){
        string s; cin >> s;
        char a = s[0];
        char b = s.back();
        int ai = a - 'a';
        int bi = b - 'a';
        outDeg[ai]++;
        inDeg[bi]++;
        AL[ai].push_back({bi, s});
        ALUndirected[ai].push_back({bi, s});
        ALUndirected[bi].push_back({ai, s});
    }
    FOR(i, 26){
        sort(AL[i].begin(), AL[i].end(), [](pis &a, pis &b){
                if(a.second < b.second) return true;
                if(a.second >= b.second) return false;
                return false;
                });
    }
    visited.assign(26, false);
    int cc = 0;
    FOR(i, 26){
        if((inDeg[i] || outDeg[i] ) && !visited[i]){
            dfs(i, ALUndirected);
            cc++;
        }
    }
    if(cc > 1){
        cout << "***";
        return;
    }
    int inDegMore=0, outDegMore=0;

    FOR(i, 26){
        if(inDeg[i] == outDeg[i]) continue;
        if(inDeg[i] == outDeg[i] + 1){
            inDegMore++;
        }else if(inDeg[i] +1 == outDeg[i]){
            outDegMore++;
        }else{
            cout << "***";
            return;
        }
    }
    if((inDegMore==0 && outDegMore == 0) || (inDegMore==1 && outDegMore == 1)){
        vector<string> ans;
        int anyIdx = -1;
        FOR(i, 26){
            if(outDeg[i] >inDeg[i]){
                pis start = {i, ""};
                ans = hierholzer(start, AL);
                break;
            }
            if(outDeg[i]>0 && anyIdx == -1){
                anyIdx = i;
            }
        }
        if(ans.size() == 0){
            pis start = {anyIdx, ""};
            ans = hierholzer(start, AL);
        }
        for(int i=n-1; i>=0; --i){
            cout << ans[i];
            if(i>0) cout <<".";
        }
    }else{
        cout << "***";
        return;
    }

}

