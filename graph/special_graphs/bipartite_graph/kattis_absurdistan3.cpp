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
vector<bool> visited;

void handleCycles(int start, vector<vi> &AL){
    stack<int> s;
    s.push(start);

    while(!s.empty()) {
        int cur = s.top();
        s.pop();

        for(int next: AL[cur]){
            if(!visited[next]) {
                s.push(next);
                visited[cur] = true;
                cout << cur+1<< " " << next+1<< endl;
                break;
            }
        }
    }

    // close cycle
    for(int next: AL[start]){
        if(!visited[next]) {
            cout << next+1 << " " << start+1 << endl;
            break;
        }
    }
}

void handleLeaves(vector<vi> &AL, vi &inDeg) {
    stack<int> s;
    int n = AL.size();
    FOR(i, n){
        if(inDeg[i] == 1) {
            s.push(i);
        }
    }

    while(!s.empty()) {
        int cur = s.top();
        s.pop();
        visited[cur]=true;
        for(int next: AL[cur]){
            if(!visited[next]) {
                inDeg[next]--;
                if(inDeg[next] == 1) {
                    s.push(next);
                }
                cout << cur+1 << " " << next+1 << endl;
            }
        }
    }

}

void solve() 
{
    // problem: https://open.kattis.com/problems/absurdistan3
    // about: Assign edges to nodes. First assign all edges to leaves, as this is 100% correct. What remains are cycles, hier just start at and afterwords, dont forget to close it
    // note: Would also fit very well as assignment-problem, but unfortunately, will get TLE
    // complexity: O(sqrt(n+n) * n)
    int n; cin >> n;
    vector<vi> AL(n);
    vi inDeg(n, 0);
    vector<pii> edges;
    FOR(i, n){
        int a, b;
        cin >> a >> b;
        a--; b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
        inDeg[a]++;
        inDeg[b]++;
        edges.push_back({a, b});
    }
    visited.assign(n, false);
    handleLeaves(AL, inDeg);
    FOR(i, n){
        if(!visited[i]){
            handleCycles(i, AL);
        }
    }

}

