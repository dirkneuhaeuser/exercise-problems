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

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//To convert it into pairs use pair<int,int> instead of int and also make less_equal<pair<int,int>> 

template <typename T>
using ost = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    // problem: https://open.kattis.com/problems/turbo
    // about: Order Statistics Tree (OST) Problem. As we need to know the left and as well the right rank of a key before deleting it, we can use two OST. One to save the negative and one to save the postive values. Then, when calling `order_of_key`, the negative will give you the rank from right, and the positive the rank from left. However, one could also just use the size of the tree, to calculate the right rank
    int n; cin >> n;
    vi positions(n);
    ost<ll> pos;

    FOR(i, n){
        pos.insert(i);
        int num; cin >> num; num--;
        positions[num]=i;
    }


    int lp = 0, rp = n-1;
    for(int i=1; i<=n; ++i){
        int ans, position;
        if(i&1){
            position = positions[lp++];
            ans = pos.order_of_key(position);
            cout << ans << endl;
        }else{
            position = positions[rp--];
            ans = pos.order_of_key(position);
            cout << pos.size() - 1 - ans << endl;
        }
        pos.erase(position);
    }

}

