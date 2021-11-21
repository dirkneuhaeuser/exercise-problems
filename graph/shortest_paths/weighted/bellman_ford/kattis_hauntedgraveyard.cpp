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

vector<pii> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
tiii grid[30][30];

vector<tiii> nexts(int i, int j, int n, int m){
    vector<tiii> adj;
    if(get<0>(grid[i][j]) != -1){  // -1 grass/ also -2 not possibel (gravyard);
        tiii next = grid[i][j];
        adj.push_back({next});
        return adj;

    }
    for(auto [di, dj]: dir){
        int nextI = i + di;    
        int nextJ = j + dj;    
        if(nextI < 0 || nextJ < 0 || nextI>=n || nextJ>=m)continue;
        if(get<0>(grid[nextI][nextJ]) == -2) continue; // gravestone;
        adj.push_back({nextI, nextJ,1});
    }
    return adj;

}


// BELOW FOR NEGATIVE CYCLES
vector<vector<int>> bellmann_ford(int endI, int endJ, int total){ // O(V^3)
    // Get the distance from start node to all other nodes and works with negative cycles (no infinite queue)
    // Stops after n iterations, if afterwars still relaxations are possible -> negative cycle
    // Limit ~ V<450
    int n = endI + 1;
    int m = endJ + 1;
    vector<vector<int>> dist(n, vector<int>(m, INF));
    dist[0][0] = 0;
    for(int i=0; i<total; ++i){
        bool changed = false;
        for(int ii=0; ii<n; ++ii){
            for(int jj=0; jj<m; ++jj){ // O(900*900)
                if(endI==ii && endJ==jj) continue;
                if(dist[ii][jj] == INF) continue;
                for(auto [nextI, nextJ, w]: nexts(ii, jj, n, m)){ // O((900^2 + 4)
                    if(dist[nextI][nextJ] > dist[ii][jj]+ w){
                        dist[nextI][nextJ] = min(dist[nextI][nextJ], dist[ii][jj] + w);
                        changed = true;
                    }
                }
            }
        }
        if(!changed) return dist;
    }
    return dist;
}

bool getNegativeCycleStarts(vector<vector<int>> &dist, int endI, int endJ){
    int n = endI+1;
    int m = endJ+1;
    for(int ii=0; ii<n; ++ii){
        for(int jj=0; jj<m; ++jj){
            if(endI==ii && endJ==jj) continue;
            if(dist[ii][jj] != INF){
                for(auto [nextI, nextJ, w]: nexts(ii, jj, n, m)){
                    if(dist[nextI][nextJ] > dist[ii][jj] + w){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

vector<vector<bool>> v;
int color(int i, int j, int n, int m){
    v[i][j] = true;
    if(i == n-1 && m == m-1) return 0;
    int ret = 1;
    for(auto [nextI, nextJ, w]: nexts(i, j, n, m)){
        if(!v[nextI][nextJ]){
            ret += color(nextI, nextJ, n, m);
        }
    }
    return ret;
}



void solve() 
{
    // Weighted SSSP Problem with negative cycles. Here I use Bellmann-Ford to detect negative cyles.
    // Pls note:
    // 1. Within Bellmann-Ford, when you are at the end field, you continue, and you do not go the adjacent fields.
    // 2. We do a dfs upfront to check how many fields are actually accessable from the n*m, meaning: which are not graveyards, or are not beyond the end
    //    This count than can be used within bellmann-ford as prunning.
    // 3. It just got acceped (0.99 seconds runtime and 1.0 is limit)
    int n,m; 
    while(cin >> n >> m){
        if(n == 0 && m == 0) break;
        FOR(i, n){
            FOR(j, m){
                get<0>(grid[i][j]) = -1;
            }
        }
        int g; cin >> g;
        FOR(i, g){
            int a, b; cin >> a >> b;
            get<0>(grid[a][b]) = -2;
        }
        int hh; cin >> hh;
        FOR(i, hh){
            int a, b, an, bn, c; cin >> a >> b >> an >> bn >>c;
            get<0>(grid[a][b]) = an;
            get<1>(grid[a][b]) = bn;
            get<2>(grid[a][b]) = c;
        }
        // next: Bellmann-fords needs to iterate many times O(N * E). The first N (which here is nxm) we can alleviate by running a simple dfs and checking how many
        // of these cells are really accessable from start to end.
        v.assign(n, vector<bool>(m, false));
        int total = color(0, 0, n, m);


        vector<vector<int>> dist = bellmann_ford(n-1, m-1, total);
        bool never =  getNegativeCycleStarts(dist, n-1, m-1);
        if(never){
            cout << "Never" << endl;
        }
        else if(dist[n-1][m-1] != INF){
            cout << dist[n-1][m-1] << endl;
        }else{
            cout << "Impossible" << endl;
        }
    }
}

