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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

void solve() 
{
    // Basic infinite Knapsack with reconstruciton of the solution (here I use a parent vector) + Offset of the negative values. 
    // Note That only the range [-t, 2*t] is needed here, as for any other, you could go back towards the center with another number(you have to do so anyway) first
    // and then keep on advacing
    int n, t; cin >> n >> t;
    vector<pll> cheers;
    FOR(i,n){
        ll a, b; cin >> a>> b;
        cheers.push_back({a, b});
    }
    int maxN = 3*t+1;
    vector<int> par(3*t+1);
    for(int i=0; i<par.size(); ++i){
        par[i] = -1;
    }
    vector<int> dist(maxN, INF);
    for(int i=t; i<maxN; ++i)dist[i] = i-t;
    FOR(i, n){
        auto [cheer, cost] = cheers[i];
        if(cheer > 0){
            for(int j = cheer; j<maxN; ++j){ // unlimited coin-change/knapsack
                if(dist[j-cheer] != INF && dist[j-cheer] + cost < dist[j]){
                    dist[j] = dist[j-cheer] + cost;
                    par[j] = i;
                }
            }
        }else{
            for(int j = maxN-1+cheer; j>=0; --j){
                if(dist[j-cheer] != INF && dist[j-cheer] + cost < dist[j]){
                    dist[j] = dist[j-cheer] + cost;
                    par[j] = i;
                }
            }

        }
    }
    int cur = 2*t;
    vector<int> sol;
    while(true){
        int cheer = par[cur];
        if(cheer == -1){
            int dif = cur - t;
            FOR(i, dif) sol.push_back(1);
            break;
        }else{
            sol.push_back(cheer+2);
            cur-=cheers[cheer].first;
        }
    }
    sort(sol.begin(), sol.end());
    cout << sol.size() << endl;
    FOR(i, sol.size()){
        cout << sol[i] << " ";
    }

}

