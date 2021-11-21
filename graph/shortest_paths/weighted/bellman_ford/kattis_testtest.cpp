#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
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
int cost[101];
int best[101];
int last[101];
char adj[101][101];

int z,i,j,k,m,n,e,progress;
void solve(){
   while ((1 == scanf("%d",&n)) && n != -1){
      memset(adj,0,sizeof(adj));
      memset(last,0,sizeof(last));
      for (i=1;i<=n;i++) best[i] = 0x3fffffff;
      for (i=1;i<=n;i++) {
         scanf("%d%d",&e,&m);
         cost[i] = -e;
         for (j=0;j<m;j++) {
            scanf("%d",&k);
            adj[i][k] = 1;
         }
      }
      best[1] = -100;
      for (z=0;;z++) {
         progress = 0;
         for (i=1;i<=n;i++) for (j=1;j<=n;j++) {
            if (adj[i][j] &&
                best[i] < 0 && best[i] + cost[j] < 0 &&
                best[i] + cost[j] < best[j]){
                   best[j] = best[i] + cost[j];
                   progress = 1;
                   last[j] = z;
            }
         }
         if (!progress || best[n] < 0) break;
         if (z == n) {
            for (i=1;i<=n;i++) if (last[i] != z) best[i] = 0x3fffffff;
            for (i=1;i<=n;i++) cost[i] = 0;
         }
      }
      if (best[n] < 0 /*|| z == n*/) printf("winnable\n");
      else printf("hopeless\n");
   }
   if (n != -1) printf("missing end delimiter\n");
}
