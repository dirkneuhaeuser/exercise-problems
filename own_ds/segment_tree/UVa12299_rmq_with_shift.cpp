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
class SegmentTree{
private:
    ll NEUTRAL;
    ll n;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    // the conq method decides the problem which is being solved: here min
    ll conq(ll a, ll b){
        if (a==NEUTRAL) return b; // edge case (happens in invalid subtree in query)
        if (b==NEUTRAL) return a;
        return min(a, b); // TODO;
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

    void point_update(ll p, ll L, ll R, ll curIdx, ll val){ // O(logn)
        if(L > curIdx || R < curIdx) return;
        if(L==curIdx && R == curIdx){
            st[p] = val; 
        } else{
            ll m = (L+R)/2;
            if(curIdx <= m){
                point_update(l(p), L, m, curIdx, val);
            }else{
                point_update(r(p), m+1, R, curIdx, val);
            }
            //update(r(p), m+1, R, i, j, val);
            st[p] = conq(st[l(p)], st[r(p)]);
        }
    }


    ll query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        if(L > j || R < i) return NEUTRAL;
        if(i<=L && j>=R){ // with == would be sufficent
            return st[p];
        }
        ll m = (L+R)/2;
        return conq(query(l(p), L, m, i, j), query(r(p), m+1, R, i, j));
    }
public:
    vector<ll> A, st, lazy;
    SegmentTree(ll size) : n(size), st(4*size) {
        NEUTRAL = INF; // TODO;
        lazy.assign(4*n, NEUTRAL);
    }
    SegmentTree(const vector<ll> &initA): SegmentTree(initA.size()) {
        NEUTRAL = INF; // TODO
        A = initA;
        build(1, 0, n-1);
        //dbg(st);
    } 
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    void point_update(ll i, ll val) {
        // updates [i,..j]
        point_update(1, 0, n-1, i, val);
    }
    ll query(ll i, ll j){
        // queries [i,..j]
        return query(1, 0, n-1, i, j);
    }
};
// vector<ll> test{1, 2, 3, 4, 5, 6, 7, 8};
// SegmentTree st(test);
// st.update(2,2,77); // point-update A[5] = 77
// cout << st.query(0, 3) << endl;

// in conq you can choose the way it works, for addion probably fenwich is faster/easier.
// for function like min/max st very good


void solve() 
{
    // problem: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3720
    // about: Dynamica Range query with min operator -> Use Segment-tree. As we only have point-updates, don't use propagate
    // learnd: With BIT you have to always calculate with 1-based index. With ST normally too, but in our implementation of the update/query we just use 0-baed idx
    int n, q; scanf("%d %d", &n, &q);
    vector<ll> nums;
    FOR(i, n){
        ll num; scanf("%ld", &num);
        nums.push_back(num);
    }
    SegmentTree st(nums);
    char s[30];
    FOR(i, q){
        char s[110];
        scanf(" %s", s);
        int idx = 6;
        if(s[0] == 'q'){
            string a = "", b = "";
            while(s[idx] != ','){
                a+=s[idx];
                idx++;
            }
            idx++;
            while(s[idx] != ')'){
                b+=s[idx];
                idx++;
            }
            int ai = stoi(a)-1;
            int bi = stoi(b)-1;
            ll ans = st.query(ai, bi);
            cout << ans << endl;
        }else{
            vi params;
            while(s[idx] != ')'){
                string cur = "";
                while(s[idx] != ',' && s[idx] != ')'){
                    cur+=s[idx];
                    idx++;
                }
                int curInt = stoi(cur);
                params.push_back(curInt-1);
                if(s[idx] == ')')break;
                idx++;
            }
            int m = params.size();
            vi newValues;
            FOR(j, m){
                if(j < m-1){
                    newValues.push_back(nums[params[j+1]]);
                }else{
                    newValues.push_back(nums[params[0]]);
                }
            }
            FOR(j, m){
                st.point_update(params[j], newValues[j]);
                nums[params[j]] = newValues[j];
            }

        }
    }


}

