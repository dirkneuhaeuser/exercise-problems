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

int max_n = 1000001;
bitset<1000001> p;
vector<int> primes;
vector<int> smallest(max_n, 1);
void sieve(){
    for(ll i=2;i<max_n;++i){
        if(smallest[i] != 1) continue;
        p[i] = 1;
        smallest[i] = 1;
        primes.push_back(i);
        for(ll j = i*i; j<max_n; j+=i){
            smallest[j]=i;
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
    sieve(); 
    int t=1; 
    //cin >> t;
    int count = 1;
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
    cin >> n;
    while(n != 0){
        int a=1;
        int b=1;
        for(int prime:primes){
            if(p[n-prime]){
                a = prime; b = n-prime;
                break;
            }
        }
        int maxE = max(a, b);
        int minE = min(a, b);
        cout << n << " = " << minE << " + " << maxE << endl; 
        cin >> n;
    }

}

