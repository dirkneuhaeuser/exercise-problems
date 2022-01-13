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

using namespace std;
using namespace __gnu_pbds;

// order statistic tree
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//To convert it into pairs use pair<int,int> instead of int and also make less_equal<pair<int,int>> 

template <typename T>
using ost = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// To use ordered use ordered_multiset<type>S something like this

//int x=1;
//ost<ll> s;
//s.insert(x);
//ll low=s.order_of_key(x); // this is not possible with normal multiset. There you must have use distance(s.begin(), iterator), which takes O(n);
//s.lower_bound(x)

ost<int>t;
int maxn = 2000000;
vector<bool> isLucky(2000001);
vector<int> luckys;

void getLuckys(ost<int> &t){
    luckys.clear();
    for(int elem: t){
        luckys.push_back(elem);
        isLucky[elem] = true;
    }
}

void printSolution(int num){
    if((num&1)==0){
        // speed-up: we can go from the n/2 down to the smallest, and break when we found an elemnt, as this will minimise (l2-l1)
        int idx = upper_bound(luckys.begin(), luckys.end(), num/2) - luckys.begin();
        idx--;
        while(idx>=0){
            if(isLucky[num-luckys[idx]]){
                printf("%d is the sum of %d and %d.\n", num, luckys[idx], num-luckys[idx]);
                return;
            }
            idx--;
        }
    }
    printf("%d is not the sum of two luckies!\n", num);
}

void solve() 
{
    // problem: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1850
    // about: The difficult part is to pre-process the lucky-numbers. One way of doing it, is with an order statistics tree, which allow for logarithmic order-queries. Nonethesless, here we neeed to speed up the calculation, by directly deleting each 3rd and 7th element. Alternatively, we can use a Fenwick-Tree or a segment-tree to save for each position it specific order(at each idx we add +1). With a binary search we can then, get in O(log n * log n) the position of an order (which later will be updated by -1; so dynnamic).
    ost<int> t;
    int idx3 = 0;
    int idx7 = 0;
    for(int i=1; i<=maxn; i+=2){
        // speed up (not including them right away)
        if(((idx3+1)%3) == 0){
            idx3++;
            continue;
        }
        if(((idx7+1)%7) == 0){
            idx7++;
            idx3++;
            continue;
        }
        idx3++;
        idx7++;
        t.insert(i);
    }
    int i = 3;
    int total = 0;
    while(i < t.size()){
        // for all the remaining elements, just simulate:
        int newOrder=*t.find_by_order(i); // get the number of the next element == or new order, for which we need to delete the elemnts
        int cur = t.size()/newOrder*newOrder;
        int cnt = 0;
        bool done = true;
        while(cur > 0){
            auto it = t.find_by_order(cur-1);
            done = false;
            cur-=newOrder;
            t.erase(it);
            cnt++;
        }
        if(done) break;
        total += cnt;
        i++;
    }
    getLuckys(t);
    int num;
    while(scanf("%d", &num) != EOF){
        printSolution(num);
    }
}

