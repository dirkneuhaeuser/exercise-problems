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

template <typename T>
using ost = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// To use ordered use ordered_multiset<type>S something like this

//int x=1;
//ost<ll> s;
//s.insert(x);
//ll low=s.order_of_key(x); // this is not possible with normal multiset. There you must have use distance(s.begin(), iterator), which takes O(n);
//s.lower_bound(x)

int getOrder(ost<string> &oms, string &a, string &b){
    auto bIt = oms.lower_bound(b);
    if(bIt != oms.begin()){
        bIt--;
        string inBound = *bIt;
        //dbg(inBound);
        auto aIt = oms.lower_bound(a);
        if(aIt == oms.begin()){
            return oms.order_of_key(inBound)+1;
        }else{
            aIt--;
            string aString = *aIt;
            //dbg(aString);
            int sub = oms.order_of_key(aString)+1;
            return max(0,(int)oms.order_of_key(inBound)+1 - sub);
        }
    }
    return 0;

}

char nameC[30]; 

void solve() 
{
    // problem: https://open.kattis.com/problems/babynames
    // about: We need to know the orders of names and thus we should use an Order Statistic Tree (OST) for that. Here we use two OST, one for the males and one for the femalse. Also, note that here, a Fenwick tree for the order is not feasable, as the OST allows for any type while a Fenwick Tree is rather for small indexes. Also, this problem can only be handled by fast i/o.
    int type;
    ost<string> female, male;
    while(true){
        scanf("%d", &type);
        if(type == 0) break;
        if(type == 1){
            int gender;
            scanf("%s %d", nameC, &gender);
            string name(nameC);
            if(gender == 1){
                male.insert(name);
            }else{
                female.insert(name);
            }
        }
        if(type == 2){
            scanf(" %s", nameC);
            string name(nameC);
            male.erase(name);
            female.erase(name);
        }
        if(type == 3){
            int gender;
            scanf("%s", nameC);
            string a(nameC);
            scanf(" %s %d", nameC, &gender);
            string b(nameC);
            if(gender == 0){
                //both genders
                int ans1 = getOrder(male, a, b);
                int ans2 = getOrder(female, a, b);
                printf("%d\n", ans1+ans2);

            }else if(gender == 1){
                // male
                int ans = getOrder(male, a, b);
                printf("%d\n", ans);
            }else{
                // female
                int ans = getOrder(female, a, b);
                printf("%d\n", ans);
            }
        }

    }

}

