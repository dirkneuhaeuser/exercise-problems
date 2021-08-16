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
const int s = 1415;
vector<int>primes;
bitset<s>p;
void sieve(){
    p.set();
    for(ll i =2; i<s; ++i){
        if(p[i]){
            primes.push_back(i);
            for(ll j = i*i; j<s; j+=i){
                p[j]=0;
            }
        }
    }
}
int numPf(int x){
    int ret = 0;
    for(int i=0; i<primes.size() && primes[i]*primes[i]<=x; i++){
        while(x%primes[i]==0){
            ret++;
            x/=primes[i];
        }
    }
    if(x>1)ret++;
    return ret;
}

vector<pii> pfs(2000000,{0,0});

void sortMe(){
    sieve();
    for(int i=1;i<pfs.size()+1;++i){
        pfs[i-1]={numPf(i),i};
    }
    sort(pfs.begin(), pfs.end());
    //dbg(pfs);
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

    sortMe();

    
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
    int count = 1;
    while(cin >> n){
        if(!n)return;
        cout<<"Case " << count++ << ": ";
        cout << pfs[n-1].second << endl;
    }
}

