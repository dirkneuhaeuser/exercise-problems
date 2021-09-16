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
        cout<<"Case #" << count++ << ":" << endl;
        solve(); 
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

int getNextHeight(int i, int j, vector<vector<int>> &grid){
    int ans = INF;
    if(i > 0) ans = min(ans, grid[i-1][j]);
    if(i<grid.size()-1)ans = min(ans, grid[i+1][j]);
    if(j > 0) ans = min(ans, grid[i][j-1]);
    if(j<grid[0].size()-1)ans = min(ans, grid[i][j+1]);
    return ans;
}

char dfs(int i, int j, queue<char> &letters, vector<vector<int>> &grid, vector<vector<char>> &ret){
    if(ret[i][j] != '!') return ret[i][j];
    int nextHeight = getNextHeight(i, j, grid);
    char let;
    if(grid[i][j] <= nextHeight){
        // sink
        let = letters.front(); letters.pop(); 
    }else if(i>0 && grid[i-1][j] == nextHeight){
        let = dfs(i-1, j, letters, grid, ret);
    }else if(j>0 && grid[i][j-1] == nextHeight){
        let = dfs(i, j-1, letters, grid, ret);
    }else if(j<(grid[0].size()-1) && grid[i][j+1] == nextHeight){
        let = dfs(i, j+1, letters, grid, ret);
    }else{
        let = dfs(i+1, j, letters, grid, ret);
    }
    ret[i][j] = let;
    return let;
}


void solve() 
{
    // Rather a dfs than a dp excersie
    int n, m; cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    vector<vector<char>> ret(n, vector<char>(m, '!'));
    queue<char> q;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    FOR(i, 26){
        q.push(alphabet[i]);
    }

    FOR(i, n){
        FOR(j, m){
            cin >> grid[i][j];
        }
    }
    FOR(i, n){
        FOR(j, m){
            if(ret[i][j] == '!'){
                dfs(i, j, q, grid, ret);
            }
        }
    }
    FOR(i, n){
        FOR(j, m){
            if(j < m-1) cout << ret[i][j] << " ";
            else cout << ret[i][j];
        }
        cout << endl;
    }




}

