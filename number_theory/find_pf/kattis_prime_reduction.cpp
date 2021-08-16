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

const int s  = 1<<15;
bitset<s> p;
vector<int>primes;
void sieve(){
    p[0]=0;
    p[1]=0;
    p.set();
    for(ll i = 2; i<s; ++i){
        if(p[i]){
            primes.push_back(i);
            for(ll j = i*i; j<s; j+=i){
                p[j]=0;
            }
        }
        
    }
}

bool isPrime(int x){
    if(x<s)return p[x];
    for(int i =0; i<primes.size() && (primes[i]*primes[i]<=x); ++i){
        if(x%primes[i]==0)return false;
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
    int n;
    while(cin >> n){
        if(n==4)return;
        int cnt = 1;
        int c = 10;
        while(!isPrime(n)){
            cnt++;
            int newN = 0;
            for(int i=0;i<primes.size() && primes[i]*primes[i]<=n; ++i){
                while(n%primes[i] == 0){
                    n/=primes[i];
                    newN += primes[i];
                }
            }
            if(n>1){
                newN += n;
            }
            n = newN;
        }

        cout << n << " " << cnt <<endl;
    }

}

