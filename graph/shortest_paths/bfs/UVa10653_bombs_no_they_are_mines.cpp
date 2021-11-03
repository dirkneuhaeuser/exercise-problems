#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
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
    // Unweigted SSSDSP: basic 2D level bfs
    // Note: In order to save the already seen fields, we cannot use a set here, as to inefficient.
    int n,m;
    while(cin >> n >> m){
        if(n==0 && m == 0)break;
        vector<vector<bool>> grid(n, vector<bool>(m, false));
        int brows; cin >> brows;
        FOR(b, brows){
            int i; cin >> i;
            int t; cin >> t;
            FOR(l, t){
                int j; cin >> j;
                grid[i][j] = true;
            }
        }
        int startI, startJ;
        int endI, endJ;
        cin >> startI >> startJ >> endI >> endJ;
        vector<pii> q{{startI, startJ}};
        vector<vector<bool>> seen(n, vector<bool>(m, false));
        vector<pii> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int time = 0;
        while(q.size()){
            vector<pii> nq;
            for(auto [i,j]: q){
                if(i==endI && j == endJ){
                    cout << time << endl;
                    break;
                }
                for(auto [di, dj]: directions){
                    int nextI = i+di;
                    int nextJ = j+dj;
                    if(nextI<0 || nextI>n-1 || nextJ<0 || nextJ>m-1) continue;
                    if(grid[nextI][nextJ]==true)continue;
                    if(seen[nextI][nextJ] == true) continue;
                    seen[nextI][nextJ]=true;
                    nq.push_back({nextI, nextJ});
                }
            }
            time++;
            q = nq;
        }

    }

}

