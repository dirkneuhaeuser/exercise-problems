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

const int s = (1<<16);
vector<int> primes;
bitset<s+1> p;
void sieve(){
    p.set();
    for(ll i = 2; i<s; ++i){
        if(p[i]==1){
            primes.push_back(i);
            for(ll j = i*i; j<s; j+=i){
                p[j]=0;
            }
        }
    }
}

vector<int> getPF(int x){
    vector<int> ret;
    for(int pr:primes){
        while(x%pr==0){
            ret.push_back(pr);
            x/=pr;
        }
    }
    if(x>1){
        ret.push_back(x);
    }
    return ret;
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
    sieve();
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
        if(n==0)break;
        cout << n << " =";
        if(n<0){
            cout << " -1 x";
            n=abs(n);
        }
        vector<int> ret = getPF(n);
        for(int i=0; i< ret.size(); ++i){
            if(i==0){
                cout << " " << ret[i];
            }else{
                cout << " x " << ret[i];
            }
        }
        cout << endl;

    }

}

