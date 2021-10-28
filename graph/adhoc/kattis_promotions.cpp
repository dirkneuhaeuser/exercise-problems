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


vector<bitset<5000>> memo;
vector<bitset<5000>> memoRev;
vector<int> v;

bitset<5000> dfsAfterCur(int cur, vector<vector<int>> &AL, bool rev){
    bitset<5000> &after = rev?memoRev[cur]:memo[cur];
    if(v[cur]) return after;
    v[cur]  = 1;
    after.set(cur);
    for(int next: AL[cur]){
        after = after|dfsAfterCur(next, AL, rev);
    }
    return after;

}



void solve(); int main() 
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
    // to count if promotion is possible, we have to know the number of nodes after the current node in the DAG. As often, we don't want to overcount. Therfore, use a bitset and do only
    // two dfs. Atlernative: Do a dfs for each node and use a color to know if you have already useed this vertex
    int prom1, prom2, n, m;
    cin >> prom1 >> prom2 >> n >> m;
    vector<vector<int>>AL(n, vector<int>());
    vector<vector<int>>ALRev(n, vector<int>());
    FOR(i, m){
        int a, b;
        cin >> a >> b;
        AL[a].push_back(b);
        ALRev[b].push_back(a);
    }
    v.assign(n, 0);
    memo.assign(n, bitset<5000>());
    FOR(i, n){
        dfsAfterCur(i, AL, 0);
    }
    v.assign(n, 0);
    memoRev.assign(n, bitset<5000>());
    FOR(i, n){
        dfsAfterCur(i, ALRev, 1);
    }
    int a=0, b=0, notb=0;
    for(int i=0; i<n; ++i){
        if (n-memo[i].count() < prom1){
            a++;
        }
        if (n-memo[i].count() < prom2) b++;
        if (memoRev[i].count() > prom2) notb++;
    }
    cout << a << endl << b << endl <<notb;
}

