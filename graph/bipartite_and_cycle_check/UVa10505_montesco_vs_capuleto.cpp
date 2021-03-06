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
    
    int t=1; 
    cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

vector<int> colors;

pair<int, int> dfs(int idx, int c1, int c2, vector<set<int>> &AL, bool &isBipartite){
    colors[idx] = c1;
    pii ret;
    if(c1 < c2){
        ret = {1, 0};
    }else{
        ret = {0, 1};
    }
    for(int next: AL[idx]){
        if(colors[next] == -1){
            pii ans = dfs(next, c2, c1, AL, isBipartite);
            ret.first += ans.first;
            ret.second += ans.second;
        }else if(colors[next] == c1){
            isBipartite = false; // indicating that the current graph is not bipartite;
        }
    }
    return ret;

}


void solve() 
{
    // For each connected compontents, check if it is bipartite and then get the max partition of it (left or right) and add it to the result.
    // Note: The problem is very bad formulated.
    int n; cin >> n;
    vector<set<int>> AL(n, set<int>());

    FOR(i, n){
        int m; cin >> m;
        FOR(j, m){
            int enemy; cin >> enemy;
            enemy--;
            if(enemy < n && enemy >=0){
                AL[i].insert(enemy);
                AL[enemy].insert(i);
            }
        }
    }
    colors.assign(n, -1);
    int idx = 0;
    int ret = 0;
    FOR(i, n){
        if(colors[i] == -1){
            bool isBipartite = true;
            pii ans = dfs(i, idx, idx+1, AL, isBipartite);
            if(isBipartite){
                ret += max(ans.first, ans.second);
            }
            idx+=2;
        }
    }
    cout << ret;


}

