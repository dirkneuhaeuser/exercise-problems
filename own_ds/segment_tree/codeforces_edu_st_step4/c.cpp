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
const ll NINF = 1ll<<62;
const ll INF = 1ll<<61;


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
    ll inv;
    vi nums, pfs;
    bool invalid;
    Node(){
        invalid = false;
        nums.assign(40,0);
        pfs.assign(41,0);
        inv = 0;
    }
    Node(int val){
        invalid = false;
        inv = 0;
        nums.assign(40,0);
        nums[val] = 1;
        pfs.assign(41,0);
        for(int i=val+1; i<=40; ++i){
            pfs[i] = pfs[i-1] + nums[i-1];
        }
    }
    Node operator+(const Node &o) const{
        // O(40)
        if(invalid) return o;
        if(o.invalid) return *this;
        Node x;
        x.inv = inv+o.inv;
        //dbg(o.pfs);
        for(int i=0; i<40;++i){
            x.inv += nums[i]*(o.pfs[i]);
            x.nums[i] = nums[i]+o.nums[i];
        }
        for(int i=1; i<=40; ++i){
            x.pfs[i] = x.pfs[i-1] + x.nums[i-1];
        }
        return x;
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
        // O(2n * 40)
        if (L == R){
            st[p] = A[L];
        } else{
            ll m = (L+R)/2;
            build(l(p), L, m);
            build(r(p), m+1, R);
            st[p] = st[l(p)] + st[r(p)];
        }
    }

    void update(ll p, ll L, ll R, ll i, ll j, Node val){ // O(logn)
        // O(log n * 40)
        if(L > j || R < i) return;
        if(L>=i && R<=j){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            st[p] = val; 
        } else{
            ll m = (L+R)/2;
            update(l(p), L, m, i, j, val);
            update(r(p), m+1, R, i, j, val);
            st[p] = st[l(p)] + st[r(p)];

        }
    }


    Node query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        // O(log n * 40)
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

void solve() 
{
    // problem: https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/C
    // about: Segment-tree with complex state. As numbers are small, we can save in each node, the frequency array and for each number from left, we add the numbers which are bigger in right (use pfs);
    int n, q;
    scanf("%d %d", &n, &q);
    vector<Node> init;
    FOR(i, n){
        int num;
        scanf(" %d", &num);
        num--;
        Node nn(num);
        init.push_back(nn);
    }
    SegmentTree st(init);
    FOR(i, q){
        int type; //cin>>type;
        scanf("%d", &type);
        if(type == 1){
            int l, r;
            scanf(" %d %d", &l, &r);
            l--; r--;
            ll ans = st.query(l, r).inv;
            printf("%lld\n",ans);
        }else{
            int idx, val;
            scanf(" %d %d", &idx, &val);
            idx--;
            val--;
            init[idx] = Node(val);
            st.update(idx, idx, init[idx]);
        }
    }


}

