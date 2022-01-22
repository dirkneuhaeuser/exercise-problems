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
    int closing, opening;
    Node(){
        closing = 0;
        opening = 0;
    }
};

class ST{
public:
    vector<Node> st;
    int n;
    Node NOT_VALID;
    Node conq(Node left, Node right){
        if(left.opening == -1) return right;
        if(right.opening == -1) return left;
        Node ret = Node();
        ret.closing = left.closing;
        ret.opening = right.opening;

        int cancel = min(left.opening, right.closing);
        ret.opening += left.opening - cancel;
        ret.closing += right.closing - cancel;
        return ret;
    }

    int l(int x){return 2*x;};
    int r(int x){return 2*x + 1;};

    void build(int p, int L, int R, vector<Node> &nodes){
        if(L == R){
            st[p] = nodes[L];
        }else{
            int m = (L+R)>>1;
            build(l(p), L, m, nodes);
            build(r(p), m+1, R, nodes);
            st[p] = conq(st[l(p)], st[r(p)]);
        }
    }

    void point_update(int p, int L, int R, int point, Node val){
        if(L == R){
            st[p] = val;
        }else{
            int m = (L+R)>>1;
            if(point <= m){
                point_update(l(p), L, m, point, val);
            }else{
                point_update(r(p), m+1, R, point, val);
            }
            st[p] = conq(st[l(p)], st[r(p)]);
        }
    }

    Node query(int p, int L, int R, int lx, int rx){
        if(L>rx || R < lx) return NOT_VALID;
        if(lx <= L && R<= rx)return st[p];
        int m = (L+R)>>1;
        return conq(query(l(p), L, m, lx, rx), query(r(p), m+1, R, lx, rx));
    }
    ST(vector<Node> init){
        NOT_VALID = Node();
        NOT_VALID.opening = -1;
        NOT_VALID.closing = -1;
        n = init.size();
        st.assign(4*n, NOT_VALID);
        build(1, 0, n-1, init);
    }
};

void solve() 
{
    // problem: https://atcoder.jp/contests/abc223/tasks/abc223_f
    // about: Segment-Tree task, dynammic matching of parenthesis. Here a node has two values, the number of opening and closing. When merging segments we can use that to try to match as mutch as possible. If a segment does not have opening == 0 && closing == 0 it is not valid
    // note: It is faster to not use pointers -> heap is slower than stack
    int n, q; cin >> n >> q;
    vector<Node> v;
    FOR(i, n){
        Node nn = Node();
        char cur; cin >> cur;
        if(cur == ')'){
            nn.closing++;
        }else{
            nn.opening++;
        }
        v.push_back(nn);
    }
    ST st(v);
    FOR(i, q){
        int type, l, r;
        cin >> type >> l >> r;
        l--; r--;
        if(type == 1){
            Node nl = v[l];
            Node nr = v[r];
            st.point_update(1, 0, n-1, r, nl);
            st.point_update(1, 0, n-1, l, nr);
            swap(v[l], v[r]);
        }else{
            Node ret = st.query(1, 0, n-1, l, r);
            if(ret.opening == 0 && ret.closing == 0){
                cout << "Yes" << endl;
            }else{
                cout << "No" << endl;
            }
        }
    }

}

