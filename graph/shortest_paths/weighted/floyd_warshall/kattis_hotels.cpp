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
    while(t--) 
    { 
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
pair<int, int> interpolation(int lidx, int ridx, int lsteps, int rsteps){
    int idx = (rsteps - lsteps + ridx + lidx)/2;
    vector<int> pot{lidx, idx, idx+1, ridx};
    int maxDis = -1;
    int maxIdx = -1;
    for(int p: pot){
        if(p>= lidx && p<=ridx){
            int pMax = min(lsteps + (p-lidx), rsteps + (ridx - p));
            if(pMax > maxDis){
                maxDis = pMax;
                maxIdx = p;
            }
        }
    }
    return {maxDis, maxIdx};
}

void solve() 
{
    // Complicated APSP Problem. Here the ASAP are between elevators. Therefore we get all possible reachable levels together with the specific elevaor reaching this level. 
    //
    // Instead going over all possible pairs of reachable levels, we can make use of the transitive nature of Floyed-Warshall:
    // Sorting the reachable `levels` vector and going over within a linear scan to check if for two adj entries, the elevators connection within the AM can be improved (TRANSITIVE NATURE)
    // This however, is just the initial distance. We now need to run Floyed-Warshall on this to get the APSP.
    //
    // No we have all reachable levles (by elevators) and their respective cost. Now, for each gap in between two levels, we need to interpolate and get that value where we have to run the furthest. For this, we truely only need to set two equations equal. One is X + cost(a) - levela, the other is -X + cost(b) + levelb
    //
    // Learned: In floyed-warshall the inital AM do not need all start-values as long these can be build by the principe of transitivity.
    int n, elevators; cin >> n >> elevators;
    vector<pii> levels{{0, 0}};
    vector<vector<int>> elevator_levels(elevators);
    FOR(j, elevators){
        int r, mod; cin >> r >> mod;
        while(r < n){
            elevator_levels[j].push_back(r);
            levels.push_back({r, j+1});
            r += mod;
        }
    }
    // Init AM
    vector<vector<ll>> AM(elevators+1, vector<ll>(elevators+1, INF)); // the 0th is the EG
    sort(levels.begin(), levels.end());
    int prevElevatorLevel = -1;
    int prevElevator = -1;
    for(int i=0; i<levels.size(); ++i){
        auto [curLevel, curElevator]  = levels[i];
        if(prevElevator != -1){
            AM[curElevator][prevElevator]  = AM[prevElevator][curElevator] = min(AM[prevElevator][curElevator], (ll)abs(curLevel - prevElevatorLevel));
        }
        prevElevator = curElevator;
        prevElevatorLevel = curLevel;

    }
    // Floyed-Warshall ASAP
    FOR(k, elevators+1){
        FOR(i, elevators+1){
            for(int j = i+1; j<elevators+1; ++j){
                AM[j][i] = AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
            }
        }
    }
    int prevLevel = 0;
    int prevLevelCost = 0;
    levels.push_back({n-1, INF});
    int retIdx = -1;
    int retCost = -1;
    for(int i=1; i<levels.size(); ++i){
        auto [l, el] = levels[i];
        int cost;
        if(i != levels.size()-1){
            cost = AM[0][el];
        }else{
            cost = INF;
        }
        // interpolate all adj. levels reachable by elevaors
        auto [maxDis, maxIdx] = interpolation(prevLevel, l, prevLevelCost, cost);
        if(maxDis > retCost || (maxDis == retCost && maxIdx < retIdx)){
            retCost = maxDis;
            retIdx = maxIdx;
        }
        prevLevel = l;
        prevLevelCost = cost;
    }
    cout << retCost << " " << retIdx;

}

