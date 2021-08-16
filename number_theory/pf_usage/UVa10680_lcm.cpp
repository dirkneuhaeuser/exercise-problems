#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 

// 2**6 =  64                           // 5!  = 120                        
// 2**8 =  256                          // 10! = 3,628,800
// 2**10 = 1,024                        // 12! = 479,001,600
// 2**15 = 32,768                       // 14! = 87,178,291,200
// 2**20 = 1,048,576                    // 16! = 20,922,789,888,000
// 2**25 = 33,554,432                   // 18! = 6,402,373,705,728,000
// 2**30 = 1,073,741,824                // 20! = 2,432,902,008,176,640,000
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

const int s =1001;
vector<int> primes;
bitset<s>p;
void sieve(){
    p.set();
    for(ll i =2; i<s; ++i){
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

vector<int> newRet = {6, 2, 8, 4};


void solve() 
{

    // idea: LCM(x,y) = max power of both prime-factores. Problem: number will become very large -> keep only the last digit, BUT, if you happen to find another 5 (so max power of pf 5 increases) than take out a 2 (this will get rid of a trailing zero)
    int size_all = 1000001;
    vector<ll> lcms_last(size_all,-1);
    vector<ll> pfs(size_all,0);
    ll ret=1;
    for(int i=1; i<size_all; ++i){
        int num =i;
        for(int j=0; j<primes.size() && primes[j]*primes[j]<=num; j++){
            int times =0;
            while(num%primes[j] ==0){
                times++;
                num/=primes[j];
            }
            if(times>pfs[primes[j]]){
                int diff = times -pfs[primes[j]];
                if(primes[j]==5){
                    while(diff){// 2 -> 6, 4-> 2, 6->8, 8->4
                        if(ret == 2){
                            ret = 6; 
                        }else if(ret == 4){
                            ret = 2;
                        }else if(ret == 6){
                            ret = 8;
                        }else{
                            ret = 4;
                        }
                        diff--;
                    }
                }else{
                    while(diff){
                        ret*=primes[j];
                        diff--;
                    }
                }
                pfs[primes[j]] =times;
            }

        }
        if(!pfs[num]){
            pfs[num]++;
            if(num == 5){
                if(ret == 2){
                    ret = 6;
                }else if(ret == 4){
                    ret = 2;
                }else if(ret == 6){
                    ret = 8;
                }else{
                    ret = 4;
                }
            }else{
                ret*=num;
            }
        }
        while(ret%10==0){
            ret/=10;
        }
        ret = ret%10;
        lcms_last[i]=ret;

    }
    int n;
    while(cin >> n){
        if(n==0) return;
        cout << lcms_last[n] <<endl;
    }

}

