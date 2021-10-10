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

tuple<int, int, int> moveUp(int curPointingBottom, int curPointingUp, int curPointingLeft){
    return {curPointingUp, 7-curPointingBottom, curPointingLeft};
}
tuple<int, int, int> moveDown( int curPointingBottom, int curPointingUp, int curPointingLeft){
    return {7-curPointingUp, curPointingBottom, curPointingLeft};
}
tuple<int, int, int> moveLeft( int curPointingBottom, int curPointingUp, int curPointingLeft){
    return {curPointingLeft, curPointingUp, 7 - curPointingBottom};
}
tuple<int, int, int> moveRight( int curPointingBottom, int curPointingUp, int curPointingLeft){
    return {7-curPointingLeft, curPointingUp, curPointingBottom};
}

void dfs(int iCur, int jCur, int curPointingBottom, int curPointingUp, int curPointingLeft, vector<vector<int>> &v, vector<vector<char>> &grid){
    v[iCur][jCur] = curPointingBottom;
    if(grid[iCur-1][jCur] == '#' && v[iCur-1][jCur] == -1){
        auto [nb, nu, nl] = moveUp(curPointingBottom, curPointingUp, curPointingLeft);
        dfs(iCur-1, jCur, nb, nu, nl, v, grid);
    }
    if(grid[iCur][jCur-1] == '#' && v[iCur][jCur-1] == -1){
        auto [nb, nu, nl] = moveLeft(curPointingBottom, curPointingUp, curPointingLeft);
        dfs(iCur, jCur-1, nb, nu, nl, v, grid);
    }
    if(grid[iCur+1][jCur] == '#' && v[iCur+1][jCur] == -1){
        auto [nb, nu, nl] = moveDown(curPointingBottom, curPointingUp, curPointingLeft);
        dfs(iCur+1, jCur, nb, nu, nl, v, grid);
    }
    if(grid[iCur][jCur+1] == '#' && v[iCur][jCur+1] == -1){
        auto [nb, nu, nl] = moveRight(curPointingBottom, curPointingUp, curPointingLeft);
        dfs(iCur, jCur+1, nb, nu, nl, v, grid);
    }
}

bool check(vector<vector<int>> &v){
    set<int> all;
    FOR(i, 8){
        FOR(j, 8){
            if(v[i][j] != -1){
                all.insert(v[i][j]);
            }
        }
    }
    return all.size() == 6;
}

void solve() 
{
    // Dfs problem. when we find the first dice field, we assume it to be 1 (because of ismorphism here). When the 1 of the dice is facing at the bottom there are 4 possibilites of 
    // the alignment of the dice. Again because of isomorphism we can choose any of these 4 alginment. Now we only have to dfs and unfold the dice and check if all 6 elements of connected componennt have different numbers (1-6).
    int n = 8;
    vector<vector<char>> grid(8, vector<char>(8, '.'));
    FOR(i, 6){
        FOR(j, 6){
            cin >> grid[i+1][j+1];
        }
    }
    vector<vector<int>> v;
    for(int i=1; i<=6; ++i){
        for(int j=1; j<=6; ++j){
            if(grid[i][j] == '#'){
                // 1 bottom, 4 up, 3 left;
                v.assign(8, vector<int>(8, -1));
                dfs(i, j, 1, 4, 5, v, grid);
                if(check(v)){
                    cout  <<"can fold";
                    return;
                }
                cout  <<"cannot fold";
                return;
                
            }
        }
    }




}

