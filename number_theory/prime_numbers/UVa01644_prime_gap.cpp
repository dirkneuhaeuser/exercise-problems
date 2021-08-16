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

const int s = 1299709 + 1;
bitset<s>p;
vector<int> primes;
void sieve(){
    p.set();
    for(ll i = 2; i< s; ++i){
        if(!p[i])continue;
        primes.push_back(i);
        for(ll j = i*i; j<s; j+= i){
            p[j] = 0;
        }
    }
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
    
    int t=1; 
    //cin >> t;
    //int count = 1;
    sieve();
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
    int n;
    while(cin>>n){
        if(n== 0) break;
        auto it = lower_bound(primes.begin(), primes.end(), n);
        int bigger = it-primes.begin();
        if (primes[bigger] == n){
            cout << 0 << endl;
        }else{
            cout << primes[bigger] - primes[bigger- 1] << endl;

        }
    }
}

