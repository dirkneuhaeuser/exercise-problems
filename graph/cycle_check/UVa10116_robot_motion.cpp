#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long, long> pll;
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

enum {VISITED=-2, UNVISITED=-3, BACKWARD=-4};

// returns {x, y} which means, that there are in total x steps of which y are before the loop. 
// if y==-1 then there is no loop
pair<int, int> dfs(int curI, int curJ, vector<vector<char>> &grid, vector<vector<int>> &vis){
    vis[curI][curJ] = VISITED;
    char curC = grid[curI][curJ];
    pii ans;
    if(curC == 'N'){
        if(curI == 0) return {1, -1};
        if(vis[curI-1][curJ] == VISITED){
            vis[curI-1][curJ] = BACKWARD;
            return {1, -1};
        }
        ans = dfs(curI-1, curJ, grid, vis);
    }else if(curC == 'S'){
        if(curI == grid.size()-1) return {1, -1};
        if(vis[curI+1][curJ] == VISITED){
            vis[curI+1][curJ] = BACKWARD;
            return {1, -1};
        }
        ans = dfs(curI+1, curJ, grid, vis);
    }else if(curC == 'W'){
        if(curJ == 0) return {1, -1};
        if(vis[curI][curJ-1] == VISITED){
            vis[curI][curJ-1] = BACKWARD;
            return {1, -1};
        }
        ans = dfs(curI, curJ-1, grid, vis);
    }else{
        if(curJ == grid[0].size()-1) return {1, -1};
        if(vis[curI][curJ+1] == VISITED){
            vis[curI][curJ+1] = BACKWARD;
            return {1, -1};
        }
        ans = dfs(curI, curJ+1, grid, vis);
    }
    if(vis[curI][curJ] == BACKWARD){
        ans.second=0;
    }else if(ans.second>=0){
        ans.second++;
    }
    return {ans.first+1, ans.second};
}



void solve() 
{
    // very easy cycle check. In the implicit graph there is always only one way (forward edges are not possible,
    // hence it is sufficient to check if the next grid element has been already visited to find a cycle;
    int n, m, c; 
    while(cin >> n >> m >> c){
        if(n==0 && m==0 && c==0){
            break;
        }
        vector<vector<char>> grid(n, vector<char>(m, '!'));
        FOR(i, n){
            FOR(j, m){
                cin >> grid[i][j];
            }
        }
        vector<vector<int>> vis(n, vector<int>(m, UNVISITED));
        pii ans =dfs(0, c-1, grid, vis);
        if(ans.second == -1){
            cout << ans.first << " step(s) to exit" << endl;
        }else{
            cout << ans.second << " step(s) before a loop of " << ans.first-ans.second <<" step(s)" << endl;
        }
        //dbg(ans);


    }
}

