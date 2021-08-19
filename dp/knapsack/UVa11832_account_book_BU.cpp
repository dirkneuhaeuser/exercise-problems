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

int sizeF;
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
void dfs(int sum,int numIdx, vector<vector<bool>> &dp, unordered_set<int> &used, vector<int> &nums, vector<vector<bool>> &visited){
    // Getting the solution from Bottom-up -> Backtrack solution, here we don't need to save the predecessors as we can simply check both possibilieties,
    // num[i] used, -num[i] used
    if(numIdx<0)return;
    if(visited[numIdx][sum]) return;
    visited[numIdx][sum] = true;
    if(sum >= nums[numIdx] && dp[numIdx][sum-nums[numIdx]] == true){
        used.insert(nums[numIdx]);
        dfs(sum - nums[numIdx],numIdx-1, dp, used, nums, visited);
    }
    if(sum+nums[numIdx] <sizeF && dp[numIdx][sum+nums[numIdx]] == true){
        used.insert(-nums[numIdx]);
        dfs(sum + nums[numIdx],numIdx-1, dp, used, nums, visited);
    }
}
void solve() 
{
    // Knapsack with offset and printing the solution. As the dp array is big in not all states are needed all the time, top-down would be better here.
    int n, sum; 
    while(cin >> n >> sum){
        if(n == 0 && sum == 0) return;
        sizeF = min(n*1001 * 2, 56002);

        // we also need the idx dimension (of nums), as we want to backtrack solution, 
        // and bc each number can be applied twice (negative and positie, we don't want them to influence (theoretically 2 Dims could be sufficient for this)
        vector<vector<bool>> dp(n+1, vector<bool>(sizeF, false));
        int offset = n*1001;
        vector<int> nums;
        dp[0][offset] = true;
        for(int i=1; i<=n; ++i){
            int num; cin >> num;
            nums.push_back(num);
            for(int j = sizeF-1; j>=num; --j){
                if(j - num >= 0 && dp[i-1][j-num] ){
                    dp[i][j] = true;
                }
            }
            FOR(j, sizeF){
                if(j + num < sizeF && dp[i-1][j+num] ){
                    dp[i][j] = true;
                }
            }
        
        }
        unordered_set<int> used;
        vector<vector<bool>> v(n+1, vector<bool>(sizeF, false));
        dfs(offset+sum,n-1, dp, used, nums, v);

        FOR(i, n){
            if(used.count(nums[i]) && used.count(-nums[i])){
                cout << "?";
            }else if(used.count(nums[i])){
                cout << "+";
            }else if(used.count(-nums[i])){
                cout << "-";
            }else{
                cout << "*";
                break;
            }
        }
        cout << endl;

    }



}

