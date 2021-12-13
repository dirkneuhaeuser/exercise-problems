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

vector<bool> seen; // seen only saves the already seen pass-trough stations (degree == 2)
pii dfs(int start, int prev, vector<vector<pii>> &AL, vi &inD){
    seen[start] = true;
    pii ret = {start, 0};
    for(auto [next, w]: AL[start]){
        if(next == prev) continue;
        if(inD[next] == 2 && !seen[next]){
            pii add = dfs(next, start, AL, inD);
            ret.second+=add.second;
            ret.second+=w;
            ret.first = add.first;
        }else{
            ret.first = next;
            ret.second = w;
        }
    }
    return ret;
}


void solve() 
{
    // problem: https://open.kattis.com/problems/railroad
    // about: Baisc dfs problem: When ever you have a starting point (one station not passing through, but next is a passing through station), apply a dfs to get the end station and weight. For any other edge, just add it once to the result. The order of the edges does not matter, neighter the which endpoint will be stated first.
    int n, m; cin >> n >> m;
    vi inD(n, 0);
    vector<vector<pii>> AL(n);
    FOR(j, m){
        int a, b, c; cin >> a >> b >> c;
        a--;b--;
        inD[b]++;
        inD[a]++;
        AL[a].push_back({b, c});
        AL[b].push_back({a, c});
    }
    vector<tiii> newEdges;
    seen.assign(n, false);
    FOR(i, n){
        FOR(j, AL[i].size()){
            auto [next, w] = AL[i][j];
            if(inD[next] ==2 &&inD[i] !=2 && !seen[next]){ // start from any non passing station (i), where the next is a passing through station
                auto [end, cost] = dfs(next, i, AL, inD); // then go this clear defined path till the end, and return the end and its cumulated weight
                cost+=w;
                newEdges.push_back({i, end, cost});
            }
            if((inD[i] != 2 && inD[next] != 2 && i >= next)){ // for any other edge, only include it once
                newEdges.push_back({i, next, w});
            }
        }
    }
    cout << newEdges.size() << endl;
    FOR(i, newEdges.size()){
        auto [a, b, c] = newEdges[i];
        cout << a+1 << " " << b+1 << " " << c << endl;
    }


}

