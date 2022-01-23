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

class ST{
private:

    // TODO: you need to change these functions+neutrals
    ll NEUTRAL_QUERY = LLONG_MAX;
    ll NEUTRAL_UPDATE = 0;
    // Segment-tree consists of two operations, update and query:
    ll conqQuery(ll a, ll b){
        return a & b;
    }
    // If update function is not distributive, you might need to think a little
    ll conqUpdate(ll prev, ll op){
        return prev | op;
    }


    ll n;
    vector<ll> A, st, lazy;
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
            st[p] = conqQuery(st[l(p)], st[r(p)]);
        }
    }

    // might need some refactoring if conqUpdate is not distributive wrt conqQuery.
    void propagate(ll p, ll L, ll R){ // propagate the lazy flag one level further down
        st[p] = conqUpdate(st[p], lazy[p]);
        if(L!=R){
            lazy[l(p)] = conqUpdate(lazy[l(p)], lazy[p]);
            lazy[r(p)] = conqUpdate(lazy[r(p)], lazy[p]);
        }
        lazy[p] = NEUTRAL_UPDATE;
    }

    void update(ll p, ll L, ll R, ll i, ll j, ll val){ // O(logn)
        propagate(p, L, R); // if you update a node further done, you can't have a invalid lazy flag here
        if(L > j || R < i) return;
        if(L>=i && R<=j){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            st[p] = conqUpdate(st[p], val);
            if(L != R){
                lazy[l(p)] = conqUpdate(lazy[l(p)], val);
                lazy[r(p)] = conqUpdate(lazy[r(p)], val);
            }
        } else{
            ll m = (L+R)/2;
            update(l(p), L, m, i, j, val);
            update(r(p), m+1, R, i, j, val);
            st[p] = conqQuery(st[l(p)], st[r(p)]);

        }
    }


    ll query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        propagate(p, L, R);
        if(L > j || R < i) return NEUTRAL_QUERY;
        if(i<=L && j>=R){ // with == would be sufficent
            return st[p];
        }
        ll m = (L+R)/2;
        return conqQuery(query(l(p), L, m, i, j), query(r(p), m+1, R, i, j));
    }
public:
    ST(ll size) : n(size) {
        //NEUTRAL_UPDATE = 1;
        //NEUTRAL_QUERY = 0;
        st.assign(4*size, NEUTRAL_UPDATE); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
        lazy.assign(4*n, NEUTRAL_UPDATE);
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
    ll query(ll i, ll j){
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
    // problem: https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/C
    // about: Basic ST, OR is distributive wrt to AND -> normal lazy propagation
    int n, q;
    scanf("%d %d", &n, &q);
    vi init(n, 0);
    ST st(init);
    FOR(i, q){
        int type;
        scanf("%d", &type);
        if(type == 1){
            ll l, r, v;
            scanf(" %lld %lld %lld", &l, &r, &v);
            r--;
            st.update(l, r, v);
        }else{
            ll l, r;
            scanf("%lld %lld", &l, &r);
            r--;
            ll ans = st.query(l, r);
            printf("%lld\n", ans);
        }

    }

}

