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


const int s = (1 << 15);
vector<int>primes;
bitset<s>p;
void sieve(){
    p.set();
    for(ll i=2; i<s; ++i){
        if(p[i]){
            primes.push_back(i);
            for(ll j = i*i; j<s; j+=i){
                p[j]=0;
            }
        }
    }
}

bool isPrime(int x){
    //dbg(primes);
    //dbg(p);
    if(x<s) return p[x];
    for(int i = 0; i<primes.size() && primes[i]*primes[i] <= x; ++i){
        if(x%primes[i]==0) return false;
    }
    return true;
}


//ll save_mod(ll a,ll m){
//    return ((a%m)+m)%m;
//}

ll mod_pow(ll a, ll p, ll m){
    if(p == 0) return 1;
    ll ans = mod_pow(a, p>>1, m);
    ans = (ans*ans) % m;
    if(p&1) ans*=a;
    return (ans % m);
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
    int p, a;
    while(cin >> p >> a){
        if(a==0 && p ==0)break;
        //cout << p << " " << isPrime(p) << endl;
        if(isPrime(p)){
            cout << "no" << endl;
            continue;
        }
        a = a%p;
        ll ret = mod_pow(a,p, p);
        //cout << a << " "<< p << " " << ret<<endl;
        if(a == ret){
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

    }
}

