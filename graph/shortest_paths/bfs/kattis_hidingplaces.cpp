#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
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

    int t; cin >> t;
    while(t--){
        solve();
        cout << endl;
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    // Basic unweighted SSMDSP
    char a; cin >> a;
    int aI = a - 'a';
    int aJ; cin >> aJ; aJ--;
    int n=8, m=8;

    vector<vector<int>> dis(8, vector<int>(8, INF));
    dis[aI][aJ] = 0;
    queue<pii> q;
    q.push({aI, aJ});
    vector<pii> dir{{-2, 1}, {-2,-1}, {2, -1}, {2, 1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    while(q.size()){
        auto [i, j] = q.front(); q.pop();
        for(auto [di, dj]: dir){
            int nextI = (int)i+di;
            int nextJ = (int)j+dj;
            if(nextI<0|| nextJ <0|| nextI >=n || nextJ >= m) continue;
            if(dis[nextI][nextJ] < INF) continue;
            dis[nextI][nextJ] = 1 + dis[i][j];
            q.push({nextI, nextJ});
        }
    }
    int maxE = -1;
    vector<pii> ans;
    for(int j=7; j>=0; --j){
        FOR(i, n){
            if(dis[i][j] > maxE){
                maxE = dis[i][j];
                ans.clear();
                ans.push_back({i, j});
            }else if(dis[i][j] == maxE){
                ans.push_back({i, j});
            }
            
        }
    }
    cout << maxE;
    FOR(i, ans.size()){
        char t = ans[i].first + 'a';
        cout <<" "  << t << ans[i].second+1;
    }

}


