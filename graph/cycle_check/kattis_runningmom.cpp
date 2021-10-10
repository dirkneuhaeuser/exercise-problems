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

enum {UNVISITED=-1, EXPLORED=-2, VISITED=-3};

bool dfs(int cur, vector<vector<int>> &al, vector<int> &vis){
    vis[cur] = EXPLORED;
    for(int next: al[cur]){
        if(vis[next] == EXPLORED){ // backward edge creats a cycle
            return true;
        }else if(vis[next]==UNVISITED){
            if(dfs(next,al, vis))return true;
        }
    }
    vis[cur] = VISITED;
    return false;
}



void solve() 
{
    // Basic cycle check. Let the dfs return true if you find a backward edge.
    int m; cin >> m;
    unordered_map<string, int> name2Idx;
    vector<vector<int>> al;
    int idx = -1;
    FOR(i, m){
        string a, b; cin >> a >> b;
        if(name2Idx.count(a)==0){
            name2Idx[a]=++idx;
        }
        if(name2Idx.count(b)==0){
            name2Idx[b]=++idx;
        }
        if(name2Idx[a] >= al.size()){
            vector<int> newL{name2Idx[b]};
            al.push_back(newL);
        }else{
            al[name2Idx[a]].push_back(name2Idx[b]);
        }

        if(name2Idx[b] >= al.size()){
            vector<int> newL{};
            al.push_back(newL);
        }
    }
    string city;
    int n = al.size();
    while(cin >> city){
        vector<int> v(n, UNVISITED);
        int idx = name2Idx[city];
        bool safe = dfs(idx, al, v);
        if(safe){
            cout << city << " safe" << endl;
        }else{
            cout << city << " trapped" << endl;
        }
    }
}

