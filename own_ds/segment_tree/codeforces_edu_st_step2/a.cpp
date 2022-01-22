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

struct Node{
    ll maxPrefix, maxSuffix, maxSegment, sumSegment;
    bool invalid;
    Node(){
        invalid = false;
        maxPrefix = 0;
        maxSuffix = 0;
        maxSegment = 0;
        sumSegment = 0;
    }
    Node operator+(const Node &o) const{
        if(invalid) return o;
        if(o.invalid) return *this;
        Node ret;
        ret.maxPrefix = max(maxPrefix, sumSegment + o.maxPrefix);
        ret.maxSuffix = max(o.maxSuffix, o.sumSegment + maxSuffix);
        ret.sumSegment = sumSegment + o.sumSegment;
        ret.maxSegment = max({maxSegment, o.maxSegment, maxSuffix + o.maxPrefix});
        return ret;
    }
};
class SegmentTree{
private:
    Node NO_VALUE;
    ll n;
    vector<Node> A, st;
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

    void update(ll p, ll L, ll R, ll idx, Node val){ // O(logn)
        if(L > idx || R < idx) return;
        if(L==idx && R==idx){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            st[p] = val; 
        } else{
            ll m = (L+R)/2;
            if(idx <= m){
                update(l(p), L, m, idx, val);
            }else{
                update(r(p), m+1, R, idx, val);
            }
            st[p] = st[l(p)] + st[r(p)];

        }
    }


    Node query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        if(L > j || R < i) return NO_VALUE;
        if(i<=L && j>=R){ // with == would be sufficent
            return st[p];
        }
        ll m = (L+R)/2;
        return query(l(p), L, m, i, j)+ query(r(p), m+1, R, i, j);
    }
public:
    SegmentTree(ll size) : n(size) {
        NO_VALUE.invalid=true; // TODO;
        st.resize(4*size); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
    }
    SegmentTree(const vector<Node> &initA): SegmentTree(initA.size()) {
        A = initA;
        build(1, 0, n-1);
    } 
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    void update(ll idx, Node val) {
        // updates [i,..j]
        update(1, 0, n-1, idx, val);
    }
    Node query(ll i, ll j){
        // queries [i,..j]
        return query(1, 0, n-1, i, j);
    }
};
// vector<ll> test{1, 2, 3, 4, 5, 6, 7, 8};
// SegmentTree st(test);
// st.update(2,2,77); // point-update A[5] = 77
// cout << st.query(0, 3) << endl;

// SegmentTree st2(10);
// st2.update(0, 9, 2); // set all to 2;


// in conq you can choose the way it works, for addion probably fenwich is faster/easier.
// for function like min/max st very good



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
    // problem: https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A
    // about: Find on a dynammic array the segment with max-sum:Segment-Tree with more advanced state (maxPrefix, maxSuffix, maxSegment, sum)
    // note: Using smart way of defining operator+, instead of conq function
    int n, q; cin >> n >> q;
    vector<Node> nums(n);
    FOR(i, n){
        int num; cin >> num;
        nums[i].maxPrefix = max(0, num);
        nums[i].maxSuffix = max(0, num);
        nums[i].maxSegment = max(0, num);
        nums[i].sumSegment = num;
    }
    SegmentTree st(nums);
    Node ans = st.query(0, n);
    cout << ans.maxSegment << endl;
    FOR(i, q){
        ll idx, num; cin >> idx >> num;
        Node newNode;
        newNode.maxPrefix = max(0ll, num);
        newNode.maxSuffix = max(0ll, num);
        newNode.maxSegment = max(0ll, num);
        newNode.sumSegment = num;
        st.update(idx, newNode);
        Node ans = st.query(0, n-1);
        cout << ans.maxSegment << endl;

    }

}

