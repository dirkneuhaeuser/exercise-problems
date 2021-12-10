#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<ll> vi;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
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

vi taxesCumulated, towards, backwards, cntWays;
ll totalTaxes;
ll n;
vector<bool> visited;

ll cntDFS(ll cur, vector<vector<pll>> &AL){
    cntWays[cur] = 0;
    ll ret = 1;
    for(auto [next, w]: AL[cur]){
        if(cntWays[next] == -1){
            ret += cntDFS(next, AL);
        }
    }
    //ret = max(1, ret);
    cntWays[cur] = ret;
    return ret;
}

ll weightedWaysDFS(ll cur, vector<vector<pll>> &AL){
    // needed for towardsCalculation
    visited[cur] = true;
    ll ret = 0;
    for(auto [next, w]: AL[cur]){
        if(visited[next] == false){
            ret += w*cntWays[next] + weightedWaysDFS(next, AL);
        }
    }
    return ret;
}

void towardsCalculationDFS(ll cur, vector<vector<pll>> &AL, ll weightedSum, vi &taxes){
    ll n = AL.size();
    visited[cur] = true;
    towards[cur] = weightedSum * taxes[cur];
    for(auto [next, w]: AL[cur]){
        if(visited[next] == false){

            towardsCalculationDFS(next, AL, weightedSum - w*cntWays[next] + w*(n-cntWays[next]), taxes);
        }
    }

}

ll taxesSubtreeDFS(ll cur, vector<vector<pll>> &AL, vi &taxes){
    taxesCumulated[cur] = 0;
    ll ret = taxes[cur];
    for(auto [next, w]: AL[cur]){
        if(taxesCumulated[next] == -1){
            ret += taxesSubtreeDFS(next, AL, taxes);
        }
    }
    return taxesCumulated[cur]=ret;
}

ll getInitBackwardsCost(ll cur, vector<vector<pll>> &AL, ll wCumulated, vi &taxes){
    visited[cur] = true;
    ll ret = (taxes[cur])*wCumulated;
    for(auto [next, w]: AL[cur]){
        if(visited[next] == false){
            ret += getInitBackwardsCost(next, AL, wCumulated+w, taxes);
        }
    }
    return ret;
}

void backwardsCalculationDFS(ll cur, vector<vector<pll>> &AL, ll backwardsCost){
    visited[cur] = true;
    backwards[cur] = backwardsCost;
    for(auto [next, w]: AL[cur]){
        if(visited[next] == false){
            backwardsCalculationDFS(next, AL, backwardsCost+w*(totalTaxes-taxesCumulated[next]) - w*taxesCumulated[next]);
        }
    }
}

void solve() 
{
    // problem: https://open.kattis.com/problems/fulldepthmorningshow
    // about: Harder DFS problem. (ti + tj)dij can be splitted to ti*dji + tj*dij. If we look from the perspective of i, then, the former we call 'towards' and the latter 'backwards'. Both can be calcuated with DFS in O(n). The towards values are based on weightedWays (O(n)), and once we have that, we can traverse through the graph, adjust this weightedWays as we go and calcuated all towards-values on the fly O(n). Analogously, we need the backward-value for one value (O(n)) only (and the summed up taxes in a subtree O(n)) to calculate the backwards values for the remaining O(n).
    cin >> n;
    vector<vector<pll>> AL(n);
    vi taxes(n);
    totalTaxes = 0;
    FOR(i, n){
        cin >> taxes[i];
        totalTaxes += taxes[i];
    }
    FOR(i, n-1){
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        AL[a].push_back({b, c});
        AL[b].push_back({a, c});
    }

    cntWays.assign(n, -1);
    cntDFS(0, AL);

    visited.assign(n, false);
    ll weightedSum = weightedWaysDFS(0, AL);

    visited.assign(n, false);
    towards.assign(n, 0);
    towardsCalculationDFS(0, AL, weightedSum, taxes);

    visited.assign(n, false);
    ll backwardsCost = getInitBackwardsCost(0, AL, 0, taxes);

    taxesCumulated.assign(n, -1);
    taxesSubtreeDFS(0, AL, taxes);

    visited.assign(n, false);
    backwards.assign(n, 0);
    backwardsCalculationDFS(0, AL, backwardsCost);
    FOR(i, n){
        cout << towards[i] + backwards[i] << endl;
    }



}

