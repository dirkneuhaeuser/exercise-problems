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
    int maxFreq, freqLeft, numLeft, freqRight, numRight;
    Node(int _maxFreq, int _freqLeft, int _numLeft, int _freqRight, int _numRight):maxFreq(_maxFreq), freqLeft(_freqLeft), freqRight(_freqRight), numLeft(_numLeft), numRight(_numRight){}
    Node(){};
};

class SegmentTree{
private:
    ll n;
    Node NO_VALUE;// = Node(-1, -1, -1, -1, -1);
    vector<Node> A, st, lazy; // freq2Number
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    // the conq method decides the problem which is being solved: here min
    Node conq(const Node &a, const Node &b){
        if(a.maxFreq==-1) return b;
        if(b.maxFreq==-1) return a;
        if(a.numRight == b.numLeft){
            Node ret = a;
            ret.numRight = b.numRight;
            ret.freqRight = b.freqRight;
            if(a.numLeft == a.numRight){
                ret.freqLeft += b.freqLeft;
            }
            if(b.numLeft == b.numRight){
                ret.freqRight +=  a.freqRight;
            }
            int maxFreq = max(a.maxFreq, b.maxFreq);
            maxFreq = max(maxFreq, a.freqRight + b.freqLeft);
            ret.maxFreq = maxFreq;
            return ret;
        }else{
            Node ret = a;
            ret.numRight = b.numRight;
            ret.freqRight = b.freqRight;
            int maxFreq = max(a.maxFreq, b.maxFreq);
            ret.maxFreq = maxFreq;
            return ret;

        }
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

    Node query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        if(L > j || R < i) return NO_VALUE;
        if(i<=L && j>=R){ // with == would be sufficent
            return st[p];
        }
        ll m = (L+R)/2;
        return conq(query(l(p), L, m, i, j), query(r(p), m+1, R, i, j));
    }
public:
    SegmentTree(ll size) : n(size) {
        NO_VALUE = Node(-1, -1, -1, -1, -1);
        st = vector<Node> (4*size);
        lazy = vector<Node> (4*size);
        //st.assign(4*size);
        //lazy.assign(4*n);
    }
    SegmentTree(const vector<Node> &initA): SegmentTree(initA.size()) {
        A = initA;
        build(1, 0, n-1);
        //dbg(st);
    } 
    Node query(ll i, ll j){
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

void solve() 
{
    // problem: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2176
    // about: Interesting Segment-Tree variation. Asked ist for fast queries of the max frequency of a number within an idx-interval. First note, that there are no updates, so its static; nontheless a segment-tree might be a good idea to go for fast queries. As the array is montonic, we can be smart when calculating the maxFrequency of a segment. This is the max of the maxFrequencys of both children and also the frequency which we have when concatenating both ends (from left segment the most right number with its frequency, with the most left number and its frequencys of the right segment), if both matching ends have the same number.
    int n, q; 
    while(cin >> n >> q){
        vector<Node> arg;
        FOR(i, n){
            int num; cin >> num;
            Node cur = Node(1, 1, num, 1, num);
            arg.push_back(cur);
        }
        SegmentTree st(arg);
        FOR(i, q){
            int a, b; cin >> a >> b;
            a--; b--;
            Node ans = st.query(a, b);
            cout << ans.maxFreq << endl;
        }
        
    }

}

