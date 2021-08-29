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
const ld INF = (ld)(1<<30);


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

int LSOne(int x){
    return x&(-x);
}

ld getDistance(pii c1, pii c2){
    int x1 = c1.first;
    int y1 = c1.second;
    int x2 = c2.first;
    int y2 = c2.second;
    return pow(pow(x1-x2, 2) + pow(y1-y2, 2), 0.5) + 16.;

}

ld memo[8][(1<<8)-1];

ld dp(int cur, int mask, vector<pii> &coords){
    ld &ans = memo[cur][mask];
    if(ans != (ld)-1) return ans;
    if(mask == 0){
        ans = 0;
        return ans;
    }
    int m = mask;
    ans = INF;
    while(m){
        int v = LSOne(m);
        int next = __builtin_ctz(v);
        ans = min(ans, dp(next, mask^v, coords) + getDistance(coords[cur], coords[next]) );
        m ^= v;
    }
    return ans;
}

void getSolution(int cur, int mask, vector<pii> &coords, vector<int> &sol){
    // retrieving the solution.
    sol.push_back(cur);
    if(mask == 0)return;
    int m = mask;
    ld &ans = memo[cur][mask];
    while(m){
        int v = LSOne(m);
        int next = __builtin_ctz(v);
        if(memo[next][mask^v] + getDistance(coords[cur], coords[next]) == ans){
            getSolution(next, mask^v, coords, sol);
            return;
        }
        m ^= v;
    }

}


void solve() 
{
    // TSM-problem. Here no circle but a route passing through all cities 'computers' without returning. Thus it makes a difference where to start. 
    // In classical TSM you can just choose a given node as your start and end point and you don't have to change it. 
    // Here, we have to try all possible start points. But the algorithm stays the same.
    int count = 1;
    int n; 
    while(cin >> n && n){
        vector<pii> comps;
        FOR(i, n){
            int a, b;
            cin >> a >> b;
            comps.push_back({a, b});
        }

        int maxI = 0;
        ld minE =  (ld) INF;
        FOR(i, n){
            ld val = (ld) - 1;
            fill_n(&memo[0][0], 8*((1<<8) - 1), val);
            int mask = (1<<n)-1;
            mask ^= (1<<i);
            ld ans = dp(i, mask, comps);
            if(ans < minE){
                minE = ans;
                maxI = i;
            }

        }

        int mask = (1<<n)-1;
        mask ^= (1<<maxI);
        ld val = (ld) - 1;
        fill_n(&memo[0][0], 8*((1<<8) - 1), val);
        ld ans = dp(maxI, mask, comps);
        vector<int> ret;
        getSolution(maxI, mask, comps, ret);
        cout << "**********************************************************"  << endl;
        cout << "Network #" << count++ << endl;
        FOR(i, n-1){
            cout << "Cable requirement to connect (" << comps[ret[i]].first <<","<< comps[ret[i]].second << ") to (" << comps[ret[i+1]].first <<","<< comps[ret[i+1]].second << ")";
            cout << setprecision(2) << fixed;
            cout << " is " << getDistance(comps[ret[i]], comps[ret[i+1]])<<" feet." << endl;
        }
        cout << "Number of feet of cable required is " << ans << "." << endl;

    }

}

