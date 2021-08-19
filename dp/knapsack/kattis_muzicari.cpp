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

const int n_max = 501;
const int t_max = 5001;
int dp[n_max][t_max];// dp[i][j] := max. number of dudes after assigning the ith dude to the first slot (or not -> skip), s.t he/she ends his/her pause at j

vector<int> recover_sol(int n, int t, vector<int> &nums){
    int sol = dp[n][t];
    vector<int>ret;

    for(int i=n-1; i>=0; --i ){
        int curr = nums[i];
        if(dp[i][t-curr] + nums[i] ==  dp[i+1][t]){
            ret.push_back(i);
            t-=curr;
        }
    }

    return ret;

}

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
void solve() 
{
    // It seems greedy, but in fact, it is a job-shop scheduling problem, in which you want to minimise the makespan, s.t. it smaller/equal than T (duration of concert).
    // If you take greedily, you might end up with 2 minutes left for both slots, but the last guy needs 4 miniutes of rest -> can't split him.
    //
    // As there are only two pause-slots, the idea would be to utilize the first on as much as possible, s.t. the allocated pauses are in total <= T. We do this by knapsack-dp
    // Then we recover the solution, and all other dudes, will be assigned to the second slot.


    // knapsack: items: the band-members, value: the specfic pause-time, weight: pause-time
    int t, n; cin >> t >> n;
    priority_queue<int,vector<int>, ::greater<int>> q;
    vector<int> nums;
    FOR(i, n){
        int num; cin >> num;
        nums.push_back(num);
    }
    memset(dp, 0, sizeof dp);
    dp[0][0] = 0;

    for(int i =1; i<=n; ++i){
        int pauseTime = nums[i-1];
        for(int j =0; j<=t; ++j){
            dp[i][j] = dp[i-1][j]; // skipping current guy (he takes 2nd slot)
            if(j >= pauseTime && pauseTime + dp[i-1][j-pauseTime] <= t){
                dp[i][j] = max(dp[i][j], pauseTime + dp[i-1][j-pauseTime] );
            }

        }
    }
    vector<int> fst = recover_sol(n, t, nums);
    int idx = fst.size()-1;
    int fstSlotTime = 0;
    int sndSlotTime = 0;
    for(int i =0; i<n; ++i){
        if(idx >= 0 && fst[idx] == i){
            idx--;
            cout << fstSlotTime;
            fstSlotTime += nums[i];
        }else{
            cout << sndSlotTime;
            sndSlotTime += nums[i];
        }
        if(i<n-1){
            cout << " ";
        }
    }

}

