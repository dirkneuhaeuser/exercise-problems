#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 

// 2**6 =  64                           // 4!  = 24                          
// 2**8 =  256                          // 5!  = 120                       
// 2**10 = 1,024                        // 6!  = 720
// 2**15 = 32,768                       // 7!  = 5,040
// 2**20 = 1,048,576                    // 8!  = 40,320
// 2**25 = 33,554,432                   // 9!  = 362,880
// 2**30 = 1,073,741,824                // 10! = 3,628,800
// 2**32 = 4,294,967,296                // 12! = 479,001,600
                                        // 14! = 87,178,291,200
 // int up to  2*10^9 (2^31-1)          // 16! = 20,922,789,888,000
 // ll up to   9*10^18 (2^63 -1)        // 18! = 6,402,373,705,728,000
 // ull up to 18*10^18 (2^64-1)/        // 20! = 2,432,902,008,176,640,000

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


const ull MOD = 100'000'000'000ull;
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
        //cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    ull n; //<=10 KK
    cin >> n;
    ull fac = 1;
    ull factor = 1;
    ull fives = 0;
    while(factor<=n){
        ull f = factor;
        while(f%5==0){
            fives++;
            f/=5;
        }
        factor++;
    }
    //cout << fives;
    factor = n;
    while(factor >= 1){
        ull k = factor;
        while(k%5==0){
            k/=5;
        }
        while(fives && k%2==0){
            fives--;
            k/=2;
        }

        fac *= k;
        factor--;
        fac%=1000 ;
        //cout << fac <<endl;
    }
    
    ull ret =  fac%1000;
    if(n<7){
        cout << ret;
        return;
    }

    string ans = to_string(ret);
    int paddingZeros =  3 - ans.size() ;
    cout << string(paddingZeros, '0') + ans;


}

