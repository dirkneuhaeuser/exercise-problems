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
// ld up to  10*10^307
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
int getVal(int x, int y){
    if(x==2 && y == 1) return 21;
    if(x==6 && y == 6) return 20;
    if(x==5 && y == 5) return 19;
    if(x==4 && y == 4) return 18;
    if(x==3 && y == 3) return 17;
    if(x==2 && y == 2) return 16;
    if(x==1 && y == 1) return 15;
    if(x==6 && y == 5) return 14;
    if(x==6 && y == 4) return 13;
    if(x==6 && y == 3) return 12;
    if(x==6 && y == 2) return 11;
    if(x==6 && y == 1) return 10;
    if(x==5 && y == 4) return 9;
    if(x==5 && y == 3) return 8;
    if(x==5 && y == 2) return 7;
    if(x==5 && y == 1) return 6;
    if(x==4 && y == 3) return 5;
    if(x==4 && y == 2) return 4;
    if(x==4 && y == 1) return 3;
    if(x==3 && y == 2) return 2;
    if(x==3 && y == 1) return 1;
    return 0;
}
void solve() 
{
    char a, b, x, y; 
    // complete search it
    while(cin >> a >> b >> x >> y){
        if(a=='0') return;
        int ret =0;
        for(int i=1; i<7; ++i){
            for(int j=1; j<7; ++j){
                for(int k=1; k<7; ++k){
                    for(int l=1; l<7; ++l){
                        int t1 = i, t2 = j, t3 = k, t4=l;
                        if(a!='*') t1=a -'0';
                        if(b!='*') t2=b -'0';
                        if(x!='*') t3=x -'0';
                        if(y!='*') t4=y -'0';
                        if(t1 < t2) swap(t1,t2);
                        if(t3 < t4) swap(t3,t4);
                        bool suc = getVal(t1, t2) > getVal(t3, t4);
                        ret += suc;
                    }
                }
            }
        }
        int denom = 1296;
        if(ret == 0){
            cout << 0 << endl;
        }else if(ret == denom){
            cout << 1 << endl;
        }else{
            int d = __gcd(ret,denom);
            cout <<ret/d << "/" << denom/d << endl;
        }
    }
}

