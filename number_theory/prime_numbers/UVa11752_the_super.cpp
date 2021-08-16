#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first

// int up to 2*10^9 (2^31-1)
#define ll long long  // up to 9*10^18 (2^63 -1)
#define ull unsigned long long // up to 18*10^18 (2^64-1)
#define ld long double
#define FOR(i, n) for(int i=0; i<n; i++)
#define FORS(i, n) for(; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/templates/debug.h"
#endif

const int MOD = 1000000007;
using namespace std; 

const int s = 65;
bitset<s> p;
void sieve(){
    p.set();
    for(int i = 2; i< s; ++i){
        if(!p[i]) continue;
        for(int j = i*i; j< s; j+=i){
            p[j]=0;
        }
    }
}

ull mpow(ull a, ull p){
    // mpow instead of native pow, as it doesn't support ull
    if(p==0) return 1;
    ull ans = mpow(a, p>>1);
    ans = ans*ans;
    if(p&1) ans = ans*a;
    return ans;
}

void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 
    
    sieve();
    int t=1; 
    cin >> t;
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
    // print all numbers up to 2**64 - 1 which are power of two different numbers
    // main idea: a number A is a power two different numbers, if there is B and a not prime number C: B**C = A
    // As C is not prime you can write C in the form C = x*y -> (B**x)**y = A or (B**y)**x = A, so A is a power of two different numbers(B**x and B**y)
    // Note: it is sufficient to up to (2**64)**(1/4) = 2**16 = 65536, as for a number i, the smallest non-prime is 4 -> 65536**4 == 2**64 (too large) 
    set<ull> ret;
    for(int i = 1; i<65536; i++){
        for(int j = 2; j<65; ++j ){
            if(!p[j] && log2(i)*j <64){ // break down all to the power of 2 to check whether the result is smaller than 2**64
                ret.insert(mpow(i, j));
            }
        }
    }
    vector<ull> ans;
    copy(ret.begin(), ret.end(), back_inserter(ans)); // c++ 11 doesnt allow for vector(ret.begin(), ret.end()) to convert set to vector

    sort(ans.begin(), ans.end());
    for(int i=0;i<ans.size(); ++i){
        cout << ans[i] << endl;
    }


}

