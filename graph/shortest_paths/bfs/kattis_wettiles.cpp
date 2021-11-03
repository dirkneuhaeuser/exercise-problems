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
    int n, m, t, l, walls; 
    while(cin >> m >> n >> t >> l >> walls){
        vector<vector<int>> grid(n, vector<int>(m, -1)); // -1 unvisited // -2 walls;
        vector<pii> q;
        int ret = 0;
        FOR(i, l){
            int a, b; cin >> b >> a;
            a--; b--;
            grid[a][b] = 1;
            q.push_back({a, b});
        }
        FOR(i, walls){
            int ai, aj; cin >> aj >> ai;
            int bi, bj; cin >> bj >> bi;
            ai--; aj--;
            bi--; bj--;
            if(ai == bi || aj == bj){
                if(ai > bi)swap(ai, bi);
                if(aj > bj)swap(aj, bj);
                for(int x=ai; x<=bi; ++x){
                    for(int y=aj; y<=bj; ++y){
                        grid[x][y]=-2;
                    }
                }
            }else{
                int dis = abs(bi-ai);
                int sign1 = bi > ai?1:-1;
                int sign2 = bj > aj?1:-1;
                //cout << ai << " " << aj << " " << bi << " " << bj <<endl;
                FOR(i, dis+1){
                    //cout << ai + sign1*(int)i << " " << aj + sign2*(int)i <<endl;
                    grid[ai + sign1*(int)i][aj + sign2*(int)i] = -2;
                }
            }
        }
        //dbg(grid);
        vector<pii> dir{{1, 0},{-1, 0}, {0, 1}, {0, -1}};
        int tt = 2;
        while(q.size()){
            vector<pii> nq;
            for(auto [i, j]: q){
                ret++;
                for(auto [di, dj]: dir){
                    int nextI = i+di;
                    int nextJ = j+dj;
                    if(nextI < 0 || nextJ < 0 || nextI >= n|| nextJ >= m) continue;
                    if(grid[nextI][nextJ] == -1 && t>1){
                        grid[nextI][nextJ] = tt;
                        nq.push_back({nextI, nextJ});
                    }
                }
            }
            t--;
            tt++;
            if(t==0) break;
            q=nq;
        }
        //dbg(grid);
        cout << ret << endl;

    }

}

