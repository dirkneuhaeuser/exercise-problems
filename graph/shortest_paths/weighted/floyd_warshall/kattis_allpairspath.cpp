#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<long long, bool> plb;
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
const ll INF = 1<<30;


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
    // Basic APSP + neg. cycle detection: If there is one k such that there is a path from i to k and from k to j and also AM[k][k] < 0, then we can make the way from i to j
    // infinietely small...
    // didnt reflect several edges between nodes
    // When having negative weights, we need to be careful of using INF as 'no path' because AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]) suddenly gets lower then INF
    int n, m ,q; 
    bool first = true;
    while(cin >> n >> m >> q){
        if(n == 0 && m == 0 && q == 0) break;
        if(!first) cout << endl;
        first = false;
        vector<vector<ll>> AM(n, vector<ll>(n, INF));
        FOR(i, n){
            AM[i][i] = 0;
        }
        FOR(j, m){
            int a, b;
            ll c; 
            cin >> a >> b >> c; // a and b maybe equal?
            AM[a][b] = min(AM[a][b], c);
        }
        

        FOR(k, n) FOR(i, n) FOR(j, n){
            AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
        }
        FOR(i, n) FOR(j, n) FOR(k, n){
            if(AM[k][k] < 0 && AM[i][k] < INF && AM[k][j] < INF) AM[i][j] = -INF;
        }

        FOR(qq, q){
            int a, b; cin >> a >> b;
            if(AM[a][b] == -INF){
                cout << "-Infinity" << endl;
            }else if(AM[a][b] == INF){
                cout << "Impossible" << endl;
            }else{
                cout << AM[a][b] << endl;
            }
        }
    }


}

