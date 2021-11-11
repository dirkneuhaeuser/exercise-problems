#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int, int, int> tiiiii;
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
void solve() 
{
    // Weigted MSMDSP + parent reconstruction;
    // Note: Graph is no DAG, (you can also go up/left/rigth..) so no DP possible. But weighted MSMDSP problem -> Dijkstra
    int n, m;
    while(cin >> n >> m){
        if(n == 0 && m == 0)break;
        int grid[n][m];
        FOR(i, n){
            string l;
            cin >> l;
            FOR(j, m){
                int num = l[j] - '0';
                grid[i][j] = num;
            }
        }
        priority_queue<tiiiii, vector<tiiiii>, greater<tiiiii>> pq;
        vector<vector<int>> dis(n, vector<int>(m, INF));
        vector<pii> dir{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
        vector<vector<pii>> par(n, vector<pii>(m));
        FOR(j, m){
            pq.push({grid[0][j], 0, j, -1, -1});
        }
        while(pq.size()){
            auto [c, i, j, pI, pJ] = pq.top(); pq.pop();
            if(dis[i][j] <= c) continue;
            dis[i][j] = c;
            par[i][j] = {pI, pJ};
            for(auto [di, dj]: dir){
                int nextI = i+di;
                int nextJ = j+dj;
                if(nextI < 0 || nextJ < 0 || nextI > n-1 || nextJ > m-1) continue;
                if(dis[nextI][nextJ] <= dis[i][j] + grid[nextI][nextJ]) continue;
                pq.push({dis[i][j] + grid[nextI][nextJ], nextI, nextJ, i, j});
            }
        }

        int maxJ = -1;
        int sum = INF;
        for(int j = 0; j<m; ++j){
            if(dis[n-1][j] < sum){
                sum = dis[n-1][j];
                maxJ = j;
            }
        }
        pii cur = {n-1, maxJ};
        while(cur.first != -1){
            grid[cur.first][cur.second] = -1;
            cur = {par[cur.first][cur.second]};

        }
        FOR(i, n){
            FOR(j, m){
                if(grid[i][j] != -1){
                    cout << grid[i][j];
                }else{
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << endl;


    }


}

