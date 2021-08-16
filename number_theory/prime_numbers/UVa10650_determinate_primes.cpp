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

const int s = 32001;
bitset<s> p;
vector<int> primes;
void sieve(){
    p.set();
    for(ll i=2; i< s; ++i){
        if(!p[i]) continue;
        primes.push_back(i);
        for(ll j=i*i; j<s; j+= i){
            p[j]=0;
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
    int a, b;
    while(cin >> a >> b){
        if(a == 0 && b==0)break;
        if(a>b) swap(a, b);
        int idx = (upper_bound(primes.begin(), primes.end(), a-1) - primes.begin());
        //cout << idx << endl;
        for(int i = idx; (i < primes.size() - 2) && (primes[i+2] <=b); ++i){
            int diff = primes[i+1]-primes[i];
            if(primes[i+1]+diff == primes[i+2]){
                int j = i+2;
                while((j+1 < primes.size())&& ((primes[j] + diff) == primes[j+1])){
                    j++;
                }
                if(primes[j]>b){
                    break;
                }
                if(i && primes[i]-diff == primes[i-1]) continue;
                for(int k = i; k < j; ++k){
                    cout << primes[k] << " ";
                }
                cout << primes[j] <<endl;
                i = j-1;
            }
            
        }
    }

}

