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

// Least secnificant bit
// As index i is responsible for [(i - LSOne(i)+1)..i]
// Update: update as well the next bigger number responsible for you (i' = i+LSOne(i))
// Query: get as well next smaller number, which is responsible for [..i-LSOne(i) + 1)
#define LSOne(S) ((S) & -(S))


// Point-Update Range-Query (Standard Fenwick)
// like Prefix sum, but dynamic
// queries and update in O(logn), build in O(n) or O(nlogn)
class PURQ {
private:
    vector<vector<ll>> ft;
public:
    PURQ(int n) { // without leading 0
        ft.assign(n+1,vector<ll>(n+1, 0)); // idx 0 is bound, no value asigned to it
    }
    ll range_query_from_left(int i,int j){ // interval [1,...,j]
        ll ret = 0;
        for(;i>0; i-=LSOne(i)){
            int j1 = j;
            for(;j1>0; j1-=LSOne(j1)){
                //cout << i << " " << j1 << endl;
                ret += ft[i][j1];
            }
        }
        return ret;
    }
    ll range_query(int li, int lj, int ri, int rj){ // interval [i,...,j]
        return range_query_from_left(ri, rj) + range_query_from_left(li-1, lj-1) - range_query_from_left(ri, lj-1) - range_query_from_left(li-1, rj) ;
    }
    void point_update(int i, int j, int val){
        int n = ft.size();
        for(;i<n; i+=LSOne(i)){
            int j1=j;
            for(;j1<n; j1+=LSOne(j1)){
                ft[i][j1] += val;
            }
        }
    }
};

void solve() 
{
    int n; cin >> n;
    vector<vi> grid(n+1, vi(n+1, 0));
    FOR(i, n){
        FOR(j, n){
            cin >> grid[i+1][j+1];
        }
    }
    PURQ fw(n+1);
    FOR(i, n){
        FOR(j, n){
            fw.point_update(i+1, j+1, grid[i+1][j+1]);
        }
    }
    int q; cin >> q;
    FOR(i, q){
        char type; cin >> type;
        if(type == 'q'){
            int li, lj, ri, rj; cin >> li >> lj >> ri >> rj;
            ll ans = fw.range_query(li, lj, ri, rj);
            cout << ans << endl;
        }else{
            int a, b, c; cin >> a >> b >> c;
        }


    }
    
}

