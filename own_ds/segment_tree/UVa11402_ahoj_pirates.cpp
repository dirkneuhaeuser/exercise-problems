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
#define lft at<<1
#define ryt at<<1|1
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
    int count = 1;
    while(t--) 
    { 
        cout<<"Case " << count++ << ":" << endl;
        solve(); 
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
enum{NTH=-1, FLIP=0, SET=1, UNSET=2};
class SegmentTree{
private:
    ll INVALID;
    ll n;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    // the conq method decides the problem which is being solved: here min
    ll conq(ll a, ll b){
        if (a==INVALID) return b; // edge case (happens in invalid subtree in query)
        if (b==INVALID) return a;
        return a+b; // TODO;
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

    int doFlip(int flag) {
        if( flag == SET ) return UNSET ;
        if( flag == UNSET ) return SET ;
        if( flag == FLIP ) return NTH ;
        return FLIP ;
    }

    void propagate(int p , int L , int R){
        // if there is a lazy flag at the children as well, then merge both flags, but be smart about it (flipping causes a flip there as well);
        if( lazy[p] == NTH ) return ;
        if( lazy[p] == SET ) {
            st[p] = R - L + 1 ;
        }
        else if( lazy[p] == UNSET ) {
            st[p] = 0;
        }
        else if( lazy[p] == FLIP ) {
            st[p] = ( R - L + 1 ) - st[p];
        }
        if( L != R ) {
            if( lazy[p] == SET || lazy[p] == UNSET ) {
                lazy[l(p)] = lazy[r(p)] = lazy[p];
            } else {
                lazy[l(p)] = doFlip( lazy[l(p)] );
                lazy[r(p)] = doFlip( lazy[r(p)] );
            }
        }
        lazy[p] = NTH;
    }


    void update(ll p, ll L, ll R, ll i, ll j, ll op){ // O(logn)
        propagate(p, L, R);
        if( L > j || i > R ) return ;
        if(L>=i && R<=j){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
           if(op == SET) {
               st[p]=R-L+1;
               lazy[l(p)] = lazy[r(p)] = SET;
           }
           if(op == UNSET){
               st[p]=0;
               lazy[l(p)] = lazy[r(p)] = UNSET;
           }
           if(op == FLIP){
               st[p] = R-L+1 - st[p];
               lazy[l(p)] = doFlip(lazy[l(p)]);
               lazy[r(p)] = doFlip(lazy[r(p)]);
           }
        } else{
            ll m = (L+R)/2;
            update(l(p),L,m,i,j, op);
            update(r(p),m+1,R,i,j, op);
            st[p] = st[l(p)] + st[r(p)];
            st[p] = conq(st[l(p)], st[r(p)]);

        }
    }


    ll query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        propagate(p, L, R);
        if(R < i || L > j) return 0;
        if(i<=L && j>=R){ // with == would be sufficent
            return st[p];
        }
        ll m = (L+R)/2;
        return conq(query(l(p), L, m, i, j), query(r(p), m+1, R, i, j));
    }
public:
    vector<ll> A, st;
    vector<int> lazy; // first op (0 == inv, 1 == set, 2 == unset); second value
    SegmentTree(ll size) : n(size), st(4*size) {
        INVALID = -1; // TODO;
        lazy.assign(4*n, NTH);
    }
    SegmentTree(const vector<ll> &initA): SegmentTree(initA.size()) {
        INVALID = -1; // TODO;
        A = initA;
        lazy.assign(4*n, NTH);
        build(1, 0, n-1);
    } 
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    void update(ll i, ll j, ll type) {
        // updates [i,..j]
        update(1, 0, n-1, i, j, type);
    }
    ll query(ll i, ll j){
        return query(1, 0, n-1, i, j);
    }
};
// vector<int> test{18, 17, 13, 19, 15, 11, 20, 99};
// SegmentTree st(test);
// st.update(5,5,77); // point-update A[5] = 77
// cout << st.query(1, 3) << endl;

// in conq you can choose the way it works, for addion probably fenwich is faster/easier.
// for function like min/max st very good

void solve() 
{
    // problem: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2397 
    // about: Segment-tree variaton. Here the intersting part is that we have 3 flags (set, unset and inverse). 
    // learnt1: When we are propagating flags down, we might need to merge to flags. For example the left children alredy have a set flag, while our current node has a flip flag.
    // Now when propagating the flip flag, we merge both flags to one (flip + set = unset)
    // learnt2: Good practice, when reachign a node, s.t. that we can abort, as we are lazy, we set the current st value nontheless and only for the children we set the lazy flag (remember learnt1);
    string init;
    int m; cin >> m;
    FOR(j, m){
        int times; cin >> times;
        string cur; cin >> cur;
        FOR(i, times){
            init += cur;
        }
    }
    int n = init.size();
    vector<ll> cur(n, 0);
    FOR(i, n){
        if(init[i] == '1'){
            cur[i]=1;
        }
    }
    SegmentTree st(cur);
    int q; cin >> q;
    int cnt = 1;
    FOR(i, q){
        char a; cin >> a;
        int b, c; cin >> b >> c;
        int op = -1;
        if(a == 'F'){
            op = 1;
        }else if( a == 'E'){
            op = 2;
        }else if(a == 'I'){
            op = 0;
        }else{
            ll ans = st.query(b, c);
            cout << "Q" << cnt++ <<": ";
            cout << ans << endl;
            continue;
        }

        st.update(b, c, op);

    }


}

