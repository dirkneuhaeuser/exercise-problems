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

const  int s=2000001;
vector<int>totient(s);
vector<int>stepTotient(s);
vector<ll>pf;
void calc(){
    // precalculate totient with modified sieve
    for(int i = 1; i<s; ++i) totient[i]=i;
    for(int i=2;i<s;++i){
        if(totient[i]==i){
            for(int j=i; j<s; j+=i){
                totient[j]-=totient[j]/i;
            }
        }
    }
    // calculate totient-step with dp
    for(int i =2;i<s;++i){
        stepTotient[i] = 1+ stepTotient[totient[i]];
    }

    // use prefix sum to deliver results in O(1)
    for(int i=0; i<s; ++i){
        pf.push_back((i?pf.back():0) + stepTotient[i]);
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

    calc();
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
    int m, n;
    cin >> m>> n;
    cout << pf[n]-pf[m-1];

}

