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

bool dfs(string cur, int col, unordered_map<string, int>&v, unordered_map<string, vector<string>> &AL, vector<string>&walter, vector<string> &jesse){
    v[cur] = col;
    if(col == 0){
        walter.push_back(cur);
    }else{
        jesse.push_back(cur);
    }
    for(string next: AL[cur]){
        if(v[next] == col) return false;
        if(v[next] == -1 && !dfs(next, col^1, v, AL, walter, jesse)) return false;
    }
    return true;
}

void solve() 
{
    // basic bicoloring problem.
    int n; cin >> n;
    unordered_map<string, vector<string>> AL;
    unordered_map<string, int> v;
    FOR(i, n){
        string s; cin >> s;
        v[s] = -1;
    }
    int m; cin >> m;
    FOR(i, m){
        string a, b; cin >> a >> b;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    vector<string> walter, jesse;

    for(auto [k, val]: v){
        if(val==-1){
            bool poss = dfs(k, 0, v, AL, walter, jesse);
            if(!poss){
                cout << "impossible";
                return;
            }
        }
    }
    FOR(i, walter.size()){
        cout << walter[i];
        if(i< walter.size()-1) cout << " ";
    }
    cout << endl;
    FOR(i, jesse.size()){
        cout << jesse[i];
        if(i< jesse.size()-1) cout << " ";
    }

}

