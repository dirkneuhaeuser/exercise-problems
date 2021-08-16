#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
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
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*b,m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
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
    int r, g, b, y, s; cin >> r >> g >> b >> y >> s;
    int maxMoves = r + g + b  + y + s;
    // dp[i][r][g][b][y][s] is the probability that after the ith move we have r, g, b, y fruits still to harvest and the raven still s steps to go 
    vector<vector<vector<vector<vector<vector<ld>>>>>>dp(r+g+b+y+s+1, vector<vector<vector<vector<vector<ld>>>>>(r+2, vector<vector<vector<vector<ld>>>>(g+2,
                    vector<vector<vector<ld>>>(b+2, vector<vector<ld>>(y+2, vector<ld>(s+2, 0))))));

    // note, that here it is easier to use forward dp, as when basket is thrown it its easier to calculate it! 
    dp[0][r][g][b][y][s]=1;
    for(int i=0;i< maxMoves; ++i){
        for(int ri= r; ri>=0; --ri){
            for(int gi= g; gi>=0; --gi){
                for(int bi= b; bi>=0; --bi){
                    for(int yi= y; yi>=0; --yi){
                        for(int si= s; si>=0; --si){
                            int fruitsNonZeros = (int)(ri>0) + (int)(gi>0) + (int)(bi>0) + (int)(yi>0);
                            int ravenNonZeros =  (int)(si>0); 
                            int nonZeros = fruitsNonZeros + ravenNonZeros + 1;
                            if(fruitsNonZeros == 0 || ravenNonZeros == 0) continue; // if already end position, then we do not split this probability any further
                            // draw raven
                            if(si > 0)
                                dp[i+1][ri][gi][bi][yi][si-1] += (ld)1/(ld)nonZeros * dp[i][ri][gi][bi][yi][si];
                            // draw yellow
                            if(yi>0)
                                dp[i+1][ri][gi][bi][yi-1][si] += (ld)1/(ld)nonZeros * dp[i][ri][gi][bi][yi][si];
                            // draw blue
                            if(bi>0)
                                dp[i+1][ri][gi][bi-1][yi][si] += (ld)1/(ld)nonZeros * dp[i][ri][gi][bi][yi][si];
                            // draw green
                            if(gi>0)
                                dp[i+1][ri][gi-1][bi][yi][si] += (ld)1/(ld)nonZeros * dp[i][ri][gi][bi][yi][si];
                            // draw red
                            if(ri > 0)
                                dp[i+1][ri-1][gi][bi][yi][si] += (ld)1/(ld)nonZeros * dp[i][ri][gi][bi][yi][si];

                            // draw basket
                            vector<int> e {ri, gi, bi, yi};
                            int m = *max_element(e.begin(), e.end());
                            int cnt = 0;
                            for(int ii =0; ii<e.size(); ++ii){
                                if(e[ii]==m) cnt++;
                            }
                            if(ri == m ) dp[i+1][ri-1][gi][bi][yi][si] += (ld)1/(ld)nonZeros/cnt * dp[i][ri][gi][bi][yi][si];
                            if(gi == m ) dp[i+1][ri][gi-1][bi][yi][si] += (ld)1/(ld)nonZeros/cnt * dp[i][ri][gi][bi][yi][si];
                            if(bi == m ) dp[i+1][ri][gi][bi-1][yi][si] += (ld)1/(ld)nonZeros/cnt * dp[i][ri][gi][bi][yi][si];
                            if(yi == m ) dp[i+1][ri][gi][bi][yi-1][si] += (ld)1/(ld)nonZeros/cnt * dp[i][ri][gi][bi][yi][si];
                        }
                    }
                }
            }
        }
    }
    ld probAfterOne = 0;
    for(int ri= r; ri>=0; --ri){
        for(int gi= g; gi>=0; --gi){
            for(int bi= b; bi>=0; --bi){
                for(int yi= y; yi>=0; --yi){
                    for(int si= s; si>=0; --si){
                        probAfterOne += dp[1][ri][gi][bi][yi][si];
                    }
                }
            }
        }
    }
    
    ld win =0;
    ld lose =0;
    for(int i=0; i<maxMoves+1; ++i){
        for(int k=1; k<s+1; ++k){
            win += dp[i][0][0][0][0][k];
        }
    }
    cout << setprecision(8);
    cout << fixed << win << endl;

}

