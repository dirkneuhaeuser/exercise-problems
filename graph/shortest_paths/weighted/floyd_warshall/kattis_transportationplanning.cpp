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
ld euclid(int ax, int ay, int bx, int by){
    return powl(powl((ld)abs(ax-bx), 2)+powl((ld)abs(ay-by), 2),0.5);
}


void solve() 
{
    // APSP Problem. To get the commute time, we need the shortest path between all intersections -> Floyed-Warshall O(n^3).
    // Then we need O(n^2) to get the commute time.
    //
    // Now we can add 1 edge to make this commute time lower.
    // For each unused edge O(n^2) do:
    //  A new calculation of the commute time, but using the min of the old value AM[i][j] and using the new road: AM[i][a] + AM[b][j] + roadLength
    //  Note: check both dirctions of the road: AM[i][b] + AM[a][j] + roadLength
    //
    //  learning: When having the ASAP distance you can often work with and build upon these
    int n;
    while(cin>>n && n){
        vector<pii> coords;
        FOR(i, n){
            int a, b; cin >> a >> b;
            coords.push_back({a, b});
        }
        vector<vector<ld>> AM(n, vector<ld>(n, INF));
        vector<vector<bool>> usedEdges(n, vector<bool>(n, false));
        int m; cin >> m;
        FOR(i, m){
            int a, b; cin >> a >> b;
            usedEdges[a][b] = true;
            usedEdges[b][a] = true;
            auto [ax, ay] = coords[a];
            auto [bx, by] = coords[b];
            ld dis = euclid(ax, ay, bx, by);
            AM[a][b] = dis;
            AM[b][a] = dis;
        }
        FOR(i, n){
            AM[i][i] = 0;
        }
        FOR(k, n) FOR(i, n) FOR(j, n){
            AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
        }
        ld total=0;
        FOR(i, n){
            for(int j = i+1; j<n; ++j){
                total+=AM[i][j];
            }
        }
        ld newTotal = total;
        int a = -1, b=-1;
        FOR(i, n){
            for(int j =i+1;j<n;++j){
                if(usedEdges[i][j])continue;
                auto [ax, ay] = coords[i];
                auto [bx, by] = coords[j];
                ld dis = euclid(ax, ay, bx, by);
                ld newRedDis = 0;
                FOR(ii, n){
                    for(int jj=ii+1; jj<n; ++jj){
                        newRedDis += min(min(AM[ii][jj], AM[ii][i] + AM[j][jj] + dis), AM[ii][j] + AM[i][jj] + dis);
                    }
                }
                if(newRedDis + 0.000001< newTotal){
                    newTotal = newRedDis;
                    a = i;
                    b = j;
                }
            }
        }
        cout << setprecision(10) <<fixed;
        if(a == -1){
            cout << "no addition reduces " << total << endl;
        }else{
            cout << "adding " <<a << " " << b << " reduces " << total << " to " << newTotal << endl;

        }
    }

}

