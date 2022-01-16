#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                          // ld up to  10*10^307
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif

const int MOD = 1000000007;
using namespace std; 


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <typename T>
using ost = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// To use ordered use ordered_multiset<type>S something like this

//int x=1;
//ost<ll> s;
//s.insert(x);
//ll low=s.order_of_key(x); // this is not possible with normal multiset. There you must have use distance(s.begin(), iterator), which takes O(n);
//s.lower_bound(x)
//ll secondSmallest = *s.find_by_order(1); 



int main() 
{
    ost<int> t;
    t.insert(1);
    t.insert(1);
    t.insert(1);
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    //cout << *t.find(3) << endl;
    cout << t.order_of_key(2) << endl;
    ////cout << *t.lower_bound(1) << endl;
    //t.erase(t.upper_bound(1));
    //cout << *t.find_by_order(2) << endl;
    return 0; 
} 


