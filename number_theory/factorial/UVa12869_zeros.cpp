#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 

// 2**6 =  64
// 2**8 =  256
// 2**10 = 1,024
// 2**15 = 32,768
// 2**20 = 1,048,576
// 2**25 = 33,554,432
// 2**30 = 1,073,741,824
// 2**32 = 4,294,967,296

// 5!  = 120
// 10! = 3,628,800
// 12! = 479,001,600
// 14! = 87,178,291,200
// 16! = 20,922,789,888,000
// 18! = 6,402,373,705,728,000
// 20! = 2,432,902,008,176,640,000

// int up to  2*10^9 (2^31-1)
// ll up to   9*10^18 (2^63 -1)
// ull up to 18*10^18 (2^64-1)/

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;

#define FOR(i, n) for(int i=0; i<n; i++)
#define FORS(i, n) for(; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/templates/debug.h"
#endif

const int MOD = 1000000007;



void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 
    
    int t=1; 
    //cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    //idea: to create a 0 you need a multiple of 5 and 2
    ull l, u;
    while(cin >> l >> u){
        if(l == 0 && u ==0){
            return;
        }
        // note: normally you would also check if 5**2, 5**3,... are supported by u or l, because that would give you another 5. However here don't need this, as we are only interested
        // in different values: 24! has 4 trailing zeros, while 25! has 6 trailing zeros. So we dont need to calculuate it for powers of five as they don't lead to more different values
        // (only more zeros)
        ull retUpper = u/5ull;
        ull retLower = l/5ull;
        cout << retUpper - retLower + 1 << endl;
    }

}

