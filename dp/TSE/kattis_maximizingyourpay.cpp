#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
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
    freopen("/Users/dirk/development/algorithms/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/output.txt", "w", stdout); 
    #endif 
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

int memo[10][(1<<10)];

int LSOne(int num){
    return num&-num;
}

int dp(int cur, int mask, vector<vector<bool>> &am){
    int &ans = memo[cur][mask];
    if(ans != -1)return ans;
    if(mask == 0){
        if(am[cur][0]){
            return ans=1;
        }else{
            return ans=0;
        }
    }
    ans = 0;
    int m = mask;
    while(m){
        int v = LSOne(m);
        int next = __builtin_ctz(v)+1;
        if(am[cur][next]){
            if(dp(next, mask^v, am)){
                ans = 1;
            }
        }
        m^=v;
    }
    return ans;
}



void solve() 
{
    // Seach greates hamiltionian cycle;
    // Try all possible masks and check if there is a hamiltionian cycle. 
    // Note to check if there is a hamiltionian cycle we don't need to minimise anythin, just possible or not possible to visit all.
    int n, m;
    while(cin >> n >> m){
        memset(memo, -1, sizeof memo);
        vector<vector<bool>> am(n, vector<bool>(n, false));
        FOR(i, m){
            int a, b; cin >> a >> b;
            am[a][b] = true;
            am[b][a] = true;
        }
        bool done = false;
        for(int i=n; i>=0; i--){
            vector<bool> toUse(n, false);
            FOR(j, i){
                toUse[j]=true;
            }
            do{
                if(!toUse[0]) continue;
                int mask = 0;
                int ans = 1;
                for(int j=1; j<n; ++j){
                    if(toUse[j]){
                        ans++;
                        mask ^= (1<<(j-1));
                    }
                }
                int ret = dp(0, mask, am);
                if(ret == 1){
                    cout << ans << endl;
                    done = true;
                    break;
                }
            }while(prev_permutation(toUse.begin(), toUse.end()));
            if(done){
                break;
            }
        }
        if(!done){
            cout << 1 << endl;
        }
    }
}

