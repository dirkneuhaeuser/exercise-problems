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
const ll INF = 9223372036854775807ll;


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


class SegmentTree{
private:
    ll notValid = INF;
    ll n;
    vector<ll> A, st, lazy;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    // the conq method decides the problem which is being solved: here min
    ll conq(ll a, ll b){
        if (a==notValid) return b; // edge case (happens in invalid subtree in query)
        if (b==notValid) return a;
        return a+b;
    }

    // O(n) as O(1+2+4+..+ 2**logn) = O(2n)
    void build(ll p, ll L, ll R){
        if (L == R){
            st[p] = A[L];
        } else{
            ll m = (L+R)/2;
            build(l(p), L, m);
            build(r(p), m+1, R);
            st[p] = conq(st[l(p)], st[r(p)]);
        }
    }

    void propagate(ll p, ll L, ll R){ // propagate the lazy flag one level further down
        if(lazy[p] != notValid){
                st[p] = lazy[p];
            if(L==R){
                A[L] = lazy[p]; // the initial update also will be updated
            }else{
                lazy[l(p)] = lazy[r(p)] = lazy[p];
            }
            lazy[p] = notValid;
        }
    }

    void update(ll p, ll L, ll R, ll i, ll j, ll val){ // O(logn)
        if(i>j)return; // will capture the case if you only look in the left subtree, but right gets also called
        if(L > j || R < i) return ;
        if(L>=i && R<=j){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            lazy[p] = val;
        } else{
            ll m = (L+R)/2;
            update(l(p), L, m, i, j, val);
            update(r(p), m+1, R, i, j, val);
            ll lsubtree = (lazy[l(p)]!=notValid)?lazy[l(p)]:st[l(p)];
            ll rsubtree = (lazy[r(p)]!=notValid)?lazy[r(p)]:st[r(p)];
            st[p] = conq(lsubtree, rsubtree);

        }
    }

    void point_update(ll p, ll L, ll R, ll idxToUpdate,  ll val){ // O(logn)
        //propagate(p, L, R); // if you update a node further done, you can't have a invalid lazy flag here
        if(L== idxToUpdate && idxToUpdate == R){
            st[p] += val;
            return;
        }
        ll m = (L+R)/2;
        if(idxToUpdate<=m){
            point_update(l(p), L, m, idxToUpdate, val);
        }else{
            point_update(r(p), m+1, R, idxToUpdate, val);
        }
        st[p] = conq(st[l(p)], st[r(p)]);

    }


    ll query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        //propagate(p, L, R);
        if(i>j)return notValid; // invalid subtree(with no coverage)
        if(L > j || R < i) return 0;
        if(i<=L && j>=R){ // with == would be sufficent
            return st[p];
        }
        ll m = (L+R)/2;
        return conq(query(l(p), L, m, i, j), query(r(p), m+1, R, i, j));
    }
public:
    SegmentTree(ll size) : n(size), st(4*size), lazy(4*n, notValid) {}
    SegmentTree(const vector<ll> &initA): SegmentTree(initA.size()) {
        A = initA;
        build(1, 0, n-1);
    }
    // range update, for point update set i == j
    void update(ll i, ll j, ll val) {
        // updates [i,..j]
        update(1, 0, n-1, i, j, val);
    }
    void point_update(ll idx, ll val) {
        // updates [i,..j]
        point_update(1, 0, n-1, idx, val);
    }
    ll query(ll i, ll j){
        // queries [i,..j]
        return query(1, 0, n-1, i, j);
    }
};



void solve() 
{
    // problem: https://open.kattis.com/problems/fenwick
    // about: Cumulate dynammica data, thus take basic fenwick or segment-tree. Note that you will get TLE if not using fast io. Here we are using ST.

    int n, q;
    scanf("%d %d", &n, &q);
    SegmentTree st(n);
    FOR(i, q){
        char a;
        scanf(" %c", &a);
        int idx;
        scanf(" %d", &idx);
        if(a == '+'){
            ll inc;
            scanf(" %lld", &inc);
            st.point_update(idx, inc);
        }else{
            if(idx == 0){
                printf("%d\n",0);
                continue;
            }
            ll ans = st.query(0, idx-1);
            if(ans == INF){
                printf("%d\n",0);
            }else{
                printf("%lld\n",ans);
            }
        }

    }

}

