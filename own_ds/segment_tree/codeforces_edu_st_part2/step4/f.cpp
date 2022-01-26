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
int n;

struct Node{
    ll sum, prefix;
    int lazy, start, end, mid;
    bool has_lazy_flag;
    vector<Node> sons;
    Node(int _start=0, int _end=n-1, ll _sum=0, ll _prefix=0, bool _has_lazy_flag=false){
        sum = _sum;
        prefix = _prefix;
        start = _start;
        end = _end;
        mid = (start + end)/2;
        has_lazy_flag=_has_lazy_flag;
    }
    void propagate(){
        if(sons.size() == 0 && start < end){
            sons.push_back(Node(start, mid));
            sons.push_back(Node(mid+1, end));
        }
        if(has_lazy_flag){
            if(lazy > 0){
                prefix = sum = (end - start + 1) * lazy;
            }else{
                prefix = 0;
                sum = (end - start + 1) * lazy;
            }
            if(start < end){
                sons[0].has_lazy_flag = sons[1].has_lazy_flag = true;
                sons[0].lazy = sons[1].lazy = lazy;
            }
        }
        has_lazy_flag = false;
        lazy = 0;
    }
    int query(ll h){
        propagate();
        if(start == end){
            if(prefix <= h){
                return start;
            }
            return start - 1;
        }
        sons[0].propagate();
        if(sons[0].prefix > h) return sons[0].query(h);
        return sons[1].query(h-sons[0].sum);
    }
    void update(int l, int r, ll val){
        propagate();
        if(start > r || end < l)return;
        if(start >= l && end <= r){
            // covered
            if(val > 0){
                prefix = sum = (end - start + 1) * val;
            }else{
                prefix = 0;
                sum = (end - start + 1) * val;
            }
            lazy=val;
            has_lazy_flag=true;
            return;
        }
        int m = (start + end)/2;
        sons[0].update(l, r, val);
        sons[1].update(l, r, val);
        prefix = max(sons[0].prefix, sons[0].sum + sons[1].prefix);
        sum = sons[0].sum + sons[1].sum;
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
    // problem: https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/F
    // about: Sparse-Segmenttree problem. At each node we need the sum, and the maxPrefixSum in order to answer the queries. Both are long long. Now we have 10^9 rails, leading to approx 4*10^9 Nodes with -> MLE. But as we only have 100.000 queries and or updates, we can go for a sparse segment-tree. Meaning instead of initialising right away our tree in array form, we just have a node and when needed we add two children to it, which each cover the half of the current segment.
    scanf("%d", &n);
    Node st; 
    while(true){
        char type;
        scanf(" %c", &type);
        if(type == 'Q'){
            ll h;
            scanf(" %lld", &h);
            ll ans = st.query(h);
            printf("%lld\n", ans+1);

        }else if(type == 'I'){
            int l, r;
            ll val; // 1-idx-based
            scanf(" %d %d %lld", &l, &r, &val);
            r--; l--;
            st.update(l, r, val);
        }else{
            break;
        }
    }

}

