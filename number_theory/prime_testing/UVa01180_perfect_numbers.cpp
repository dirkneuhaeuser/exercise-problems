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
const int s = 1<<18;
//vector<int>sp(s+1, 1);
vector<int> primes;
bitset<s>p;
void sieve(){
    p.set();
    for(ll i=2;i<s;i++){
        if(p[i]==1){
            primes.push_back(i);
            for(ll j=i*i; j<s; j+=i){
                p[j]=0;
            }
        }

    }
}

ll sum_divs(int a, int b){
    ll ret = 1;
    for(int i=0;i<primes.size() && (primes[i]*primes[i] <= a || primes[i]*primes[i] <= b); ++i){
        ll total = 1, multiplier = 1;
        while(a%primes[i]==0){
            multiplier *= primes[i];
            total += multiplier;
            a /= primes[i];
        }
        while(b%primes[i]==0){
            multiplier *= primes[i];
            total += multiplier;
            b /= primes[i];
        }
        ret *= total;
        //cout << primes[i] << " " << ret << endl;
    }
    //cout << a <<  " " << b << endl;
    if(a==1 && b == 1){
        return ret;
    }else if(a==1){
        ret *= (1+b);
    }else if(b==1){
        ret *= (1+a);
    }else{
        if(a != b){
            ret*= (1+a);
            ret*= (1+b);
        }else{
            ret*=(1+a+a*a);
        }
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
    int n; cin >> n;
    //dbg(primes);
    //ll r = sum_divs(60,1);
    //dbg(r);
    while(n){
        int num; cin >> num;
        char bla; cin >> bla;
        ll a= pow(2, num-1);
        ll b= pow(2, num)-1;
        ll ret = sum_divs(a, b);
        if(ret == 2*a*b){
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
        n--;
    }

}

