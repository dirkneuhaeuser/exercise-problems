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
const ll INF = 1ll<<50;


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
    vector<ll> A, st, lazy;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}

    // the conq method decides the problem which is being solved: here min
    ll conq(ll a, ll b){
        if (a==NEUTRAL) return b; // edge case (happens in invalid subtree in query)
        if (b==NEUTRAL) return a;
        return max(a,b); // TODO;
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
    ll query(ll p, ll L, ll R, ll i, ll j){ // O(logn)
        if(i>j)return NEUTRAL; // invalid subtree(with no coverage)
        if(L > j || R < i) return NEUTRAL;
        if(i<=L && j>=R){ // with == would be sufficent
            return st[p];
        }
        ll m = (L+R)/2;
        return conq(query(l(p), L, m, i, j), query(r(p), m+1, R, i, j));
    }
public:
    SegmentTree(ll size) : n(size), st(4*size) {
        NEUTRAL = -1; // TODO;
        lazy.assign(4*n, NEUTRAL);
    }
    SegmentTree(const vector<ll> &initA): SegmentTree(initA.size()) {
        NEUTRAL = -1; // TODO
        A = initA;
        build(1, 0, n-1);
        //dbg(st);
    } 
    // All idx's i,j from 0 to n-1
    // range update, for point update set i == j
    ll query(ll i, ll j){
        // queries [i,..j]
        return query(1, 0, n-1, i, j);
    }
};
vi rain, years;
unordered_map<ll, int> y2idx;
ll getRain(ll year){
    if(y2idx.count(year)){
        int yearIdx = y2idx[year];
        return rain[yearIdx];
    }
    return -1;

}

void solve() 
{
    // problem: https://open.kattis.com/problems/worstweather
    // about: Range Minimum Queries via Segment Tree. Transform the years to indices from 0 to n-1. These stand for the position of that year in the segmenttree. Now, for each query, one has to carefully transfer the given years also to indicies. As some years are missing, one hast to spend some attention to do thinks right here.
    int n;
    while(true){
        scanf("%d", &n);
        if(n == 0)break;
        rain.assign(n, 0);
        years.assign(n, 0);
        y2idx.clear();
        FOR(i, n){
            ll y, r;
            scanf("%lld%lld", &years[i], &rain[i]);
            y2idx[years[i]]=i;
        }
        SegmentTree st(rain);
        
        int m;
        scanf("%d", &m);
        ll a, b;
        FOR(i, m){
            scanf("%lld%lld", &a, &b);
            // first case: a + 1 == b -> nothing in between
            int result = 2; // 2 = true, 1 = maybe, 0 = false;
            ll aRain = getRain(a);
            ll bRain = getRain(b);
            if(aRain == -1 || bRain == -1){
                result = min(result, 1);
            }else if(aRain<= bRain){
                result = min(result, 0);
            }

            
            // case: a+1 < b -> there are years inbetween to check:
            if(a+1 != b){
                // first year bigger than a:
                auto ita = upper_bound(years.begin(), years.end(), a);
                if(ita == years.end()){
                    // there are no records -> maybe
                    result = min(result, 1);
                }else{
                    ll ya = *ita;
                    if(ya >= b){
                        // there are no records -> maybe
                        result = min(result, 1);
                    }else{
                        auto itb = lower_bound(years.begin(), years.end(), b);
                        itb--;
                        ll yb = *itb;
                        int idxa = y2idx[ya];
                        int idxb = y2idx[yb];
                        if(idxb-idxa != b-a-2){
                            result = min(result, 1);
                        }
                        ll rainBetween = st.query(idxa, idxb);
                        if(bRain != -1){
                            if(rainBetween >= bRain){
                                result = min(result, 0);
                            }
                        }
                        if(aRain != -1){
                            if(rainBetween >= aRain){
                                result = min(result, 0);
                            }
                        }
                    }
                }
            }
            if(result == 1){
                printf("maybe\n");
            }else if(result == 0){
                printf("false\n");
            }else{
                printf("true\n");
            }
        }
        printf("\n");

    }

}

