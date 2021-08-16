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




const int s = (1<<15) + 1;
vector<int> primes;
bitset<s> p;
void sieve(){
    p.set();
    for(ll i = 2; i < s; ++i){
        if(!p[i]) continue;
        primes.push_back(i);
        for(ll j = i*i; j<s; j+=i){
            p[j] = 0;

        }
    }
}

bool isPrime(int a){
    if(a < s){return p[a];}
    for(int p:primes){
        if(a%p == 0) return false;
    }
    return true;
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
    // idea: as for number greate than 2**24 the sieve takes too long, we can do the sieve only up the half of 2**30, so 2**15, as all other numbers if not prime, will have a pf<=2**15
    int n;
    while(cin >> n){
        if(n == 0) break;
        int goal = (n << 1) + 1;
        while(!isPrime(goal)){
            goal++;
        }
        if(!isPrime(n)){
            cout << goal << " (" << n << " is not prime)"<< endl;
            continue;
        }
        cout << goal << endl;

    }
}

