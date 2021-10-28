#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
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


set<pair<int,int>> seen;
bool dfs(int ii, int jj, vector<string> &grid, vector<int> &moves, vector<int> &ret){
    if(grid[ii][jj] == 'X') return false;
    if(jj == grid[0].size()-1){ 
        ret = moves;
    }
    if(ret.size() > 0){
        return true;
    }
    seen.insert({ii, jj});
    if(seen.count({max(ii-1, 0), jj+1}) == 0){ // go up
        moves[jj] = 1;
        if(dfs(max(ii-1, 0), jj+1, grid, moves, ret)) return true;
    }
    if(seen.count({min(ii+1, 9), jj+1}) == 0){ // stay the same
        moves[jj] = 0;
        if(dfs(min(ii+1, 9), jj+1, grid, moves, ret)) return true;
    }
    return false;
}


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
    // basic dfs, but bad description of what is allowed and what not.
    int n; cin >> n;
    vector<string> grid;
    string line;
    getline(cin, line);
    FOR(i, 10){
        getline(cin, line);
        grid.push_back(line);
    }
    vector<int> moves(n, 0);
    vector<int> ret;
    bool ans = dfs(9, 0, grid, moves, ret);
    int cnt = 0;
    int start=0;
    vector<pii> pushIntervals;
    for(int i=0; i<ret.size();++i){
        if(ret[i]){
            if(cnt>0){
                cnt++;
            }else{
                start = i;
                cnt = 1;
            }
        }else{
            if(cnt > 0){
                pushIntervals.push_back({start, cnt});
                cnt = 0;
            }
        }
    }
    if(cnt > 0){
        pushIntervals.push_back({start, cnt});
    }
    cout << pushIntervals.size() << endl;
    for(auto [s, t]: pushIntervals){
        cout << s << " " << t << endl;
    }


}

