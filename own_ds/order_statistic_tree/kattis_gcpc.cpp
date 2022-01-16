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



void solve() 
{
    // problem: https://open.kattis.com/problems/gcpc 
    // about: dynammic rank problem. Use a ost with pair<int, int>. Think about how to alter a pair, when a new event occures. Use less_equal, as we want to use it as multiset (it is important to us when there are many teams having the same score).
    int n, m;
    scanf("%d %d", &n, &m);
    vector<pii> teams(n, {0, 0});
    ost<pii> tree;
    FOR(i, m){
        int t, p;
        scanf("%d %d", &t, &p);
        t--;
        pii oldPair = teams[t];
        tree.erase(tree.upper_bound(oldPair));
        pii newPair = oldPair;
        newPair.second += p;
        newPair.first--;
        tree.insert(newPair);
        teams[t] = newPair;
        printf("%d\n", tree.order_of_key(teams[0])+1);
    }


}

