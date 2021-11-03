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
    
    int t=1; 
    cin >> t;
    while(t--) 
    { 
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{

    // Unweigted SSSDSP: 2D level bfs. Here the paths of the ants needs to be modelled into a graph (assume a 201x201 grid as there max 100 directions and reconstruct AL)
    int n; cin >> n;
    int s = 201*201;

    // reconstruct the AL:
    vector<set<int>> AL(s, set<int>());
    int prevI = 100, prevJ = 100;
    int curI = 100, curJ = 100;
    FOR(i, n){
        char c; cin >>c;
        if(c == 'S') curI++;
        if(c == 'N') curI--;
        if(c == 'E') curJ++;
        if(c == 'W') curJ--;
        int prev = prevI * 201 + prevJ;
        int cur = curI * 201 + curJ;
        AL[prev].insert(cur);
        AL[cur].insert(prev);
        prevI = curI;
        prevJ = curJ;
    }
    int start = 100*201 + 100;
    int end = curI*201 + curJ;
    vector<int> q{start};
    vector<bool> seen(s, false);
    seen[start] = true;
    int steps = 0;
    while(q.size()){
        vector<int> nq;
        for(int cur: q){
            if(cur == end){
                cout << steps;
                return;
            }
            for(int next: AL[cur]){
                if(seen[next]) continue;
                nq.push_back(next);
                seen[next] = true;

            }
        }
        q = nq;
        steps++;
    }
}

