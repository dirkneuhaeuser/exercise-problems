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
int memo[41][56002];
bool alr[41][56002];
int td(int idx, int sum, int goal, vector<int> &nums){
    if(idx < 0 && sum == goal) {
        return 1;
    }
    if(idx < 0){
        return 0;
    }
    int &ans = memo[idx][sum];
    if(ans != -1) return ans;
    if(td(idx-1, sum+nums[idx], goal, nums) == 1){
        ans = 1;
    }
    if(td(idx-1, sum-nums[idx], goal, nums) == 1){
        ans = 1;
    }
    if(ans == -1){
        ans =0;
    }
    return ans;
}
void get_solution(int idx, int sum, int goal, vector<int> &nums, set<int> &ret){
    // The reconstruction of the solution can be done by a very similiar dp to the original one.
    // Here we need also a visited array alr, as it growth is 2^n
    if(idx < 0 && sum == goal) {
        return;
    }
    if(idx < 0){
        return;
    }
    if(alr[idx][sum]) return;
    alr[idx][sum] = true;
    if(td(idx-1, sum+nums[idx], goal, nums) == 1){
        ret.insert(nums[idx]);
        get_solution(idx-1, sum+nums[idx], goal, nums, ret);
    }
    if(td(idx-1, sum-nums[idx], goal, nums) == 1){
        ret.insert(-nums[idx]);
        get_solution(idx-1, sum-nums[idx], goal, nums, ret);
    }
}

void solve() 
{
    // Knapsack with offset and printing the solution. As the dp array is big in not all states are needed all the time, top-down would be better here.
    int n, sum; 
    while(cin >> n >> sum){
        if(n == 0 && sum == 0) return;
        vector<int> nums(n);
        FOR(i, n){
            cin >> nums[i];
        }
        int offset = 28001;

        memset(memo, -1, sizeof memo);
        memset(alr, 0, sizeof alr);

        td(n-1, offset, sum+offset, nums);
        set<int>used;
        get_solution(n-1, offset, sum+offset, nums, used);

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

