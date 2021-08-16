#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
#ifdef DIRK                                                    
#include "/Users/dirk/development/algorithms/templates/debug.h"
#endif

using namespace std;                        // 2**6 =  64                           // 4!  = 24                        
typedef long long ll;                       // 2**8 =  256                          // 5!  = 120                      
typedef unsigned long long ull;             // 2**10 = 1,024                        // 6!  = 720
typedef long double ld;                     // 2**15 = 32,768                       // 7!  = 5,040
typedef pair<long, long> pll;               // 2**20 = 1,048,576                    // 8!  = 40,320
typedef pair<int, int> pii;                 // 2**25 = 33,554,432                   // 9!  = 362,880
#define FOR(i, n) for(int i=0; i<n; i++)    // 2**30 = 1,073,741,824                // 10! = 3,628,800
#define FORS(i, n) for(; i<n; i++)          // 2**32 = 4,294,967,296                // 12! = 479,001,600
                                                                                    // 14! = 87,178,291,200
                                            // int up to  2*10^9 (2^31-1)           // 16! = 20,922,789,888,000
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
    ll c;
    while(cin >> c && c){
        // c = n-m
        // n = 10*m + b
        // => 9*m + b = c --> diophantine equation
        ll s, t, x=9, y=1; 
        ll d = eea(x,y, s, t);

        if(c%d){
            cout << endl;
            continue;
        }
        // adjust equation for ride side
        s = s*(c/d); // still divisable by d
        t = t*(c/d);

        // prepare lcm movement to left and right 
        ll left = y/d;
        ll right = x/d;

        if(t<0){
            ll times = t/right + 2;
            s-= left*times;
            t+= right*times;
        }
        if(t>=0){ // t can be between 0 and 9
            ll times = t/right;
            s+= left*times;
            t-= right*times;
        }
        vector<ll> ret;
        while(s > 0 && t>=0 && t<=9){ // b on the other hand is last digit which was cut of, ok to be 0
            ret.push_back(10*s+t);
            s-= left;
            t+= right;
        }
        sort(ret.begin(), ret.end());
        FOR(i, ret.size()){
            cout << ret[i];
            if(i<ret.size()-1) cout << " ";
        }
        cout << endl;
    }
}

