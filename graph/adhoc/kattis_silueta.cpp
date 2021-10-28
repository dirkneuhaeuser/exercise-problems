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

void drawSingle(int l, int r, int h, vector<vector<char>> &grid){
    for(int i=1000-1; i>= 1000-h; i--){
        grid[i][l] = 'x';
        grid[i][r-1] = 'x';
    }
    for(int j = l; j<= r-1; ++j){
        grid[1000-h][j] = 'x';
    }

}
void drawAbscissa(vector<vector<char>> &grid){
    for(int j=0; j<grid[0].size(); ++j){
        grid[1000][j] = '*';
    }

}

int dfsColorBorder(int i, int j, vector<vector<char>> &grid){
    int m = grid[0].size();
    grid[i][j]='#';
    int perimeter = 1;
    if(i>0 && grid[i-1][j] == 'x'){
        return perimeter + dfsColorBorder(i-1, j, grid);
    }
    if(j< m && grid[i][j+1] == 'x'){
        return perimeter + dfsColorBorder(i, j+1, grid);
    }
    if(i < 999 && grid[i+1][j] == 'x'){
        return perimeter + dfsColorBorder(i+1, j, grid);
    }
    return perimeter;
}

vector<pair<int, int>> directions = {{-1, 0}, {0, +1}, {1, 0}, {0, -1}};
vector<vector<bool>> seen;
void deleteInside(int i, int j, vector<vector<char>> &grid){
    seen[i][j] = true;
    grid[i][j]='.';
    for(auto [iD, jD]: directions){
        int nextI = i + iD;
        int nextJ = j + jD;
        if(nextI>=0 && nextI < 1000 && nextJ >=0 && nextJ <1000 && grid[nextI][nextJ] != '#' && seen[nextI][nextJ] == false){
            deleteInside(nextI, nextJ, grid);
        }
    }
}

int unionfy(vector<vector<char>> &grid){
    int m = grid[0].size();
    int perimeter = 0;
    bool open = false;
    for(int j=0; j<m; ++j){
        if(!open && grid[1000-1][j] == 'x'){
            open = true;
            perimeter+=dfsColorBorder(999, j, grid);
        }else if(open && (grid[1000-1][j] == 'x' || grid[1000-1][j] == 'z')){
            grid[999][j] = 'Z';
            deleteInside(999, j, grid);
        }else if(open && grid[1000-1][j] == '#'){
            open = false;
        }
    }
    return perimeter;
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
    // 2D grid travesal. 1. color the outer siluette from each building in a different color and then delete everthing inside.
    // Biggest Difficulty is to undertstand the concept of perimeter, which are all '#' fields + the specific '*' fields the building is build upon (this also is part of the building)
    int n; cin >> n;
    vector<vector<char>> grid(1001, vector<char>(1000, '.'));
    int left = 1001;
    int right = 0;
    int height = 0;
    FOR(i, n){
        int a, b, c; cin >> a >> b >> c;
        left = min(left, a);
        right = max(right, b-1);
        height = max(height, c);
        drawSingle(a, b, c, grid);
    }
    drawAbscissa(grid);
    seen.assign(1001, vector<bool>(1000, false));
    int perimeter = unionfy(grid);
    for(int j = left; j<=right; ++j){
        if(grid[999][j] == '#'){
            if(j == left || j ==  right -1) perimeter++;
            else if(grid[999][j-1] != '#' || grid[999][j+1] != '#') perimeter++;
        }
    }
    cout << perimeter << endl;

    for(int i=1000-height; i<=1000; ++i){
        for(int j=left; j<=right; ++j){
            cout << grid[i][j];
        }
        cout << endl;
    }

}

