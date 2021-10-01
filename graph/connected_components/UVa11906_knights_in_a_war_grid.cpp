#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
// 2**6 =  64                           // 4!  = 24                       
// 2**8 =  256                          // 5!  = 120                      
// 2**10 = 1,024                        // 6!  = 720
// 2**15 = 32,768                       // 7!  = 5,040
// 2**20 = 1,048,576                    // 8!  = 40,320
// 2**25 = 33,554,432                   // 9!  = 362,880
// 2**30 = 1,073,741,824                // 10! = 3,628,800
// 2**32 = 4,294,967,296                // 12! = 479,001,600
                                        // 14! = 87,178,291,200
// int up to  2*10^9 (2^31-1)           // 16! = 20,922,789,888,000
// ll up to   9*10^18 (2^63 -1)         // 18! = 6,402,373,705,728,000
// ull up to 18*10^18 (2^64-1)/         // 20! = 2,432,902,008,176,640,000                                                                    
// ld up to  10*10^307
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
    int count = 1;
    while(t--) 
    { 
        cout<<"Case " << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 


void dfs(int i, int j, vector<vector<int>> &grid, int nn, int mm){
    grid[i][j] = -2;
    int ans = 0;
    int n=nn, m=mm;
    bool start = true;
    for(int k=0; k<2; ++k){
        if(!start && nn == mm) break;
        if(!start) swap(n, m);
        if(i>=n && j >=m){
            if(grid[i-n][j-m] != -3) ans++;
            if(grid[i-n][j-m] == -1) dfs(i-n, j-m, grid, n, m);
        }
        if(n>0 && i+n < grid.size() && j >=m){ // avoid double counting
            if(grid[i+n][j-m] != -3) ans++;
            if(grid[i+n][j-m] == -1) dfs(i+n, j-m, grid, n, m);
        }
        if(m>0){ // avoid double counting
            if(i>=n && j+m < grid[0].size()){
                if(grid[i-n][j+m] != -3) ans++;
                if(grid[i-n][j+m] == -1) dfs(i-n, j+m, grid, n, m);
            }
            if(n>0 && i+n < grid.size() && j+m  < grid[0].size()){ // avoid double counting
                if(grid[i+n][j+m] != -3) ans++;
                if(grid[i+n][j+m] == -1) dfs(i+n, j+m, grid, n, m);
            }
        }
        start = false;
    }
    grid[i][j] =ans;

}


void solve() 
{
    // normal dfs with some edge cases for (n==0 or m ==0) or (n==m) (not finding connected components)
    int r, c, n, m; cin >> r >> c >> n >> m;
    int w; cin >> w;
    vector<vector<int>> grid(r, vector<int>(c, -1)); // -1 unvisited, -2 visited(but not yet calculated), -3 water
    FOR(i, w){
        int a, b; cin >> a >> b;
        grid[a][b] = -3;
    }
    dfs(0, 0, grid, n, m);

    int even=0, odd=0;
    for(int i =0; i<r; ++i){
        for(int j=0; j<c; ++j){
            if(grid[i][j]>=0){
                odd += ((grid[i][j]&1)==1);
                even += ((grid[i][j]&1)==0);
            }
        }
    }
    cout << even << " " << odd;

}

