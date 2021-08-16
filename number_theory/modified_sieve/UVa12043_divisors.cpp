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
const int s = 100001;
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

ll numDiv(int x){
    ll ret = 1;
    for(int i=0; i<primes.size() && primes[i]*primes[i]<=x; ++i){
        ll factor = 1;
        while(x%primes[i]==0){
            factor++;
            x/=primes[i];
        }
        ret*=factor;
    }
    if(x>1) ret*=2;
    return ret;
}

ll sumDiv(int x){
    ll ret = 1;
    for(int i=0; i<primes.size() && primes[i]*primes[i]<=x; ++i){
        ll factor = 1, mult=1;
        while(x%primes[i]==0){
            mult*=primes[i];
            factor+=mult;
            x/=primes[i];
        }
        ret*=factor;
    }
    if(x>1) ret*=(1+x);
    return ret;
}

vector<ll>sums(s,-1);
vector<ll>nums(s,-1);

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
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    int a, b, k; cin >> a >> b >> k;
    ll sum=0, num=0;
    for(int i =a; i<=b; i++){
        if(i%k!=0)continue;
        if(sums[i]==-1){
            sums[i]=sumDiv(i);
            nums[i]=numDiv(i);
        }
        sum+=sums[i];
        num+=nums[i];
    }
    cout << num << " " << sum;

}

