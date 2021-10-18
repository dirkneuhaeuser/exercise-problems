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
vector<vector<int>> AL;
vector<int> colors;
void dfs(int cur, int col){
    colors[cur] = col;
    for(int next: AL[cur]){
        if(colors[next] == -1){
            dfs(next, col^1);
        }
    }
}
void solve() 
{
    // weak bicoloring (do not check if neihbours have same color)
    // Not possible iff a connected component consists of only one node
    int n, m;
    cin >> n >> m;
    colors.assign(n, -1);
    AL.assign(n, vector<int>());
    vector<int> inDegree(n, 0);
    FOR(i, m){
        int a, b; cin >> a >> b;
        a--; b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
        inDegree[a]++;
        inDegree[b]++;
    }
    FOR(i, n){
        if(inDegree[i] == 0){
            cout <<"Impossible";
            return;
        }
        if(colors[i] == -1){
            dfs(i, 0);
        }
    }

    FOR(i, n){
        if(colors[i]==1){
            cout << "pub";
        }else{
            cout << "house";
        }
        if(i < n-1) cout << " ";
    }


}

