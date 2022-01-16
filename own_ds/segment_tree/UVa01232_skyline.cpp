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
    
    int t=1; 
    cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
class SegmentTree{
private:
    pll NO_VALUE;
    ll n;
    vector<pll> st, lazy; // {min, max}
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    // the conq method decides the problem which is being solved: here min
    pll conq(pll a, pll b){
        if (a==NO_VALUE) return b; // edge case (happens in invalid subtree in query)
        if (b==NO_VALUE) return a;
        pll ans = {min(a.first, b.first), max(a.second, b.second)};
        return ans; // TODO;
    }

    // TODO: Works only for max/min
    void propagate(ll p, ll L, ll R){ // propagate the lazy flag one level further down
        if(lazy[p] != NO_VALUE){
                st[p] = lazy[p];
            if(L!=R){
                lazy[l(p)] = lazy[r(p)] = lazy[p]; // NOTE: When at kids there is already a flag, sometimes we need to merge them
            }
            lazy[p] = NO_VALUE;
        }
    }

    void update(ll p, ll L, ll R, ll i, ll j, ll val){ // O(logn)
        if(L > j || R < i) return;
        propagate(p, L, R); // if you update a node further done, you can't have a invalid lazy flag here
        ll curMin = st[p].first;
        ll curMax = st[p].second;
        if(i == j && L>=i &&  R<=j){
            if(st[p].second < val){
                st[p].first = val;
                st[p].second = val;
            }
        } else if(L>=i && R<=j && !(val > curMin && val < curMax)){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            if(val <= curMin) return; // our value doesn't update anythin;
            if(val >= curMax){
                st[p] = {val, val};
                lazy[p] = {val, val};
            }
        } else{
            ll m = (L+R)/2;
            update(l(p), L, m, i, j, val);
            update(r(p), m+1, R, i, j, val);
            st[p] = conq(st[l(p)], st[r(p)]);

        }
    }

    ll query(ll p, ll L, ll R, ll i, ll j, ll val){ // O(logn)
        propagate(p, L, R);
        if(L > j || R < i) return 0;
        if(i<=L && j>=R){ // with == would be sufficent
            if(val >= st[p].second){
                return R - L + 1;
            }
            if(val < st[p].first){
                return 0;
            }
        }
        ll m = (L+R)/2;
        return query(l(p), L, m, i, j, val) + query(r(p), m+1, R, i, j, val);
    }
public:
    SegmentTree(ll size) : n(size) {
        NO_VALUE = {-1, -1}; // TODO;
        pll init = {0, 0}; // TODO;
        lazy.assign(4*n, NO_VALUE);
        st.assign(4*n, init);
    }
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    void update(ll i, ll j, ll val) {
        // updates [i,..j]
        update(1, 0, n-1, i, j, val);
    }
    ll query(ll i, ll j, ll val){
        // queries [i,..j]
        return query(1, 0, n-1, i, j, val);
    }
};
// vector<ll> test{1, 2, 3, 4, 5, 6, 7, 8};
// SegmentTree st(test);
// st.update(2,2,77); // point-update A[5] = 77
// cout << st.query(0, 3) << endl;
//
//
// SegmentTree st2(10);
// st2.update(0, 9, 2); // set all to 2;

// in conq you can choose the way it works, for addion probably fenwich is faster/easier.
// for function like min/max st very good

void solve() 
{
    // problem: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3673
    // about: Segment-tree variation. Instead of RMQ we change the ST, such that each inner node, which is responsible for a range, denotes the min and max height of current skyline in it. 
    int n; cin >> n;
    SegmentTree st(100001);
    ll ans = 0;
    FOR(i, n){
        int l, r, h; cin >> l >> r >> h;
        r--; // it goes until r but not r including
        ll q = st.query(l, r, h);
        ans += q;
        st.update(l, r, h);
    }
    cout << ans;

}

