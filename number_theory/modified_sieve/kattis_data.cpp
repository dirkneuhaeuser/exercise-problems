#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 

// 2**6 =  64
// 2**8 =  256
// 2**10 = 1,024
// 2**15 = 32,768
// 2**20 = 1,048,576
// 2**25 = 33,554,432
// 2**30 = 1,073,741,824
// 2**32 = 4,294,967,296

// int up to  2*10^9 (2^31-1)
// ll up to   9*10^18 (2^63 -1)
// ull up to 18*10^18 (2^64-1)/

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
    int k = 0;


    
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
    int n; cin >> n;
    int maxret = 0;
    vector<int> nums(n,0), comb(n, 0);
    for(int &num: nums){
        cin >> num;
    }

    // different pf up to n*1000 with modified sieve
    const int s=n*1000 + 1;
    vector<int> diffPf(s);
    for(int i=2;i<s; ++i){
        if(diffPf[i]==0){
            for(int j=i; j<s; j+=i){
                diffPf[j]++;
            }
        }
    }

    //all poss subsets and their distinct pf
    vector<int> dp(1<<n,0); 
    for(int mask = 1; mask<(1<<n); ++mask){
        int s=0;
        for(int j=0; j<n; ++j){
            if((mask&(1<<j))==(1<<j)){
                s+= nums[j];
            }

        }
        dp[mask]=diffPf[s];
    }


    // subset dp, if possible make subset smaller!
    for(int mask = 0; mask< (1<<n); ++mask){
        for(int i=0; i<mask; ++i){
            if((mask&i)==i){
                dp[mask] = max(dp[mask], dp[i]+dp[mask^i]);
            }
        }
    }

    cout << dp.back();

}

