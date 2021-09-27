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


int h, k, Max, ma [10], stamp [10], ans [10], vis [200];//ma records the maximum value of each backtracking, stamp records the denomination
void dfs (int cur, int n, int s)//Find out the value that can be reached at this time
{
    vis [s] = 1;
    if (cur >= h) return;
    int i;
    for (i = 0; i <n; i ++)
        dfs (cur + 1, n, s + stamp [i]);
}

void search (int cur)
{
    int i, j;
    if (cur >= k)
    {
        if (ma [cur-1]> Max)
        {
            for (i = 0; i <k; i ++) ans [i] = stamp [i];
            Max = ma [cur-1];
        }
        return;
    }
    // The value range of each retrospective denomination is from the last denomination +1 to the last maximum value +1
    // (cannot be larger, if it is larger, it is impossible to reach the previous max denomination +1).
    for (i = stamp [cur-1] +1; i <= ma [cur-1] +1; i ++) // why can you only go to max?
    {
        stamp [cur] = i;
        memset (vis, 0, sizeof (vis));
        dfs (0, cur + 1,0);
        for (j = 1; vis [j] == 1; j ++);//Find the maximum value
        ma [cur] = j-1;
        search (cur + 1);
    }
}
int main ()
{
    // very complicated Backtracking. The most difficult part is, that you need to find an upper bound for the current denomination in the backtrack to investiate
    while (scanf ("% d% d", & h, & k), h && k)
    {
        // h:= # stamps
        // k := # denominations
        stamp [0] = 1;
        ma [0] = h;
        Max = 0;
        search (1);
        int i;
        for (i = 0; i <k; i ++) printf ("% 3d", ans [i]);
        printf ("->% 3d\n", Max);
    }
    return 0;
}

