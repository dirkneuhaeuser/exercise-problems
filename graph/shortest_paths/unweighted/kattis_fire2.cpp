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
int grid[1000][1000];
void solve() 
{
    // SSMDSP Problem, here with two types: Fire type 1 and  you type 0. Type 1 will always be the first to propagate and then only type 2 can go ahead. If you meet a border:
    // stop
    int n, m; cin >> m >> n;
    int iP=-1, jP=-1;
    vector<tiii> q;
    FOR(i, n){
        FOR(j, m){
            char c; cin >> c;
            if(c == '#'){
                grid[i][j] = -2;
            }else if(c == '*'){
                q.push_back({i, j, 1});
                grid[i][j] = 1;
            }else if(c == '.'){
                grid[i][j] = -1;
            }else if(c == '@'){
                iP = i;
                jP = j;
                grid[i][j] = 1;
            }
        }
    }
    if(iP == -1){
        cout << 0;
        return;
    }
    q.push_back({iP, jP, 0});
    vector<pii> dir {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int sp = 1;
    while(q.size()){
        vector<tiii> nq;
        for(auto [i, j, type]: q){
            if(type == 0 && (i==0 || j==0 || i == n-1 || j == m-1)){
                cout << sp;
                return;
            }
            for(auto [di, dj]: dir){
                int nextI = i + di;
                int nextJ = j + dj;
                if(nextI <0 || nextI >= n || nextJ < 0 || nextJ >= m) continue;
                if(grid[nextI][nextJ] != -1) continue;
                grid[nextI][nextJ] = 1; // visited
                nq.push_back({nextI, nextJ, type});
            }
        }
        q = nq;
        sp++;
    }
    cout << "IMPOSSIBLE";
}

