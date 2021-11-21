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
    int count = 1;
    while(t--) 
    { 
        cout<<"Case #" << count++ << ":" << endl;
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{

    // APSP Problem: Check if the distances between two nodes can be improved -> wrong messaurements,
    // else run another Floyd-Warshall and see if you can make a detour without increasing the distance. If so, delete this edge.
    int n; cin >> n;
    vector<vector<ll>> AM(n, vector<ll>(n, INF));
    FOR(i, n-1){
        FOR(j, i+1){
            int num; cin >> num;
            AM[i+1][j] = num;
            AM[j][i+1] = num;
        }
    }
    FOR(i, n){
        AM[i][i]=0;
    }
    vector<vector<bool>> preFilled(n, vector<bool>(n, false));
    FOR(i, n) FOR(j, n){
        if(AM[i][j] != INF) preFilled[i][j] = true;
    }

    // calculate the min distance between all missing pair + check if some distances are wrong
    bool poss = true;
    FOR(k, n) FOR(i, n) FOR(j, n){
        if(AM[i][j] > AM[i][k] + AM[k][j]){
            if(preFilled[i][j]){
                poss = false;
            }
            AM[i][j] = AM[i][k] + AM[k][j];
        }
    }

    if(!poss){
        cout << "Need better measurements." << endl;
        return;
    }
    // unset cables if you can find a detour
    FOR(k, n) FOR(i, n) FOR(j, n){
        if(i == j || i==k || j==k) continue;
        if(AM[i][j] == AM[i][k] + AM[k][j]){
            // detour possible, delete edge:
            AM[i][j] = INF;
            AM[j][i] = INF;
        }
    }
    vector<pii> cables;
    FOR(i, n){
        for(int j=i+1; j<n; ++j){
            if(AM[i][j] != INF){
                cables.push_back({i, j});
            }
        }
    }
    cout << cables.size() << endl;
    for(auto [a, b]: cables){
        cout << a+1 << " " << b+1 << " " << AM[a][b] << endl;
    }
}

