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
void solve() 
{
    // Unweigted SSSDSP: basic 2D level bfs.
    // 1. Mark all fields which are not visible (where knights can go)
    // 2. Standard BFS
    int n, m;cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m,'.'));
    int iA, jA;
    FOR(i, n){
        FOR(j, m){
            cin >> grid[i][j];
            if(grid[i][j]=='A'){
                iA = i;
                jA = j;
                grid[i][j] = 'X';
            }
        }
    }
    vector<pii> dir{{-2, 1}, {-2,-1}, {2, -1}, {2, 1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    FOR(i, n){
        FOR(j, m){
            if(grid[i][j] == 'Z'){
                for(auto [di, dj]: dir){
                    int nextI = (int)i+di;
                    int nextJ = (int)j+dj;
                    if(nextI<0|| nextJ <0|| nextI >=n || nextJ >= m) continue;
                    if(grid[nextI][nextJ] == 'A' || grid[nextI][nextJ] == 'B' || grid[nextI][nextJ] == 'Z') continue;
                    grid[nextI][nextJ] = 'X';
                }
            }
        }
    }
    vector<vector<int>> v(n, vector<int>(m, false));
    v[iA][jA] = true;
    vector<pii> dirBFS{{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    vector<pii> q{{iA, jA}};
    int times = 0;
    bool poss = false;
    while(q.size()){
        vector<pii> nq;
        for(auto [i, j]: q){
            if(grid[i][j] == 'B'){
                poss = true;
                cout << "Minimal possible length of a trip is ";
                cout << times;
            }
            if(poss)break;
            for(auto [di, dj]: dirBFS){
                int nextI = i + di;
                int nextJ = j + dj;
                if(nextI < 0 || nextJ < 0 || nextI > n-1 || nextJ >m-1) continue;
                if(grid[nextI][nextJ] == 'X' || grid[nextI][nextJ] == 'Z') continue;
                if(v[nextI][nextJ]) continue;
                v[nextI][nextJ] = true;
                nq.push_back({nextI, nextJ});
            }
        }
        if(poss)break;
        q = nq;
        times++;
    }
    if(!poss){
        cout <<"King Peter, you can't go now!";
    }


}

