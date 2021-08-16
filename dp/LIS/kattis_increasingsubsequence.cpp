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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
bool isLexSmaller(vector<int> &a, vector<int> &b){
    for(int i=0; i<a.size(); ++i){
        if(a[i] < b[i]) return true;
        if(a[i] > b[i]) return false;
    }
    return true;
}
void solve() 
{
    // to find smalles lexicographically subsequence adjust the LISEned index when ever you find an element which is equal or smaller than the current head of the LIS vector.
    int n; 
    while(cin >> n && n){
        vector<int> A;
        FOR(i, n){
            int num; cin >> num;
            A.push_back(num);
        }
        vector<int> LIS(n), LISid(n), par(n);
        int k =0, LISEnd=0;
        vector<int> LISEnds;
        FOR(i, n){
            int pos = lower_bound(LIS.begin(), LIS.begin() + k, A[i]) - LIS.begin();
            if(pos == k){
                k++;
                LISEnd = i;
                LISEnds.push_back(i);
            }else if(pos == k-1 && A[i] <= LIS[pos]){
                // to find lexicographically smalles, adjust end if possible to further behind,
                // bc then you have more chances to have chosen smaller in general (more selection, and the greedy algo always take the smallest, overwriting of bigger ones)
                LISEnds.push_back(i);
                LISEnd = i;
            }
            LIS[pos] = A[i];
            LISid[pos] = i; // pos to idx, we only need that to construct the parent
            if(pos){
                par[i] = LISid[pos-1];
            }
        }

        vector<int> ret;
        FOR(i, k){
            ret.push_back(A[LISEnd]);
            LISEnd = par[LISEnd];
        }
        //reverse(ret.begin(), ret.end());
        cout << k << " ";
        FOR(i, k){
            cout << ret[k-1-i];
            if(i < k-1) cout << " ";
        }
        cout << endl;


    }
}

