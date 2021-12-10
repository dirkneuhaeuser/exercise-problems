#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first

//#include <boost/functional/hash.hpp>
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


//1. Bin-Coefficients with MOD
// out of main:
long long C(long long n, long long k, long long m, long long fact[]){
    // binomial coeffiecents with modulo m
    // n! / ((n-k)! k!) 
    // to use the modular arithmetic, we need to finde the inverse of (n-k)! and k! 
    // factorials need to be precalculated and taken modulo
    if(n < k) return 0;
    return (((fact[n] * invEea(fact[k], m)) % m) * invEea(fact[n-k], m)) % m;
}
// in main:
long long fact[100001];
// precalcualte factorials
fact[0]=1;
for(int i=1; i<100001;++i){
    fact[i] = (fact[i-1]*i)%MOD;
}
// 100000 C 5000:
long long ret = C(100000, 50000, MOD, fact);  // (100000 choose 50000)%1000000007 = 149033233



//2. Bin-Coefficients without MOD -> pascals Forumla for n<66
vector<vector<ll>>bincoefs(66, vector<ll>(66, 1));
for(int n = 1; n<66; ++n){
    for(int m = 1; m< n; ++m){
        bincoefs[n][m] = bincoefs[n-1][m] + bincoefs[n-1][m-1];
    }
}

int main() 
{
    unordered_map<pair<string, string>, int, boost::hash<pair<string, string>>> m;
    return 0; 
} 


