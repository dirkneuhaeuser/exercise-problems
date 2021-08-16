#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
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
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;
const int INF = 1<<30;


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
    cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
        if(t) cout << endl;
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    // IDEA: Prefixsum over the AB Planes for all C in O(A*B*C), and then kadane over C for each rectangle size for in total in O(A^2 * B^2 * C)
    // Note: The result can't be empty: In Worst-Case, take the 'smallest' (from magnitude perspective) negative element.
    // Also, I use a left and upper zero-frame for the AB planes; right and left border always are included: subtract left - 1;
    int a,b,c; cin >> a >> b >> c;
    ll NINF = 1ll << 63; 
    ll cube[a+1][b+1][c];
    memset(cube, 0, sizeof cube);
    ll maxE = NINF;
    FOR(i, a){
        FOR(j, b){
            FOR(k, c){
                cin >> cube[i+1][j+1][k];
                maxE = max(cube[i+1][j+1][k], maxE);
            }
        }
    }
    // prefix sum over a and b
    FOR(k, c){
        FOR(i, a){
            ll rowSum = 0;
            FOR(j, b){
                rowSum+= cube[i+1][j+1][k];
                cube[i+1][j+1][k] = rowSum;
                if(i>0){
                    cube[i+1][j+1][k] += cube[i][j+1][k];
                }
            }
        }
    }

    // and now kadane over c:
    ll ret = 0;
    for(int li=1; li<=a; ++li){
        for(int ri=li; ri<=a; ++ri){
            for(int lj=1; lj<=b; ++lj){
                for(int rj=lj; rj<=b; ++rj){
                    ll curSum = 0;
                    for(int k =0; k<c; ++k){
                        curSum += cube[ri][rj][k] - cube[li-1][rj][k] - cube[ri][lj-1][k] + cube[li-1][lj-1][k];
                        curSum = max(curSum, 0ll);
                        ret = max(ret, curSum);
                    }
                }
            }
        }
    }
    if(ret == 0){
        cout << maxE;
    }else{
        cout << ret;
    }

}

