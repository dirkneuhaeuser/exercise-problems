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

int LOG;
vector<ll> depth;
vector<vi> up;

void bfs(vector<vi> &AL){
    queue<int> q;
    q.push(0);
    depth[0]=0;
    while(q.size()){
        int cur = q.front(); q.pop();
        for(int next: AL[cur]){
            if(depth[next] == INF){
                depth[next] = depth[cur]+1;
                up[next][0] = cur;
                q.push(next);

                // calculate the binary lifting
                for(int j=1; j<LOG; ++j){
                    up[next][j] = up[up[next][j-1]][j-1];
                }
            }
        }
    }
}

int getLCA(int a, int b){
    if(depth[a] < depth[b]){
        swap(a, b);
    }
    // a is deeper;
    int dif = depth[a]-depth[b];
    for(int i=0; i<LOG; ++i){
        if(dif & (1 << i)){
            a = up[a][i];
        }
    }
    // edge-case:
    if(a == b) return a;
    // binary lifting to the predecessor of LCA
    for(int i=LOG-1; i>=0; --i){ // very important here to go from LOG-1 -> 0, as otherwise we cannnot do all jumps
        // for example the grand parent is two levels up. we cannot jump 1 and again 1...
        if(up[a][i] == up[b][i]) continue;
        a = up[a][i];
        b = up[b][i];
    }
    // return LCA
    return up[a][0];
}

ll getLength(int a, int b){
    int lca = getLCA(a, b);
    return depth[a] + depth[b] - 2*depth[lca];
}



void solve() 
{
    // problem: https://open.kattis.com/problems/tourists
    // about: For each multiple j of a number i we want to calculate the path length. We can do that by fixing the root (1) and then calculate depth[i] + depth[j] - 2*depth[LCA(i, j)]. The trick is to calculate the LCA in logarithmic time by using binary lifting.
    //
    // binary lifting -> get kth ancestor in log(n) by precalculateing the 1st, 2nd, 4th, 8th, 16th, ... <= nth ancestor
    // To find the LCA(a, b), we can use this binary lifting:
    // 1. bring both to the same depth
    // 2. binary lift to the smallest depth, such that both are not even (-> 1 level below LCA);
    // return parent of either a or b
    //
    // note: DFS to calculate the depth doesn't work, as we will face memory pressure. -> use bfs instead.
    int n; cin >> n;
    vector<vi> AL(n);
    FOR(i, n-1){
        int a, b; cin >> a >> b;
        a--; b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    while((1<<LOG) <= n){
        LOG++;
    }
    //cout << LOG << endl;
    //LOG = 20;
    depth.assign(n, INF);
    depth[0] = 0;
    up.assign(n, vector<int>(LOG, 0));
    bfs(AL);
    ll ans = 0;
    for(int i=1; i<=n; ++i){
        for(int j=i+i; j<=n; j+=i){
            ll l = getLength(i-1, j-1);
            ans += l+1;
        }
    }
    cout << ans;



}

