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

const int s = 4000001;
const int sh = 2000001;
vector<int> tots(sh, 0);
vector<ll> preGCDs(s, 0);// gcd sum of index i to all its prior
vector<ll> pfs(1); //sum to all its prior

void calc(){
    // euler phi sieve (we only need euler phi up the half (2KK)
    for(int i=0; i<sh; ++i) tots[i]=i;
    for(int i = 2; i<sh; ++i){
        if(tots[i]==i){
            for(int j=i; j<sh; j+=i){
                tots[j]-=tots[j]/i;
            }
        }
    }
    // calc gcd's: gcd(a, b) = sum_{k|a && k|b}phi(k)
    // idea: for all k, adde phi(k) to the multiples of k
    // use cnt, as factor, bc each time there is one element more, which also divides k
    for(int i=1;i<s;++i){
        ll cnt = 1;
        for(int j =2*i; j<s; j+= i){
            preGCDs[j]+=((cnt++)*tots[i]);
        }
    }

    // prefix sum;
    for(int i =1;i<s;++i){
        pfs.push_back(pfs.back() + preGCDs[i]);
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
    while(cin >>n){
        if(n==0)return;
        cout << pfs[n] << endl;
    }

}

