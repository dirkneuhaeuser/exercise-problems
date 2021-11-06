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
    // Task translated: Find the smallest non-trival cycle. 
    // Non-trivial: You cannot take 2 connected trees as a cycle as you need to be connected even after deleting an edege
    // Solution:
    // BFS from each node and once you find a node, which you have already seen: add up the distances
    int n, m; cin >> n >> m;
    vector<vector<int>> AL(n, vector<int>());
    FOR(i,m){
        int a, b; cin >> a >> b;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    int ret = INF;
    FOR(i, n){
        vector<int> dis(n, INF);
        vector<int> par(n, -1);
        dis[i] = 0;
        queue<int> q;
        q.push(i);
        while(q.size()){
            int cur = q.front(); q.pop();
            for(int next: AL[cur]){
                if(next != par[cur]){
                    if(dis[next] != INF){
                        int ans = dis[cur] + dis[next] + 1; // distance of the cycle
                        ret = min(ret, ans);
                    }else{
                        q.push(next);
                        dis[next] = dis[cur] + 1;
                        par[next] = cur;
                    }
                }
            }
        }
    }
    if(ret == INF){
        cout << "impossible";
    }else{
        cout << ret;
    }

}

