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
const ll INF = 1<<30;

struct Node{
    ll weightedSum;
    ll sum;
    bool invalid = false;
    Node(){
    }
    Node(ll val, ll startIdx, ll len){
        ll endIdx = startIdx + len - 1;
        ll fac1 = (endIdx+1)*(endIdx+2)>>1;
        ll fac2 = (startIdx)*(startIdx+1)>>1;
        weightedSum = val * fac1 - val*fac2;
        sum = len*val;
    }
    Node operator+(const Node &right) const{
        if(invalid) return right;
        if(right.invalid) return *this;
        Node x;
        x.weightedSum = weightedSum + right.weightedSum;
        x.sum = sum + right.sum;
        return x;
    }
    void add(ll inc, ll startIdx, ll len){
        ll endIdx = startIdx + len - 1;
        ll fac1 = (endIdx+1)*(endIdx+2)>>1;
        ll fac2 = (startIdx)*(startIdx+1)>>1;
        weightedSum += inc * fac1 - inc*fac2;
        sum += len*inc;
    }
};
class ST{
private:
    Node NO_VALUE;
    ll UPDATE_NEUTRAL = 0;
    ll n;
    vector<Node> st;
    vi A, lazy;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    // O(n) as O(1+2+4+..+ 2**logn) = O(2n). Note the advantage of build is that each segment is computed only once, if we apply n times update we also need to update the inner nodes each time, leading to O(n log n)
    void build(ll p, ll L, ll R){
        if (L == R){
            st[p] = Node(A[L], L, 1); 
        } else{
            ll m = (L+R)/2;
            build(l(p), L, m);
            build(r(p), m+1, R);
            st[p] = st[l(p)] + st[r(p)];
        }
    }

    // Only needed for range-updates
    void propagate(ll p, ll L, ll R){ // propagate the lazy flag one level further down
        st[p].add(lazy[p], L, R-L+1);
        if(L!=R){
            lazy[l(p)] += lazy[p]; 
            lazy[r(p)] += lazy[p]; // NOTE: When at kids there is already a flag, sometimes we need to merge them
        }
        lazy[p] = UPDATE_NEUTRAL;
    }

    void update(ll p, ll L, ll R, ll i, ll j, ll val){ // O(logn)
        propagate(p, L, R); // if you update a node further done, you can't have a invalid lazy flag here
        if(L > j || R < i) return;
        if(L>=i && R<=j){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            st[p].add(val, L, R-L+1);
            if(R != L){
                lazy[l(p)] += val;
                lazy[r(p)] += val;
            }
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
    ST(ll size) : n(size) {
        NO_VALUE.invalid = true; // TODO;
        st.resize(4*size, NO_VALUE); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
        lazy.assign(4*n, UPDATE_NEUTRAL);
    }
    ST(const vector<ll> &initA): ST(initA.size()) {
        A = initA;
        build(1, 0, n-1);
    } 
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    void update(ll i, ll j, ll val) {
        // updates [i,..j]
        update(1, 0, n-1, i, j, val);
    }
    Node query(ll i, ll j){
        // queries [i,..j]
        return query(1, 0, n-1, i, j);
    }
};

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
    // problem: https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/D
    // about: Range Adding and querying of a weighted sum: 1*a[l] + 2*a[l+1] + ... + (r-l+1)*a[r] for given l and r. The major problem will be to use lazy propagation and therefore saving the right states. In each node we save the weightedSum of it meaning from l to r we save ((l+1)a[l] + (l+2)a[l+1]+...+ (r+1)a[r]). When adding numbers, can easily use small gausian to calculate the add on. For queries, however, we will have to much, and have to offset it by (l*[sum of the values inside the segment]).
    ll n, q; scanf("%lld %lld", &n, &q);
    vi init(n, 0);
    FOR(i, n){
        scanf(" %lld", &init[i]);
    }
    ST st(init);
    FOR(i, q){
        ll type; scanf("%lld", &type);
        if(type == 1){
            ll l, r, d;
            scanf(" %lld %lld %lld", &l, &r, &d);
            l--; r--;
            st.update(l, r, d);

        }else{
            ll l, r;
            scanf(" %lld %lld", &l, &r);
            l--; r--;
            Node seg = st.query(l, r);
            ll ans = seg.weightedSum;
            ans -= l*seg.sum;
            printf("%lld\n", ans);

        }
    }


}

