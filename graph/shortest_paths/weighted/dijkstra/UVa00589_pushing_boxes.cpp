#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int, int, int> tiiiii;
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

struct State{
    int curI, curJ, boxI, boxJ, pushes=0;
    string path="";
    State(int _curI, int _curJ, int _boxI, int _boxJ): curI(_curI), curJ(_curJ), boxI(_boxI), boxJ(_boxJ){};
    friend bool operator < (const State &a, const State &b){
        if(a.pushes > b.pushes) return true;
        if(a.pushes < b.pushes) return false;
        return a.path.size() > b.path.size();
    }
};


bool isOk(int i, int j, vector<vector<char>> &grid){
    return !(i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] !='.');
}





void solve() 
{
    // Advanced unweighted SSSP Problem with simultanoues states (you and box).
    // Here however we need to use a priority_queue (like in weighted shortest paths problems) to prefer pathes with fewer pushes/smaller path length
    // If we have seen a state (my position + box postion) we don't need to recompute it, as we were there already with smaller pushes or smaller path length.
    // O(r*c*r*c * log(r*c*r*c))
    int n,m; 
    int cnt = 1;
    while(cin >> n >> m){
        if(n==0 && m==0)break;
        vector<vector<char>> grid(n, vector<char>(m, '.'));
        State s(-1, -1, -1, -1);
        int iT=-1, jT =-1;
        FOR(i, n){
            FOR(j, m){
                cin >> grid[i][j];
                if(grid[i][j] == 'T'){
                    grid[i][j] = '.';
                    iT = i;
                    jT = j;
                }
                if(grid[i][j] == 'S'){
                    grid[i][j] = '.';
                    s.curI = i;
                    s.curJ = j;
                }
                if(grid[i][j] == 'B'){
                    grid[i][j] = '.';
                    s.boxI = i;
                    s.boxJ = j;
                }
            }
        }

        int total = INF;
        string ret = "";
        priority_queue<State> pq;
        bool visited[n][m][n][m];
        memset(visited, 0, sizeof visited);
        pq.push(s);
        visited[s.curI][s.curJ][s.boxI][s.boxJ] = true;
        vector<pii> dir {{1, 0}, {-1, 0}, {0, 1}, {0,-1}};
        string dirPath = "snew";
        string dirPathBox = "SNEW";
        while(pq.size()){
            State cur = pq.top(); pq.pop();
            if(cur.pushes > total)break;
            if(cur.boxI == iT && cur.boxJ == jT){
                if(cur.pushes == total){
                    if(ret.size() > cur.path.size()){
                        ret = cur.path;
                    }
                }else if(cur.pushes < total){
                    ret = cur.path;
                    total = cur.pushes;

                }
                continue;
            }
            for(int i=0; i<4; ++i){
                auto [di, dj] = dir[i];
                State newState = cur;
                newState.curI += di;
                newState.curJ += dj;
                if(!isOk(newState.curI, newState.curJ, grid)) continue;
                if(newState.curI == newState.boxI && newState.curJ == newState.boxJ){
                    // pushed box;
                    if(!isOk(newState.boxI + di, newState.boxJ + dj, grid)) continue;
                    newState.boxI += di;
                    newState.boxJ += dj;
                    newState.pushes++;
                    newState.path += dirPathBox[i];
                }else{
                    newState.path += dirPath[i];
                }
                if(visited[newState.curI][newState.curJ][newState.boxI][newState.boxJ]) continue;
                visited[newState.curI][newState.curJ][newState.boxI][newState.boxJ] = true;
                pq.push(newState);
            }
        }
        cout << "Maze #" << cnt++ << endl;
        if(total == INF){
            cout << "Impossible."  << endl;
        }else{
            cout << ret << endl;
        }
        cout << endl;
    }

}

