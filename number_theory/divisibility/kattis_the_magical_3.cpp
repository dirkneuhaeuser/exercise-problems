#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
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

// 2**6 =  64                           // 4!  = 24                       
// 2**8 =  256                          // 5!  = 120                      
// 2**10 = 1,024                        // 6!  = 720
// 2**15 = 32,768                       // 7!  = 5,040
// 2**20 = 1,048,576                    // 8!  = 40,320
// 2**25 = 33,554,432                   // 9!  = 362,880
// 2**30 = 1,073,741,824                // 10! = 3,628,800
// 2**32 = 4,294,967,296                // 12! = 479,001,600
                                        // 14! = 87,178,291,200
// int up to  2*10^9 (2^31-1)           // 16! = 20,922,789,888,000
// ll up to   9*10^18 (2^63 -1)         // 18! = 6,402,373,705,728,000
// ull up to 18*10^18 (2^64-1)/         // 20! = 2,432,902,008,176,640,000                                                                    
//
ll smod(ll a, ll m){return((a%m) +m) %m;}
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*b,m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;

const int s= 1<<16;
vector<int> primes;
bitset<s>p;
void sieve(){
    p.set();
    for(ll i =2; i<s;++i){
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
void solve() 
{
    // intution: problem boils down to find the first prime, which devides (n-3), but you are not allowed to take 2 or 3 itself
    ll n;
    while(cin >>n && n){
        ll num = n;
        if(num < 3){
            cout << "No such base" << endl;
            continue;
        }else if(num==3){
            cout << "4" << endl;
            continue;
        }
        num -=3;
        bool first2 = true;
        bool first3 = true;
        ll INF = 1ll<<62;
        ll ret = INF;
        for(int i = 0; (ll)primes[i]*(ll)primes[i] <= num; ++i){
            if(primes[i]==2){
                if(num%4==0){
                    ret = min(ret, 4ll);
                }
            }else if(primes[i]==3){
                if(num%9==0){
                    ret = min(ret, 9ll);
                }
            }else{
                if(num%primes[i] == 0){
                    ret = min(ret, (ll)primes[i]);
                }
            }

        }
        if(num%6==0){
            ret = min(ret, 6ll);
        }
        if(num>3){
            ret = min(ret, num);
        }
        // the left overs are still primes and could be used
        if(num%3==0 && num/3 > 3){
            ret = min(ret, num/3);
        }
        if(num%2==0 && num/2 > 3){
            ret = min(ret, num/2);
        }
        if(num%6==0 && num/6 > 3){
            ret = min(ret, num/6);
        }
        if(ret == INF){
            cout << "No such base" << endl;
        }else{
            cout <<ret << endl;
        }

    }

}

