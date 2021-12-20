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
    vector<long long> ft;
public:
    PURQ(int n) { // without leading 0
        ft.assign(n+1, 0); // idx 0 is bound, no value asigned to it
    }
    // builds in O(n), as oposed to O(n*logn)
    void build(vector<long long> vals){ // vals idx are keys of Fenwick-tree -> first in vector needs to be 0:
        int n = vals.size();
        ft.assign(n, 0);
        for(int i=0;i<n; i++){
            ft[i] += vals[i];
            if(i+LSOne(i)<n){
                ft[i+LSOne(i)] += ft[i];
            }
        }
    }
    long long range_query_from_left(int j){ // interval [1,...,j]
        assert(j>=0 && j < ft.size());
        long long ret = 0;
        while(j!=0){
            ret += ft[j];
            j-=LSOne(j);
        }
        return ret;
    }
    long long range_query(int i, int j){ // interval [i,...,j]
        assert(j>=i && j < ft.size());
        assert(i>=0 && i < ft.size());
        return range_query_from_left(j) - range_query_from_left(i-1);
    }
    void point_update(int i, int val){
        assert(i>0 && i < ft.size());
        while(i < ft.size()){
            ft[i]+=val;
            i += LSOne(i);
        }
    }
};

//vector<long long> test{0,1,23,325,34,5};
//PURQ purq = PURQ(6);
//purq.build(test);

//RUPQ rupq = RUPQ(6);
//rupq.range_update(2, 3, 5);
//cout << rupq.point_query(4) << endl;

//RURQ rurq = RURQ(10);
//rurq.range_update(1, 6, 5); // remember from 1 to 6 means from 0 to 5 in your arr
//rurq.range_update(4, 8, 5);
//cout << rurq.range_query(7, 10) << endl;

vi ps;
void solve() 
{
    // problem: https://open.kattis.com/problems/justforsidekicks
    // about: dynamic prefix sums -> Fenwick-tree. If we would have only one type, than this is would be a standard fw problem. As we have 6 times, we can just use 6 different fw trees.
    int n, q; cin >> n >> q;
    vi vals(6);
    FOR(i, 6){
        cin >> vals[i];
    }
    FOR(i, n){
        char p; cin >> p;
        int num = p-'1';
        ps.push_back(num);
    }
    vector<PURQ> fws;
    FOR(i, 6){
        PURQ fw(n);
        fws.push_back(fw);
    }
    FOR(i, n){
        ll cur = ps[i];
        fws[cur].point_update(i+1, 1);
    }
    FOR(i, q){
        int type; cin >> type;
        ll a, b; cin >> a >> b;
        if(type == 1){
            // a [1..n]
            // b [1..6]
            // type change
            int curType = ps[a-1];
            fws[curType].point_update(a, -1);
            fws[b-1].point_update(a, 1);
            ps[a-1] = b-1;
        }else if(type == 2){
            // a [1..6]
            // b [1..10^9]
            // change value 
            vals[a-1]=b;
        }else{
            // a [1..n]
            // b [1..n]
            ll ans = 0;
            FOR(i, 6){
                ans += fws[i].range_query(a, b)*vals[i];
            }
            cout << ans << endl;
        }



    }



}

