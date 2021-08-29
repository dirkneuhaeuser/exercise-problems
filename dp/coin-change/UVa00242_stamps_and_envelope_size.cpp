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
void solve() 
{
    // check for all possible values [0, 1000] if it is possible to cover it with s stamps. dp[i][j] := after taken the ith stamp, is it possible to achive j.
    // here we get rid of the first dimension, because we can always reuse the the same array.
    // Note: This algorithm didn't get accepted because of presentation error.
    // As the presentation is super specific and not stated in the problem, I don't want to was my time here.
    int s;
    while(cin >> s && s){
        int n; cin >> n;
        vector<vector<int>> sets;
        FOR(i, n){
            int m; cin >> m;
            vector<int> nums(m);
            FOR(j, m){
                cin >> nums[j];
            }
            sets.push_back(nums);
        }
        sort(sets.begin(), sets.end(), [](vector<int> &left, vector<int> &right){
            if (left.size() < right.size()){
                return true;
            }else if (left.size() > right.size()) {
                return false;
            }else{
                for(int i= left.size()-1; i>=0; --i){
                    if(left[i] < right[i]){
                        return true;       
                    }
                    if(left[i] > right[i]){
                        return false;       
                    }
                }
                return true;
            }
        });
        int maxCoverage = 1001;
        bool dp[maxCoverage];
        int maxE = 0;
        int maxI = 0;
        FOR(l, n){
            memset(dp, 0, sizeof dp);
            dp[0] = true;
            for(int i=1; i<=s; ++i){
                for(int j=maxCoverage-1; j>=0; --j){
                    for(int k=0; k< sets[l].size(); ++k){
                        int cur = sets[l][k];
                        if(j>= cur && dp[j-cur]){
                            dp[j] = true;
                            break;
                        }
                    }
                }
            }
            FOR(i, maxCoverage){
                if(dp[i]){
                    if(i> maxE){
                        maxE = i;
                        maxI = l;
                    }
                }else{
                    break;

                }
            }
        }
        cout << "max coverage = ";
        int num =maxE; 
        if(num >= 100){
            cout << num;
        }else if(num > 10){
            cout << " " << num;
        }else{
            cout << "  " << num;
        }


        cout << " :";
        FOR(i, sets[maxI].size()){
            int num =sets[maxI][i]; 
            if(num == 100){
                cout << num;
            }else if(num > 10){
                cout << " " << num;
            }else{
                cout << "  " << num;
            }
        }
        cout << endl;

    }

}

