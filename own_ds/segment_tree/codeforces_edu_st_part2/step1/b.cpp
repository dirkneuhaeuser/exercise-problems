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

class SegmentTree{
private:
    ll NO_VALUE;
    ll n;
    vector<ll> A, st, lazy;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    //// the conq method decides the problem which is being solved: here min
    //ll conq(ll a, ll b){
    //    if (a==NO_VALUE) return b; // edge case (happens in invalid subtree in query); sometimes its enough to just use a neutral value for NO_VALUE, but it might not work with lazy-propagation
    //    if (b==NO_VALUE) return a;
    //    return a+b; // TODO;
    //}

    // O(n) as O(1+2+4+..+ 2**logn) = O(2n). Note the advantage of build is that each segment is computed only once, if we apply n times update we also need to update the inner nodes each time, leading to O(n log n)
    void build(ll p, ll L, ll R){
        if (L == R){
            st[p] = A[L];
        } else{
            ll m = (L+R)/2;
            build(l(p), L, m);
            build(r(p), m+1, R);
            //st[p] = conq(st[l(p)], st[r(p)]);
        }
    }

    // TODO: Works only for max/min
    void propagate(ll p, ll L, ll R){ // propagate the lazy flag one level further down
        if(lazy[p] != NO_VALUE){
            st[p] = max(st[p], lazy[p]);
            if(L!=R){
                lazy[l(p)] = max(lazy[l(p)], lazy[p]);
                lazy[r(p)] = max(lazy[r(p)], lazy[p]);
            }
            lazy[p] = NO_VALUE;
        }
    }

    void update(ll p, ll L, ll R, ll i, ll j, ll val){ // O(logn)
        if(L > j || R < i) return;
        propagate(p, L, R); // if you update a node further done, you can't have a invalid lazy flag here
        if(L>=i && R<=j){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            lazy[p] = val; // when flags are intercontected: better to set kids lazy flag here
        } else{
            ll m = (L+R)/2;
            update(l(p), L, m, i, j, val);
            update(r(p), m+1, R, i, j, val);
            //st[p] = conq(st[l(p)], st[r(p)]);

        }
    }


    ll query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        propagate(p, L, R);
        if(L > j || R < i) return NO_VALUE;
        if(i<=L && j>=R){ // with == would be sufficent
            return st[p];
        }
        ll m = (L+R)/2;
        if(i<=m){
            return query(l(p), L, m, i, j);
        }else{
            return query(r(p), m+1, R, i, j);
        }
    }
public:
    SegmentTree(ll size) : n(size) {
        NO_VALUE = -1; // TODO;
        ll INIT = 0; // TODO;
        st.assign(4*size, INIT); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
        lazy.assign(4*n, NO_VALUE);
    }
    SegmentTree(const vector<ll> &initA): SegmentTree(initA.size()) {
        A = initA;
        build(1, 0, n-1);
    } 
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    void update(ll i, ll j, ll val) {
        // updates [i,..j]
        update(1, 0, n-1, i, j, val);
    }
    ll query(ll i, ll j){
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
    // problem: https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/B
    // about: Apply a max functino to a segment and have a point query. Because of the point query, we don't need to worry about calculating intermediate results, but only on propagating the applied function when needed. Here we need to particularly take into consideration to MERGE the operation of the propagted mother with its childern.
    int n, q; //cin >> n >> q;
    scanf("%d %d", &n, &q);
    vi init(n, 0);
    SegmentTree st(init);
    FOR(i, q){
        int type;
        scanf("%d", &type);
        if(type == 1){
            ll l, r, v;
            scanf(" %lld %lld %lld", &l, &r, &v);
            r--;
            st.update(l, r, v);
        }else{
            ll idx;
            scanf("%lld", &idx);
            ll ans = st.query(idx, idx);
            printf("%lld\n", ans);
        }


    }


}


