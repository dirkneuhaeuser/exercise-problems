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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    int l, n, m;
    while(cin >> l >> n >> m){
        if(l == 0 && n == 0 && m==0) break;
        vector<vector<vector<int>>> grid(l, vector<vector<int>>(n, vector<int>(m, -1)));
        queue<tiii> q;
        int kD=-1, iD=-1, jD=-1;
        FOR(k, l){
            FOR(i, n){
                FOR(j, m){
                    char c; cin >> c;
                    if(c == 'S'){
                        grid[k][i][j] = 0;
                        q.push({k, i, j});
                    }else if(c == '#'){
                        grid[k][i][j] = -2;
                    }else if(c == 'E'){
                        kD = k;
                        iD = i;
                        jD = j;
                    }
                }
            }
        }
        if(kD == -1){
            cout << "Trapped!" << endl;
            continue;
        }
        bool found = false;
        vector<tiii> dir{{1, 0, 0}, {-1, 0 ,0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
        while(q.size()){
            auto [k, i, j] = q.front(); q.pop();
            if(k == kD && i == iD && j == jD){
                found = true;
                cout << "Escaped in " << grid[k][i][j] <<  " minute(s)." << endl;
                break;
            }
            for(auto [dk, di, dj]: dir){
                int nextK = k  + dk;
                int nextI = i  + di;
                int nextJ = j  + dj;
                if(nextK < 0 || nextK >= l || nextI < 0 || nextI >= n || nextJ < 0 || nextJ >= m) continue;
                if(grid[nextK][nextI][nextJ] != -1) continue;
                grid[nextK][nextI][nextJ] =  grid[k][i][j] + 1;
                q.push({nextK, nextI, nextJ});
            }
            
        }
        if(!found){
            cout << "Trapped!" << endl;
        }

    }

}

