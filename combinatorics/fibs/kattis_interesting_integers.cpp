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

const int s = 1000000000;

vector<int> fibs = {0, 1};

void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 
    int i =2;
    while(fibs.back()<s){
        fibs.push_back(fibs[i-1] + fibs[i-2]);
        i++;
    }
    
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
    // idea: let x and y be the g0 and g1, then the sequence woulde be:
    // x, y, x+y, x+2y, 2x+3y, 3x+5y, 5x+8y,... the coefficients are again fibonacci. For two consecutve fibonacci, find the coefficients s*fib[i-1] + t*fib[i] = n.
    // This again is a linear diophantine equation
    int n; cin >>n;
    int fibn = fibs.size()-2;
    int bmin = 1<<30;
    int amin = 1<<30;
    for(int i = 2; i<fibs.size()-1; ++i){
        ll a = fibs[i-1], b=fibs[i], s, t;
        ll d = eea(a, b, s, t);
        if (n%d){
            continue;
        }

        s*=(n/d);
        t*=(n/d);

        ll left = fibs[i]/d;
        ll right = fibs[i-1]/d;



        int times = (s-t)/(left + right);
        s -= times*left;
        t += times*right;
        if (s>t){
            t += right;
            s -= left;
        }

        if(s<=0 || t<=0){
            continue;
        }

        if(s<=t && t<bmin && s<amin){
            bmin = t;
            amin = s;
        }
    }
    while(bmin-amin>0 && bmin - amin <= amin){
        int aminNew = bmin - amin;
        bmin = amin;
        amin = aminNew;
    }
    cout << amin << " " << bmin;



}

