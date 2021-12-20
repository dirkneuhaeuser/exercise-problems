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
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//To convert it into pairs use pair<int,int> instead of int and also make less_equal<pair<int,int>> 

template <typename T>
using ordered_multiset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// To use ordered use ordered_multiset<type>S something like this

//int x=1;
//ordered_multiset<ll> s;
//s.insert(x);
//ll low=s.order_of_key(x); // this is not possible with normal multiset. There you must have use distance(s.begin(), iterator), which takes O(n);
//s.lower_bound(x)




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
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
struct cmp1 {
    bool operator() (const pair<int,int>& lhs, const pair<int,int>& rhs) const {
        return lhs.second < rhs.second;
    }
};
void solve() 
{
    // problem: https://open.kattis.com/problems/moviecollection
    // about: order statics tree problem
    int NINF = 1 << 31;
    int n, q; cin >> n >> q;
    set<pii, cmp1> idPos;
    ordered_multiset<pii> om;
    FOR(i, n){
        idPos.insert({i+1,i+1});
        om.insert({i+1,i+1});
    }
    auto t = idPos.begin();
    FOR(i, q){
        int r; cin >> r; 
        pii search = {NINF,r};
        auto it = idPos.lower_bound(search);
        pii real = *it;
        int ans =om.order_of_key(real);
        cout << ans << " ";

        om.erase(real);
        idPos.erase(real);
        real.first = -i;

        idPos.insert(real);
        om.insert(real);
    }

}

