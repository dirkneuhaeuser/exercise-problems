#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;                                               // 2**6 =  64                           // 4!  = 24                        
typedef unsigned long long ull;                                     // 2**8 =  256                          // 5!  = 120                       
typedef long double ld;                                             // 2**10 = 1,024                        // 6!  = 720
typedef pair<long, long> pll;                                       // 2**15 = 32,768                       // 7!  = 5,040
typedef pair<int, int> pii;                                         // 2**20 = 1,048,576                    // 8!  = 40,320
#define FOR(i, n) for(int i=0; i<n; i++)                            // 2**25 = 33,554,432                   // 9!  = 362,880
#define FORS(i, n) for(; i<n; i++)                                  // 2**30 = 1,073,741,824                // 10! = 3,628,800
#ifdef DIRK                                                         // 2**32 = 4,294,967,296                // 12! = 479,001,600
#include "/Users/dirk/development/algorithms/templates/debug.h"                                             // 14! = 87,178,291,200
#endif                                                              // int up to  2*10^9 (2^31-1)           // 16! = 20,922,789,888,000
                                                                    // ll up to   9*10^18 (2^63 -1)         // 18! = 6,402,373,705,728,000
                                                                    // ull up to 18*10^18 (2^64-1)/         // 20! = 2,432,902,008,176,640,000
ll smod(ll a, ll m){return((a%m) +m) %m;}
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*b,m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;


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
    // linear diophantine
    ll n, c1, n1, c2, n2;
    while(cin >> n &&n!=0){
        cin >> c1 >> n1>>c2 >> n2;
        // n1*s = n2*t = d
        // eea
        ll s, t;
        ll d = eea(n1, n2, s, t);
        if(n%d){
            // no solution
            cout << "failed" << endl;
            continue;
        }
        // n1*s = n2*t = n
        s = s*n/d;
        t = t*n/d;
        // now you can shift these q units: 
        // s+= n2/d*q
        // t-= n1/d*q
        if(s<0){
            bool isRest = s%(n2/d);
            int ans = abs(s/(n2/d));
            s+= (ans + isRest) *(n2/d);
            t-= (ans + isRest) * (n1/d);
        }
        while(t<0){
            bool isRest = t%(n1/d);
            int ans = abs(t/(n1/d));
            s-= (ans + isRest) *(n2/d);
            t+= (ans + isRest) * (n1/d);
        }
        if(s<0){ // sols has to be positive
            cout << "failed" << endl;
            continue;
        }


        // go into direction of best use/cost ratio
        if(n2*c1 > n1*c2){ // t2 has better use/cost ratio
            int ans = s/(n2/d); 
            s-= ans*(n2/d);
            t+= ans*(n1/d);
        }else{
            int ans = t/(n1/d); 
            s+= ans*(n2/d);
            t-= ans*(n1/d);
        }
        cout << s << " "<< t <<endl;

    }

}

