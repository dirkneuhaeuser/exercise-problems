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

const int maxJ = 30001;
ll dp[101][maxJ];

vector<int> recover_solution(int order, int n, vector<int> &nums){
    // BU reconstruction
    vector<int> ret;
    for(int i = n; i>0; --i){
        int num = nums[i-1];
        for(int &k = order; k>=0; k-=num){
            if(dp[i-1][k] == 1){
                break;
            }
            ret.push_back(i);
        }
    }
    return ret;
}

void solve() 
{
    // knapsack with index for reconstruction and additional for-loop to check the possibilities for having multiple dishes
    int n; cin >> n;
    vector<int> nums(n);
    FOR(i, n){
        cin >> nums[i];
    }
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1; // possibilieties dp
    for(int i=1; i<=n; ++i){
        int num = nums[i-1];
        for(int j = 0; j<maxJ; j++){
            // blow possibilites by checking all the possibilietes for the current dish
            for(int k=j; k>=0; k-= num){
                dp[i][j] += dp[i-1][k]; 
            }
        }
    }
    int m; cin >> m;
    vector<int> orders(m);
    FOR(i, m){
        cin >> orders[i];
        if(dp[n][orders[i]] == 0){
            cout << "Impossible" << endl;
        }else if(dp[n][orders[i]] != 1){
            cout << "Ambiguous" << endl;
        }else{
            vector<int> ret = recover_solution(orders[i], n, nums);
            FOR(i, ret.size()){
                cout << ret[ret.size()-1 -i];
                if(i < ret.size() -1){
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    


}

