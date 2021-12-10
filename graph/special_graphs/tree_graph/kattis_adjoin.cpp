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
bool visited[100000];

void markTree(int cur, vector<vi> &AL){
    visited[cur] = true;
    for(int next: AL[cur]){
        if(!visited[next]) markTree(next, AL);
    }
}

int bfs(int cur, vector<int> &dis, vector<vi> &AL){
    // gets distances, apply 3 times:
    // 1. Find furthest away of random node
    // 2. From this node, do bfs
    // 3. From its respective end node (furthest away) also apply the bfs
    queue<int> q;
    q.push(cur);
    dis[cur] = 0;
    int ret = cur;
    while(q.size()){
        int t = q.front(); q.pop();
        for(int next: AL[t]){
            if(dis[next] == INF){
                dis[next] = dis[t] + 1;
                ret = next;
                q.push(next);
            }
        }
    }
    return ret;
}

void solve() 
{
    // problem: https://open.kattis.com/problems/adjoin
    // about: diameter, center and radius of a tree. We have several trees, which we need to connect in such a way, that the result is also a tree and we minimise the overall diameter of that tree. Central Observation: Use the center of a tree to connect trees. Now, we need to connect all centers to the center of the biggest (by diamter) subtree. Then, the resulting diameter is the max of all subtree diameters and the max(biggestRadii[0] + biggestRadii[1] + 1, biggestRadii[1] + biggestRadii[2] + 2). Thats because, when the biggest subtree is involved, we need only one extra edge to pass and else we need two (towards the biggest subtree and from it)
    //
    // learned: center, diameters and radii.
    // radii can be used smately when having several subtrees
    // diameter can be calculated by 2 times bfs(towards the most remote node of a random node -> endpoint1, and then again bfs from endpoint1  -> endpoint2). dis[endpoint2] is the diameter
    int n, m; cin >> n >> m;
    vector<vi> AL(n);
    FOR(j, m){
        int a, b;
        cin >> a >> b;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    memset(visited, 0, sizeof visited);
    vi diameters;
    vi dis(n, INF), dis2(n, INF);
    FOR(i, n){
        if(visited[i] == false){
            int diameterEndpoint1 = bfs(i, dis, AL);
            int diameterEndpoint2 = bfs(diameterEndpoint1, dis2, AL);
            diameters.push_back(dis2[diameterEndpoint2]);
            markTree(i, AL);
        }
    }
    vi radii(3, 0);
    int ans = 0;
    while(diameters.size()){
        int diam = diameters.back();
        ans = max(ans, diam);
        diameters.pop_back();
        int radi = diam/2 + (diam&1);
        if(radi > radii[2]){
            radii[2] = radi;
            for(int i=2; i>0; --i){
                if(radii[i] > radii[i-1]){
                    swap(radii[i], radii[i-1]);
                }
            }
        }
    }
    ans = max(ans, radii[0] + radii[1] + 1);
    ans = max(ans, radii[1] + radii[2] + 2);
    cout << ans;


}

