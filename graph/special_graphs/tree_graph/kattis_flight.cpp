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
typedef pair<int, vi> pid;
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

pid bfs(int root, vector<vi> &AL, int endpoint1, int endpoint2){
    // returns {endpoint, dis}
    vi dis(AL.size(), INF);
    dis[root] = 0;
    queue<int> q;
    q.push(root);
    int endpoint = root;
    while(q.size()){
        int cur = q.front(); q.pop();
        for(int next: AL[cur]){
            if((cur == endpoint1 || cur == endpoint2) && (next == endpoint1 || next == endpoint2)) continue;
            if(dis[next] == INF){
                dis[next] = dis[cur] + 1;
                endpoint = next;
                q.push(next);
            }
        }
    }
    return {endpoint, dis};
}

int getCenterDfs(int cur, vector<vi> &AL, int targetDis, vi &dis, vi &disRev){
    // getCenterDfs
    if(dis[cur] == targetDis/2) return cur;
    for(int next: AL[cur]){
        if(dis[next] + disRev[next] == targetDis && dis[next] > dis[cur]){
            return getCenterDfs(next, AL, targetDis, dis, disRev);
        }
    }
    return -1;

}

void printBothCenter(vector<vi> &AL, int endpoint1, int endpoint2){
    pid a = bfs(endpoint1, AL, endpoint1, endpoint2); // find furthest away -> endpoint1 of diameter
    pid aDiam = bfs(a.first, AL, endpoint1, endpoint2); // find its furthest away -> endpoint2 of diameter
    pid aDiamRev = bfs(aDiam.first, AL, endpoint1, endpoint2); // the other way round (from endpoint2 to endpoin1)
    int aTargetDis = aDiam.second[aDiam.first];
    cout << getCenterDfs(a.first, AL, aTargetDis, aDiam.second, aDiamRev.second) +1 << " "; // go along the path until this longest path until half -> center

    pid b = bfs(endpoint2, AL, endpoint1, endpoint2);
    pid bDiam = bfs(b.first, AL, endpoint1, endpoint2);
    int bTargetDis = bDiam.second[bDiam.first];
    pid bDiamRev = bfs(bDiam.first, AL, endpoint1, endpoint2);
    cout << getCenterDfs(b.first, AL, bTargetDis, bDiam.second, bDiamRev.second) + 1;
    cout << endl;

}



int mergeDiameters(vector<vi> &AL, int endpoint1, int endpoint2){
    // if edege endpoint1<->endpoint2 is omitted, it returns the maximal diameters of both subtrees and the merged tree
    pid a = bfs(endpoint1, AL, endpoint1, endpoint2);
    pid aDiam = bfs(a.first, AL, endpoint1, endpoint2);
    int aDis = aDiam.second[aDiam.first];
    int aRadius = aDis/2 + (aDis&1);

    pid b = bfs(endpoint2, AL, endpoint1, endpoint2);
    pid bDiam = bfs(b.first, AL, endpoint1, endpoint2);
    int bDis = bDiam.second[bDiam.first];
    int bRadius = bDis/2 + (bDis&1);

    return max({aDis, bDis, aRadius + bRadius + 1});

}


void solve() 
{
    // problem: https://open.kattis.com/problems/flight
    // about: diameter, radius and center problem. For all edges, if it would be deleted: find for both subtrees its centers, such when both are connected, the overall diameter is the smallest
    //
    // Overall diameter: max(diameterTree1, diameterTree2, largestWingTree1 + largestWingTree2 + 1)
    // Here with printing both center -> dfs
    int n; cin >> n;
    vector<vi> AL(n);
    FOR(i, n-1){
        int a, b; cin >> a >> b;
        a--; b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    int ans = INF;
    int a, b;
    FOR(i, n){
        for(int next: AL[i]){
            if(next < i) continue;
            int pot = mergeDiameters(AL, i, next);
            if(pot < ans){
                ans = min(ans, pot);
                a = i;
                b = next;
            }
        }
    }
    cout << ans << endl;;
    cout << a+1<< " " << b+1 << endl;
    printBothCenter(AL, a, b);


}

