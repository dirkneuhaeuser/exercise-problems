#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
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
const int INF = 1<<25;


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
    // APSP Problem. Precalculat the shortest path between all pairs and then, for each query go through each node and try to make a little error and save the best not best result
    // learned: Optimal subpaths AM[a][i] + AM[i][b] can often be used when the problem involves shortest paths with some restrictions
    int n, m; 
    int cnt = 1;
    while(cin >> n >> m){
        vector<vector<int>> AM(n, vector<int>(n, INF));
        vector<vector<pii>> AL(n);
        cout << "Set #" << cnt++ << endl;
        FOR(j, m){
            int a, b, c; cin >> a >> b >> c;
            AM[a][b] = c;
            AM[b][a] = c;
            AL[a].push_back({b, c});
            AL[b].push_back({a, c});
        }
        FOR(i, n){
            AM[i][i] = 0;
        }
        FOR(k, n) FOR(i, n) FOR(j, n){ // O(N^3)
            AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
        }
        int q; cin >> q;
        FOR(k, q){
            int a, b; cin >> a >> b;
            int best = AM[a][b];
            int secondBest = INF;
            if(AM[a][b] == INF){
                cout << "?" << endl;
                continue;
            }
            FOR(i, n){
                if(AM[a][i] < INF && AM[i][b] < INF){
                    for(auto [next, w]: AL[i]){ // O(E)
                        if(AM[next][b] < INF){
                            int pot = AM[a][i] + w + AM[next][b];
                            if(pot  < secondBest && pot > best){
                                secondBest = pot;
                            }
                        }
                        int pot = AM[a][i] + 2*w + AM[i][b];
                        if(pot  < secondBest && pot > best){
                            secondBest = pot;
                        }

                    }
                }
            }
            if(secondBest != INF){
                cout << secondBest << endl;
            }else{
                cout << "?" << endl;
            }

        }
    }

}

