#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
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
vector<bool> isGap;
bool visited[301][301][301];
int total;
int have1, have2, have3;

bool dfs(int c1, int c2, int c3){
    visited[c1][c2][c3] = true;
    int got = c1+2*c2+3*c3;
    if(got == total) return true;
    if(got > total) return false;
    if(isGap[got]) return false;
    if(c1 < have1 && visited[c1+1][c2][c3] == 0 && dfs(c1+1, c2, c3)) return true;
    if(c2 < have2 && visited[c1][c2+1][c3] == 0 && dfs(c1, c2+1, c3)) return true;
    if(c3 < have3 && visited[c1][c2][c3+1] == 0 && dfs(c1, c2, c3+1)) return true;
    return false;
}



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
    // there are in total 300^3 = 27KK states. -> dp/dfs is sufficient
    int n;cin >> n >> have1 >> have2 >> have3;
    vector<int> nums;
    total = 0;
    FOR(i, n){
        int num; cin >> num;
        total += num;
        nums.push_back(num);
    }
    isGap.assign(total+1, false);
    int cur = 0;
    for(int i=0; i<n-1; ++i){
        cur += nums[i];
        isGap[cur] = true;
    }
    memset(visited, 0, sizeof visited);
    bool ans = dfs(0, 0, 0);
    if(ans){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }

}

