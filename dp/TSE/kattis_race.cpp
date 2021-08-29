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
const int NINF = 1<<31;


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
int memo[22][(1<<20)];

int LSOne(int num){
    return num&-num;
}

// dp retuns the min time to go from start and finalise all in mask and also current
// if not possible with current deadline -> return INF;
// we do the dp here from right to left, as this will cumulate the numbers from right -> format we need to compare to the deadlines.
int dp(int cur, int mask, vector<vector<int>> &stops, vector<vector<int>> &am){
    int &ans = memo[cur][mask];
    if(ans != -1) return ans;
    int dest = am.size() -1;
    int start = am.size() -2;
    if(mask == 0){
        if(cur!=dest){
            int t = am[start][cur] + stops[cur][1];
            if(stops[cur][2] != -1 && stops[cur][2] < t){
                return ans = INF;
            }else{
                return ans = t;
            }
        }else{
            int t = am[start][cur];
            if(stops.back()[2] < t){
                return ans = INF;
            }else{
                return ans = t;
            }
        }
    }

    ans = INF;
    int m = mask;
    while(m){
        int v = LSOne(m);
        int next = __builtin_ctz(v);
        int step = dp(next, mask^v, stops, am);
        if(cur == dest){
            if(step != INF){
                ans = min(ans, am[next][cur] + step);
            }
        }else if(cur != dest){
            if(step != INF){
                ans = min(ans, stops[cur][1] + am[next][cur] + step);
            }   
        }
        m^=v;
    }
    if(cur == dest){
        if(stops.back()[2] != -1 && stops.back()[2] < ans) ans = INF;
    }else{
        if(stops[cur][2] != -1 && stops[cur][2] < ans) ans = INF;
    }
    return ans;
}


void solve() 
{
    // Hamiltionian Path Problem with deadline-restrictions on each node: Try all potential mask: If it is possible to have hamiltoninan path, save its value and go to next mask
    int n, t; cin >> n >> t;
    vector<vector<int>> stops;
    FOR(i, n){
        int a, b, c; cin >> a >> b >> c;
        vector<int> cur = {a, b, c};
        stops.push_back(cur);
    }
    vector<int> cur = {0, 0, t};
    stops.push_back(cur);
    vector<vector<int>> am(n+2, vector<int>(n+2, 0));
    FOR(i, n+2){
        FOR(j, n+2){
            cin >> am[i][j];
        }
    }

    int ret = 0;
    int retMask = 0;
    memset(memo, -1, sizeof memo);
    for(int i=n; i>=0; i--){
        vector<bool> toUse(n, false);
        FOR(j, i){
            toUse[j]=true;
        }
        do{
            int mask = 0;
            int value = 0;
            FOR(k, n){
                if(toUse[k]){
                    mask ^= (1<<k);
                    value += stops[k][0];
                }
            }
            int time_needed = dp(n+1, mask, stops, am);
            if(time_needed < INF && ret < value){
                ret = value;
                retMask = mask;
            }

        }while(prev_permutation(toUse.begin(), toUse.end()));
    }
    cout << ret << endl;
    if(retMask){
        FOR(i, n){
            if(retMask&(1<<i)){
                cout << (i+1) << " ";
            }
        }
    }else{
        cout << endl;
    }
}

