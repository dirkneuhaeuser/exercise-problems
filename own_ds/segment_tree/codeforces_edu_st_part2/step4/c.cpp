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


struct Node{
    ll segs, len;
    bool isLeft, isRight;
    bool invalid = false;
    Node(){}
    Node(bool black, ll length){
        if(black){
            segs = 1;
            len = length;
            isRight = isLeft = true;
        }else{
            len = segs = 0;
            isRight = isLeft = false;
        }
    }
    Node operator+(const Node &right) const{
        if(invalid) return right;
        if(right.invalid) return *this;
        Node x;
        x.segs = segs+right.segs;
        if(isRight && right.isLeft){
            --x.segs;
        }
        x.invalid = false;
        x.len = len+right.len;
        x.isRight = right.isRight;
        x.isLeft = isLeft;
        return x;
    }
};
class ST{
private:
    ll UPDATE_NO_VALUE = -1;
    Node QUERY_NO_VALUE;
    ll n;
    vector<bool> A;
    vi lazy; // -1 nothing, 0 white, 1 black;
    vector<Node> st;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    void build(ll p, ll L, ll R){
        if (L == R){
            st[p] = Node(A[L], 1);
        } else{
            ll m = (L+R)/2;
            build(l(p), L, m);
            build(r(p), m+1, R);
            st[p] = st[l(p)] + st[r(p)];
        }
    }

    void propagate(ll p, ll L, ll R){ // propagate the lazy flag one level further down
        if(lazy[p] != UPDATE_NO_VALUE){
            st[p] = Node(lazy[p]==1, R-L+1);
            if(L!=R){
                lazy[l(p)] = lazy[r(p)] = lazy[p]; // override children
            }
            lazy[p] = UPDATE_NO_VALUE;
        }
    }

    void update(ll p, ll L, ll R, ll i, ll j, bool val){ // O(logn)
        propagate(p, L, R); 
        if(L > j || R < i) return;
        if(L>=i && R<=j){
            st[p] = Node(val, R-L+1); 
            if(L != R){
                if(val == true){
                    lazy[l(p)] = 1; // when flags are intercontected: better to set kids lazy flag here
                    lazy[r(p)] = 1; // when flags are intercontected: better to set kids lazy flag here
                }else{
                    lazy[l(p)] = 0; // when flags are intercontected: better to set kids lazy flag here
                    lazy[r(p)] = 0; // when flags are intercontected: better to set kids lazy flag here
                }
            }
        } else{
            ll m = (L+R)/2;
            update(l(p), L, m, i, j, val);
            update(r(p), m+1, R, i, j, val);
            st[p] = st[l(p)] + st[r(p)];
        }
    }
public:
    ST(ll size) : n(size) {
        QUERY_NO_VALUE=Node();
        QUERY_NO_VALUE.invalid=true;
        Node init(false, 1);
        st.resize(4*size, init); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
        lazy.assign(4*n, UPDATE_NO_VALUE);
    }
    ST(const vector<bool> &initA): ST(initA.size()) {
        A = initA;
        build(1, 0, n-1);
    } 
    void update(ll i, ll j, bool val) {
        update(1, 0, n-1, i, j, val);
    }
    Node get(){
        return st[1];
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
    int n; scanf("%d", &n);
    vector<bool>init(1'000'001, false);
    ST st(init);
    FOR(i, n){
        char op;
        ll l, len;
        scanf(" %c %lld %lld", &op, &l, &len);
        len--;
        if(op == 'W'){
            st.update(l, l+len, false);
        }else{
            st.update(l, l+len, true);
        }
        Node ans = st.get();
        printf("%lld %lld\n", ans.segs, ans.len);
    }


}

