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

int memo[101][101][101];
vector<int> circle;
int INF = 1 << 30;
int n;

int dp(int i, int j, int start){
    // i moves to left and j moves to right have been conducted already.
    if(memo[i][j][start] != INF) return memo[i][j][start];
    bool ourTurn = ((i+j)&1)==1; // if even, its our turn;
    if(i+j >=n-1 ) return memo[i][j][start] = 0;
    int ret =0;
    int nextRight = (start+j+1) % n;
    int nextLeft = ((start-i-1) + n) % n;
    if(ourTurn){
        int ans1 = dp(i, j+1, start) + (circle[nextRight]&1 );
        int ans2 = dp(i+1, j, start) + (circle[nextLeft]&1 );
        return memo[i][j][start] = max(ans1, ans2);
    }else{
        int ans1 = dp(i, j+1, start) - (circle[nextRight]&1 );
        int ans2 = dp(i+1, j, start) - (circle[nextLeft]&1 );
        return memo[i][j][start] = min(ans1, ans2);

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
    cin >>n;
    FOR(i, n+1){
        FOR(j, n+1){
            FOR(k, n+1){
                memo[i][j][k] = INF;

            }
        }
    }


    FOR(i, n){
        int num;
        cin >> num;
        circle.push_back(num);
    }

    int ans = 0;
    FOR(i, n){
        int  ret = dp(0, 0, i);
        if(circle[i]&1) ret++;
        if(ret>0) ans++;
    }
    cout << ans;
}

