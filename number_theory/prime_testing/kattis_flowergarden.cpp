#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first

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
#define ll long long  
#define ull unsigned long long 
#define ld long double
#define FOR(i, n) for(int i=0; i<n; i++)
#define FORS(i, n) for(; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/templates/debug.h"
#endif

const int MOD = 1000000007;
using namespace std; 

const int s=20001;
bitset<s> p;
vector<int> primes(1,0);
void sieve(){
    p.set();
    p[1]=0;
    for(ll i=2;i<s;++i){
        if(p[i]){
            primes.push_back(i);
            for(ll j=i*i; j<s; j+=i){
                p[j]=0;
            }
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
ld getdist(ld x, ld y, ld xn, ld yn) {
    //return sqrt(pow(x-xn,2) + pow(y-yn,2));
    long double diff = sqrt((long double)(pow(abs(xn-x),2) + pow(abs(yn-y),2)));
    return diff;
    //return sqrt((pow(abs(xn-x),2) + pow(abs(yn-y),2)));
}
void solve() 
{
    int N;cin >> N; 
    ld D;cin >> D;

    ll ret =0;
    ll count = 0;
    ld dis=0;

    int x = 0, y=0;
    while(N){
        int xn, yn;
        cin >> xn >> yn;
        long double diff = getdist(x, y, xn, yn);
        x = xn;
        y = yn;
        dis += diff;
        if(dis <= D){
            count++;
            if(p[count]){
                ret = count;
            }
        };
        N--;
    }
    cout << ret;
}

