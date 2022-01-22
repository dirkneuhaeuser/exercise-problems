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

// masks:
// no a,b,c = 0
// a = 1
// b = 2
// c = 4
// ab = 8
// bc = 16

vector<vector<int>> combinedMasks(32, vector<int>(32, -1));


int mergeMasks(int left, int right){
    // result contains abc:
    if((left&1) && (right&16)) return -1;
    if((left&8) && (right&4)) return -1;

    int ret = left|right;
    if((left&1) && (right&2)) ret = ret | 8;
    if((left&2) && (right&4)) ret = ret | 16;
    //cout << left << " " << right << " -> " << ret << endl;
    return ret;
}

struct Node{
    bool UNVALID;
    vector<int> dp;
    Node(){
        UNVALID = false;
        dp.assign(32, INF); // dp of masks which can contain all possible combinations
    }
};
class SegmentTree{
private:
    Node NO_VALUE;
    ll n;
    vector<Node> A, st, lazy;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}


    // the conq method decides the problem which is being solved: here min
    void conq(int p){
        int left = l(p);
        int right = r(p);

        if(st[left].UNVALID) {
            st[p] = st[right];
            return;
        }
        if(st[right].UNVALID){
            st[p] = st[left];
            return;
        }
        FOR(i, 32) st[p].dp[i] = INF;
        for(int maskLeft=0; maskLeft<32; ++maskLeft){
            if(st[left].dp[maskLeft] == INF) continue;
            for(int maskRight=0; maskRight<32; ++maskRight){
                if(st[right].dp[maskRight] == INF) continue;
                int maskTotal = combinedMasks[maskLeft][maskRight];
                if(maskTotal != -1){
                    st[p].dp[maskTotal] = min(st[p].dp[maskTotal], st[left].dp[maskLeft] + st[right].dp[maskRight]);
                }
            }
        }
    }

    // O(n) as O(1+2+4+..+ 2**logn) = O(2n). Note the advantage of build is that each segment is computed only once, if we apply n times update we also need to update the inner nodes each time, leading to O(n log n)
    void build(ll p, ll L, ll R){
        //dbg(L);
        //dbg(R);
        if (L == R){
            st[p] = A[L];
        } else{
            ll m = (L+R)/2;
            build(l(p), L, m);
            build(r(p), m+1, R);
            conq(p);
        }
    }


    void update(ll p, ll L, ll R, ll idx, Node val){ // O(logn)
        if(L==idx && R==idx){  // goal: narrow L and R down, s.t. the intervall of this node captured. == would be sufficient
            st[p] = val; 
        } else{
            ll m = (L+R)/2;
            if(idx<=m){
                update(l(p), L, m, idx, val);
            }else{
                update(r(p), m+1, R, idx, val);
            }
            conq(p);

        }
    }

public:
    SegmentTree(ll size) : n(size) {
        NO_VALUE = Node(); // TODO;
        NO_VALUE.UNVALID = -1;
        Node init = Node();
        st.assign(4*size, init); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
    }
    SegmentTree(const vector<Node> &initA): SegmentTree(initA.size()) {
        A = initA;
        build(1, 0, n-1);
    } 
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    void update(ll idx, Node val) {
        // updates [i,..j]
        update(1, 0, n-1, idx, val);
    }
    int query(){
        // queries [i,..j]
        int ret = INF;
        FOR(i, 32){
            ret = min(ret, st[1].dp[i]);
        }
        return ret;
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

void solve() 
{
    // problem: https://codeforces.com/contest/1609/problem/E
    // about: Advanced Segment-Tree + DP. A string of only 'a', 'b' and 'c' is not allowed to contain a subSEQUENCE of "abc". Also the string is dynammic and constantly changing via queries. After each query we are allowed to change as few as possible characters (also only to 'a', 'b' or 'c'). With a bitmask-approach we can set 0 for no digit (this is the trick, we dont change to 'a', 'b' or 'c', but pretend we delete it, as we will always chose the best char anyway), 1 for a is in the string, 2 for b, 4 for c, 8 for ab, ... Now when merging two nodes, we can go through all masks of left and all masks of right, their attached costs and create the new one. A bit more sophisicated is this solution: https://codeforces.com/contest/1609/submission/137243787 (no masks, but saving how many chars you have to delete, to not have 'a', or 'ab' ,...
    // note: The conq function can also just take p and operate directly on the array st;
    // note2: We can get rid of conq and add an `Node operator+(const node &o) const { .... ` to the struct
    // precalculate the combined Masks:
    for(int i=0;i<32; ++i){w
        for(int j=0; j<32; ++j){
            combinedMasks[i][j] = mergeMasks(i, j);
        }
    }
    int n, q; cin >> n >> q;
    vector<Node> v(n);
    FOR(i, n){
        char cur; cin >> cur;
        // mask = 0000;
        v[i].dp[0] = 1; // when changing the current character, it will cost 1 and we of course change it to something matching == deleting it.

        // not deleting, comes at a cost of 0 (keep it)
        if(cur == 'a'){
            // mask = 0001
            v[i].dp[1]=0;
        }else if(cur == 'b'){
            // mask = 0010;
            v[i].dp[2]=0;
        }else{
            // mask = 0100;
            v[i].dp[4]=0;
        }

    }
    SegmentTree st(v);
    FOR(i, q){
        int idx; cin >> idx; idx--;
        char cur; cin >> cur;
        Node nn = Node();
        nn.dp[0] = 1;
        // not deleting, comes at a cost of 0 (keep it)
        if(cur == 'a'){
            // mask = 0001
            nn.dp[1]=0;
        }else if(cur == 'b'){
            // mask = 0010;
            nn.dp[2]=0;
        }else{
            // mask = 0100;
            nn.dp[4]=0;
        }
        st.update(idx, nn);
        cout << st.query() << endl;
        
    }
}

