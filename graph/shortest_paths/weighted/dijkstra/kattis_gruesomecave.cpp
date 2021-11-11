#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<ld, int, int> tdii;
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




vector<pii> dir{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<pii> getAdj(int i, int j, vector<vector<char>> &grid){
    vector<pii> ret;
    for(auto [di, dj]: dir){
        int nextI = i+di;
        int nextJ = j+dj;
        if(nextI < 0 || nextI >= grid.size() || nextJ < 0 || nextJ >= grid[0].size())continue;
        if(grid[nextI][nextJ] == ' ') ret.push_back({nextI, nextJ});
    }
    return ret;
}
vector<pii> getAdjSSSP(int i, int j, vector<vector<char>> &grid){
    vector<pii> ret;
    for(auto [di, dj]: dir){
        int nextI = i+di;
        int nextJ = j+dj;
        if(nextI < 0 || nextI >= grid.size() || nextJ < 0 || nextJ >= grid[0].size())continue;
        if(grid[nextI][nextJ] != '#') ret.push_back({nextI, nextJ});
    }
    return ret;
}


vector<vector<ld>> faster_dijkstra(int si, int sj, vector<vector<ld>> &riskProb, vector<vector<char>> &grid){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    long long n = riskProb.size();
    long long m = riskProb[0].size();
    vector<vector<ld>> dist(n, vector<ld>(m, 1));
    dist[si][sj] = 0;
    set<tdii> pq;
    FOR(i, n) FOR(j, m) pq.emplace(dist[i][j], i, j);
    while(pq.size()){
        auto [cost, i, j] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        vector<pii> nextCoords = getAdjSSSP(i, j, grid);
        for(auto [nextI, nextJ]:nextCoords){
            ld prob = riskProb[nextI][nextJ];
            if(dist[i][j] + prob >= dist[nextI][nextJ]) continue;
            pq.erase(pq.find({dist[nextI][nextJ], nextI, nextJ})); // O(E * log(V));
            dist[nextI][nextJ] = dist[i][j] + prob;
            pq.emplace(dist[nextI][nextJ], nextI, nextJ);
        }
    }
    return dist;
}


void solve() 
{
    // Weighted SSSDSP. To get the probability for each field, it is sufficient to add +1 to each vacant adj fielda if you at a vacant field already.
    // Meaning there is one way to go to this field.
    // Then just dividing by all the sums and you have the probability of being in a certein vacant field
    //
    // take-away: String cin + getline when white spaces are part of the implicit graph
    // take-away: Sometimes mat-pow does not work -> figure out (eigenvalues have to be smaller than 1)
    // take-away: Probability weights may be calculated easily with just counting the adj fields for each field;
    int n, m; cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m, '.'));
    vector<vector<int>> risk(n, vector<int>(m, 0));
    vector<vector<ld>> riskProb(n, vector<ld>(m, 0));
    string s; getline(cin, s);
    int si, sj;
    int di, dj;
    FOR(i, n){
        getline(cin, s);
        FOR(j, m){
            grid[i][j] = s[j];
            if(grid[i][j] == 'E'){
                si = i;
                sj = j;
            }
            if(grid[i][j] == 'D'){
                di = i;
                dj = j;
            }
        }
    }

    int riskTotal = 0;
    FOR(i, n){
        FOR(j, m){
            if(grid[i][j] == ' '){
                vector<pii> ret = getAdj(i, j, grid);
                for(auto [nextI, nextJ]: ret){
                    riskTotal++;
                    risk[nextI][nextJ]++;
                }
            }
        }
    }
    FOR(i, n){
        FOR(j, m){
            if(risk[i][j] > 0){
                riskProb[i][j] = (ld)risk[i][j]/riskTotal;
            }
        }
    }
    vector<vector<ld>> dis = faster_dijkstra(si, sj, riskProb, grid);
    cout << setprecision(10) << fixed << dis[di][dj];
        

}

