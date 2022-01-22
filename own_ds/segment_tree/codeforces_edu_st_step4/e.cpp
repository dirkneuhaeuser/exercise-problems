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
    int minE;
    bool invalid;
    Node(){
        invalid = false;
    }
    Node(ll val){
        if(val == 0){
            invalid = true;
        }else{
            invalid = false;
            minE = val;
        }
    }
    Node operator+(const Node &right) const{
        if(invalid) return right;
        if(right.invalid) return *this;
        Node x;
        x.minE = min(minE, right.minE);
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
        if (L == R){
            st[p] = A[L];
        } else{
            ll m = (L+R)/2;
            build(l(p), L, m);
            build(r(p), m+1, R);
            st[p] = st[l(p)] + st[r(p)];
        }
    }

    // point update
    void update(ll p, ll L, ll R, ll i, ll j, Node val){ // O(logn)
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


    ll query(ll p, ll L, ll R, ll i, ll j, ll power){ // O(logn)
        if(L > j || R < i) return 0;
        if(st[p].minE > power) return 0;
        if(st[p].invalid) return 0;
        if(L==R){ // with == would be sufficent
            if(st[p].minE > power) return 0;
            st[p] = NO_VALUE;
            return 1;
        }
        ll m = (L+R)/2;
        ll ans1 = query(l(p), L, m, i, j, power);
        ll ans2 = query(r(p), m+1, R, i, j, power);
        st[p] = st[l(p)] + st[r(p)];
        return ans1+ans2;

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
        update(1, 0, n-1, i, j, val);
    }
    ll query(ll i, ll j, ll power){
        return query(1, 0, n-1, i, j, power);
    }
};

void solve() 
{
    // problem: https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/E
    // about: Normal min-Segment-tree. In one query it could happen that we go down to all leaves and destroy them O(nlogn), but then we will only build 1 building in every other query, so it won't come to often
    int n, q;
    scanf("%d %d", &n, &q);
    Node empty;
    empty.invalid = true;
    vector<Node> init(n, empty);
    SegmentTree st(init);
    FOR(i, q){
        int type;
        scanf("%d ", &type);
        if(type == 1){
            ll idx, h;
            scanf(" %lld %lld", &idx, &h);
            Node nn(h);
            st.update(idx, idx, nn);
        }else{
            ll l, r, power;
            scanf(" %lld %lld %lld", &l, &r, &power);
            ll ans = st.query(l, r-1, power);
            printf("%lld\n", ans);
        }
    }

}

