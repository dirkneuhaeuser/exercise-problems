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
    PURQ(vi &vals){
        build(vals);
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
    int select(ll k){
        int lp=1, hp=ft.size()-1;
        while(lp < hp){
            int mid = (lp+hp) /2;
            if(range_query_from_left(mid) < k){
                lp = mid+1;
            }else{
                hp = mid;
            }
        }
        return lp;
    }
};

//vector<long long> test{0,1,23,325,34,5};
//PURQ purq = PURQ(test); 


void solve() 
{
    // problem: https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B
    // about: Find the kth order, here we use a fenwick tree. Limitation of small array is met
    int n, m; cin >> n >> m;
    vi nums(n+1, 0);
    FOR(i, n){
        int num;
        cin >> num;
        nums[i+1] = num;
    }
    PURQ fw(nums);
    FOR(i, m){
        int a, b; cin >> a >> b;
        if(a == 1){
            nums[b+1]^=1;
            if(nums[b+1] == 1){
                fw.point_update(b+1, 1);
            }else{
                fw.point_update(b+1, -1);
            }
        }else{
            cout << fw.select(b+1)-1  << endl;
        }
    }
}

