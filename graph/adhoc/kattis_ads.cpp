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

bool isAllowed(char a){
    return (isalpha(a) || isdigit(a) || a=='?' || a=='!' || a==',' || a=='.' || a==' ');
}

// copy all primary
void dfs(int i, int j, vector<vector<char>> &grid, vector<vector<char>> &ret){
    ret[i][j] = grid[i][j];
    grid[i][j]=3;
    if(i>0 && grid[i-1][j] != '+' && ret[i-1][j]== 0) dfs(i-1, j, grid, ret);
    if(j>0 && grid[i][j-1] != '+' && ret[i][j-1]== 0) dfs(i, j-1, grid, ret);
    if(i<grid.size()-1 && grid[i+1][j] != '+' && ret[i+1][j]== 0) dfs(i+1, j, grid, ret);
    if(j<grid[0].size()-1 && grid[i][j+1] != '+' && ret[i][j+1]== 0) dfs(i, j+1, grid, ret);
}
vector<vector<bool>> v;
void dfsColorBorder(int i, int j, vector<vector<char>> &grid){
    v[i][j] = true;
    if(i>0 && grid[i-1][j] == '+' && v[i-1][j] == false) dfsColorBorder(i-1, j, grid);
    if(j>0 && grid[i][j-1] == '+' && v[i][j-1] == false) dfsColorBorder(i, j-1, grid);
    if(i<grid.size()-1 && grid[i+1][j] == '+' && v[i+1][j] == false) dfsColorBorder(i+1, j, grid);
    if(j<grid[0].size()-1 && grid[i][j+1] == '+' && v[i][j+1] == false) dfsColorBorder(i, j+1, grid);
}
void existForbidden(int i, int j, vector<vector<char>> &grid, bool &ans){
    v[i][j] = true;
    if(!isAllowed(grid[i][j])) ans = false;
    if(i>0 && grid[i-1][j] != '+' && v[i-1][j]== 0) existForbidden(i-1, j, grid, ans);
    if(j>0 && grid[i][j-1] != '+' && v[i][j-1]== 0) existForbidden(i, j-1, grid, ans);
    if(i<grid.size()-1 && grid[i+1][j] != '+' && v[i+1][j]== 0) existForbidden(i+1, j, grid, ans);
    if(j<grid[0].size()-1 && grid[i][j+1] != '+' && v[i][j+1]== 0) existForbidden(i, j+1, grid, ans);


}
void dfsDeleteImage(int i, int j, vector<vector<char>> &grid, vector<vector<char>> &ret){
    int n=0, m=0;
    for(int ii =i; ii<grid.size(); ++ii){
        if(grid[ii][j] == '+') n++;
        else break;
    }
    for(int jj =j; jj<grid[0].size(); ++jj){
        if(grid[i][jj] == '+') m++;
        else break;
    }
    for(int ii =i; ii <i+n; ii++){
        for(int jj =j; jj <j+m; jj++){
            grid[ii][jj]=3;
            ret[ii][jj] = ' ';
        }
    }
}

void dfsCopyImage(int i, int j, vector<vector<char>> &grid, vector<vector<char>> &ret){
    ret[i][j]= grid[i][j];
    grid[i][j]=3;
    if(i>0 && grid[i-1][j] != 3 && v[i-1][j]== 1) dfsCopyImage(i-1, j, grid, ret);
    if(j>0 && grid[i][j-1] != 3 && v[i][j-1]== 1) dfsCopyImage(i, j-1, grid, ret);
    if(i<grid.size()-1 && grid[i+1][j] != 3 && v[i+1][j]== 1) dfsCopyImage(i+1, j, grid, ret);
    if(j<grid[0].size()-1 && grid[i][j+1] != 3 && v[i][j+1]== 1) dfsCopyImage(i, j+1, grid, ret);
}


void solve(){
    int n, m; cin >> n >> m;
    vector<vector<char>> grid(n+2, vector<char>(m+2, '.')),  ret(n+2, vector<char>(m+2, 0));
    string line; 
    getline(cin, line);
    FOR(i, n){
        getline(cin, line);
        FOR(j, m){
            grid[i+1][j+1] = line[j];
        }
    }
    dfs(0, 0, grid, ret);
    for(int i=1; i<n+1; ++i){
        for(int j=1; j<m+1; ++j){
            if(grid[i][j] == '+'){
                v.assign(n+2, vector<bool>(m+2, false));
                dfsColorBorder(i, j, grid);
                bool allowed = true;
                existForbidden(i+1, j+1, grid, allowed);
                if(!allowed){
                    dfsDeleteImage(i, j, grid, ret);
                }else{
                    dfsCopyImage(i, j, grid, ret);
                }
            }
        }
    }
    //dbg(grid);
    //dbg(ret);
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            cout << ret[i][j];
        }
        cout << endl;
    }



}

