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
    ll minE, maxE;
    bool invalid = false;
    Node(){}
    Node(ll val){
        minE = maxE = val;
    }
    Node operator+(const Node &right) const{
        if(invalid) return right;
        if(right.invalid) return *this;
        Node x;
        x.minE = min(minE, right.minE);
        x.maxE = max(maxE, right.maxE);
        return x;
    }
    void setUpper(ll val){
        maxE = min(maxE, val);
        minE = min(minE, val);
    }
    void setLower(ll val){
        maxE = max(maxE, val);
        minE = max(minE, val);
    }
};
class ST{
private:
    Node NO_VALUE;
    pll UPDATE_NO_VALUE;
    ll n;
    vector<Node> st;
    vector<ll> A;
    vector<pll> lazy; // {minH, maxH}
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    // O(n) as O(1+2+4+..+ 2**logn) = O(2n). Note the advantage of build is that each segment is computed only once, if we apply n times update we also need to update the inner nodes each time, leading to O(n log n)
    void build(ll p, ll L, ll R){
        if (L == R){
            st[p] = Node(A[L]);
            //cout << p << " " << L << " " << R<< " " << st[p].minE << " " << st[p].maxE << endl;
        } else{
            ll m = (L+R)/2;
            build(l(p), L, m);
            build(r(p), m+1, R);
            st[p] = st[l(p)] + st[r(p)];
            //cout << p << " " << L << " " << R<< " " << st[p].minE << " " << st[p].maxE << endl;
        }
    }

    void propagate(ll p, ll L, ll R){ // propagate the lazy flag one level further down
        if(lazy[p].first != -1){
            st[p].setLower(lazy[p].first);
            if(L!=R){
                lazy[l(p)].first=(lazy[l(p)].first==-1)?lazy[p].first:max(lazy[p].first, lazy[l(p)].first);
                if(lazy[l(p)].second != -1 && lazy[l(p)].second < lazy[p].first){
                    lazy[l(p)].second  = lazy[p].first;
                }
                lazy[r(p)].first=(lazy[r(p)].first==-1)?lazy[p].first:max(lazy[p].first, lazy[r(p)].first);
                if(lazy[r(p)].second != -1 && lazy[r(p)].second < lazy[p].first){
                    lazy[r(p)].second  = lazy[p].first;
                }
            }
        }
        if(lazy[p].second != -1){
            st[p].setUpper(lazy[p].second);
            if(L!=R){
                lazy[l(p)].second=(lazy[l(p)].second==-1)?lazy[p].second:min(lazy[p].second, lazy[l(p)].second);
                if(lazy[l(p)].first != -1 && lazy[l(p)].first > lazy[p].second){
                    lazy[l(p)].first  = lazy[p].second;
                }
                lazy[r(p)].second=(lazy[r(p)].second==-1)?lazy[p].second:min(lazy[p].second, lazy[r(p)].second);
                if(lazy[r(p)].first != -1 && lazy[r(p)].first > lazy[p].second){
                    lazy[r(p)].first  = lazy[p].second;
                }
            }
        }
        lazy[p] = UPDATE_NO_VALUE;
    }

    void update(ll p, ll L, ll R, ll i, ll j, ll val, bool isUpper){ // O(logn)
        propagate(p, L, R); // if you update a node further done, you can't have a invalid lazy flag here
        if(L > j || R < i) return;
        if(L>=i && R<=j){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            if(isUpper){
                st[p].setUpper(val);
            }else{
                st[p].setLower(val);
            }
            if(L != R){
                if(isUpper){
                    lazy[p] = {-1, val};
                }else{
                    lazy[p] = {val, -1};
                }
            }
        } else{
            ll m = (L+R)/2;
            update(l(p), L, m, i, j, val, isUpper);
            update(r(p), m+1, R, i, j, val, isUpper);
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
        UPDATE_NO_VALUE={-1, -1};
        st.resize(4*size, NO_VALUE); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
        lazy.assign(4*n, UPDATE_NO_VALUE);
    }
    ST(const vector<ll> &initA): ST(initA.size()) {
        A = initA;
        build(1, 0, n-1);
    } 
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    void update(ll i, ll j,ll val, bool isUpper) {
        // updates [i,..j]
        update(1, 0, n-1, i, j, val, isUpper);
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
    // problem: https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/E 
    // about: Segment tree with max and min states. Note that when updaing/merging the lazy flags, you also need to check whether the kid has an opposiste flag set and if its not compatible with the current update, alter it
    ll n, q;
    scanf("%lld %lld", &n, &q);
    vi cols(n, 0);
    ST st(cols);
    ll test = 0;
    FOR(i, q){
        ll t, l, r, val;
        scanf("%lld %lld %lld %lld", &t, &l, &r, &val);
        if(t == 1){
            // adding -> setLower
            if(l<=3 && r>=3){
                test = max(test, val);
            }
            st.update(l, r, val, false);
        }else{
            // subtr -> setUpper
            st.update(l, r, val, true);
            if(l<=3 && r>=3){
                test = min(test, val);
            }
        }
    }
    Node tt = st.query(3, 3);
    FOR(i, n){
        Node cur = st.query(i, i);
        printf("%lld\n", cur.minE);
    }

}

