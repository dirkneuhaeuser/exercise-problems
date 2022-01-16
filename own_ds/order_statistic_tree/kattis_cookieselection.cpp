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
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <typename T>
using ost = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// To use ordered use ordered_multiset<type>S something like this

//int x=1;
//ost<ll> tree;
//tree.insert(x);
//ll low=tree.order_of_key(x); // this is not possible with normal multiset. There you must have use distance(s.begin(), iterator), which takes O(n);
//tree.lower_bound(x)
//ll secondSmallest = *tree.find_by_order(1); 



char sC[9];

void solve() 
{
    // problem: https://open.kattis.com/problems/cookieselection
    // about: To deal with dynammic median queries we have several option. The least code would be to use an order statistic tree (ost), like we have used. As they also allow for efficient (log n) order queries we can easily solve the task. Note that this is a multiset implementation, we need to use less_equal as comperator. Another way ist to use a fenwick-tree, but here the indixies would probably be to large. Alternatively, one could also apply two priority_queues, the left fo the median is a max-heap, the right of the median is a min heap. No we could always put the new element to to either of the pq (depending on both heads) and if they are unbalanced, we pop from one and push it to the other pq.

    ost<int> tree;
    while(scanf(" %s", sC) != EOF){
        string s(sC);
        if(s == "#"){
            int n = tree.size();
            int medianOrder = n/2;
            auto it = tree.find_by_order(medianOrder);
            printf("%d\n", *it);
            tree.erase(it);
        }else{
            int d = stoi(s);
            tree.insert(d);
        }
    }

}

