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
void rotate(int x, int y, int &xNew, int &yNew, int dx, int dy){
    xNew = dy+x-y; // dy alreay incorprates the offset
    yNew = x+y + 1; // offset for the frame
}
void solve() 
{

    // intuition: Complicated diagonal 2D-prefixsum. To test each field would timeout, as naive comes with O((dx*dy)^2), Note the window in WC is bigger than dx or dy.
    // Better Idea: For each cell, we need to test a certain cube. These cubes are very much overlapping.
    //              However, the diagonal nature of these cubes make it difficult to precalculate sums.
    //              Therefore, rotate each cell by 45 degees, such that you have normal rectangles.
    //              Now you can calculate a 2D Prefixsum, which is NOT kadane.
    //              In kadane we would only prefixsum over each row and then 'kadende' over all possible l and r column combination
    //              Here, however, we do not need to look at windows of variable size.
    //              The window-size is fixed, so each cell we get in O(1) with 2D Prefixsum, leading to overall O(dx*dy)
    int dx, dy, n, q; 
    int count = 1;
    while(cin >> dx >> dy >> n >> q){
        if(dx == 0) break;
        cout << "Case " << count++ << ":" << endl;
        int prefixSum2D[dx+dy][dx+dy];
        memset(prefixSum2D, 0, sizeof prefixSum2D);
        FOR(i, n){
            int x,y; cin >> x >> y;
            x--; y--;
            int tx, ty;
            rotate(x,y, tx, ty, dx, dy);
            prefixSum2D[ty][tx]++;
        }

        for(int i=1; i<dx+dy; ++i){
            int rowSum = 0;
            for(int j=1; j<dx+dy; ++j){
                rowSum += prefixSum2D[i][j];
                prefixSum2D[i][j] = prefixSum2D[i-1][j] + rowSum;
            }
        }
        FOR(k, q){
            int window; cin >> window;
            int maxE = 0;
            pii ret = {0, 0};
            for(int y = 0; y<dy; ++y){
                for(int x = 0; x<dx; ++x){
                    int tx, ty;
                    rotate(x, y, tx, ty, dx, dy);
                    int l = max(1, tx-window);
                    int r = min(dx+dy-1, tx+window);
                    int t = max(1, ty-window);
                    int b = min(dx+dy-1, ty+window);
                    int sumWindow = prefixSum2D[b][r] - prefixSum2D[b][l-1] - prefixSum2D[t-1][r] + prefixSum2D[t-1][l-1]; // inclusion-exclusion
                    if(sumWindow > maxE){
                        maxE = sumWindow;
                        ret = {x, y};
                    }
                }
            }
            cout << maxE << " (" << ret.first+1 << "," << ret.second+1 << ")"<< endl;
        }
    }

}

