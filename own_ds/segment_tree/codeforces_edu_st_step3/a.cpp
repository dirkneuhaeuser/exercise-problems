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
struct Node{
    ll val;
    bool invalid;
    Node(){
        invalid = false;
        val = 0;
    }
    Node operator+(const Node &o) const{
        Node x;
        x.val = val+o.val;
        return x;
    }
};
class SegmentTree{
private:
    Node NO_VALUE;
    ll n;
    vector<Node> A, st, lazy;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    // O(n) as O(1+2+4+..+ 2**logn) = O(2n). Note the advantage of build is that each segment is computed only once, if we apply n times update we also need to update the inner nodes each time, leading to O(n log n)
    void build(ll p, ll L, ll R){
        if (L == R){
            st[p] = A[L];
        } else{
            ll m = (L+R)/2;
            build(l(p), L, m);
            build(r(p), m+1, R);
            st[p] = st[l(p)] + st[r(p)];
        }
    }

    // Only needed for range-updates
    void propagate(ll p, ll L, ll R){ // propagate the lazy flag one level further down
        if(!lazy[p].invalid){
                st[p] = lazy[p]; // TODO: if range update is used, you might need to update this (only works for max, min);
                //st[p].val*=(R-L+1); // this is for sum
            if(L!=R){
                lazy[l(p)] = lazy[r(p)] = lazy[p]; // NOTE: When at kids there is already a flag, sometimes we need to merge them
            }
            lazy[p] = NO_VALUE;
        }
    }

    void update(ll p, ll L, ll R, ll i, ll j, Node val){ // O(logn)
        if(L > j || R < i) return;
        propagate(p, L, R); // if you update a node further done, you can't have a invalid lazy flag here
        if(L>=i && R<=j){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            st[p] = val; 
            lazy[p] = val; // when flags are intercontected: better to set kids lazy flag here
        } else{
            ll m = (L+R)/2;
            update(l(p), L, m, i, j, val);
            update(r(p), m+1, R, i, j, val);
            st[p] = st[l(p)] + st[r(p)];

        }
    }


    Node query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        propagate(p, L, R);
        if(L > j || R < i) return NO_VALUE;
        if(i<=L && j>=R){ // with == would be sufficent
            return st[p];
        }
        ll m = (L+R)/2;
        return query(l(p), L, m, i, j) + query(r(p), m+1, R, i, j);
    }
public:
    SegmentTree(ll size) : n(size) {
        NO_VALUE.invalid = true; // TODO;
        st.resize(4*size, NO_VALUE); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
        lazy.assign(4*n, NO_VALUE);
    }
    SegmentTree(const vector<Node> &initA): SegmentTree(initA.size()) {
        A = initA;
        build(1, 0, n-1);
    } 
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    void update(ll i, ll j, Node val) {
        // updates [i,..j]
        update(1, 0, n-1, i, j, val);
    }
    Node query(ll i, ll j){
        // queries [i,..j]
        return query(1, 0, n-1, i, j);
    }
};
// ST with Nodes
//vector<Node> arr;
//vi nums{1, 2, 3, 4, 5, 6, 7, 8};
//// 1. insert values as nodes, and redefine operator + in struct Node
//FOR(i, nums.size()){
//    Node x;
//    x.val = nums[i];
//    arr.push_back(x);
//}
//SegmentTree st(arr);
//// range-query as defined in node:
//cout << st.query(0,1).val << endl; // 3
//cout << st.query(1,2).val << endl; // 5
//cout << st.query(0,0).val << endl; // 1
//
//// point update of idx 0 to 10 (lazy flag won't be used here)
//Node upd;
//upd.val = 10;
//st.update(0,0,upd);
//
//cout << st.query(0,1).val << endl; // 12
//cout << st.query(1,2).val << endl; // 5
//cout << st.query(0,0).val << endl; // 10
//
//// for range updates with lazy flag you need to redefine the propagate methode:
//// range update of all idx to 100 (lazy flag won't be used here)
//upd.val = 100;
//st.update(0, 7,upd);
//
//cout << endl;
//cout << st.query(0,7).val << endl; // 1
//cout << st.query(0,1).val << endl; // 3
//cout << st.query(1,2).val << endl; // 5
//cout << st.query(0,0).val << endl; // 1


void solve() 
{
    // problem: https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/A
    // about: To find the number of inversions (number greater than the current but earlier in the order), we go from left to right, save current number (+1) in the ST and find the numbers already persisted in the ST greater than this current number
    int n; cin >> n;
    vector<Node> nums(n);
    SegmentTree st(nums);
    FOR(i, n){
        int num; cin >> num;
        num--;
        cout << st.query(num+1, n-1).val << " ";
        Node upd;
        upd.val = 1;
        st.update(num, num, upd);
    }
}

