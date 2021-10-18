#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long, long> pll;
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
vector<int> colors;

int dfs_color(int cur, int col1, int col2, vector<vector<int>> &AL, bool &poss){
    colors[cur] = col1;
    int ret;
    if(col1 < col2){
        ret = 0;
    }else{
        ret = 1;
    }
    for(int next: AL[cur]){
        if(colors[next] == -1){
            ret += dfs_color(next, col2, col1, AL, poss);
        }else if(colors[next] == col1-10 || colors[next] == col1){
            poss = false;
        }
    }
    return ret;
}
 void resetOver10(int cur, vector<vector<int>> &AL){
     colors[cur] = -1;
     for(int next: AL[cur]){
         if(colors[next]>=10){
             resetOver10(next, AL);
         }
     }
 }


void solve() 
{
    // bi-coloring problem: first do all certain vertexes (no airport at either edge or both has to be airports)
    // for the remaining connected components: normalal bicoloring
    int n, m; cin >> n >> m;
    colors.assign(n, -1);
    bool possible = true;
    vector<vector<int>> AL(n, vector<int>());
    vector<pii> EL;
    int ret = 0;
    FOR(i, m){
        int a, b, type; cin >> a >> b >> type;
        a--; b--;
        if(type == 0){
            if(colors[a] == 1 || colors[b] == 1 ){
                possible = false;
            }
            colors[a] = 0;
            colors[b] = 0;
        }else if(type == 2){
            if(colors[a] == 0 || colors[b] == 0 ){
                possible = false;
            }
            if(colors[a] == -1) ret++;
            if(colors[b] == -1) ret++;
            colors[a] = 1;
            colors[b] = 1;
        }else{
            EL.push_back({a, b});

        }
    }
    // some cycle edge-cases -> need to check the type 1 at last
    for(auto [a, b]:EL){
        if(colors[a] == 0 && colors[b] == 0 ){
            possible = false;
        }
        if(colors[a] == 1 && colors[b] == 1 ){
            possible = false;
        }
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    if(!possible){
        cout << "impossible" << endl;
        return;
    }

    // now each connected component which is left needs to be bicolored
    // There are two possibilites: start with 0 or 1.
    // Therefore: check both if possible(bc of sourrounding) and take the one with fewest airpot occurence (color 11 here)
    FOR(i, n){
        if(colors[i] == -1){
            //cout << i << endl;
            // first possibility
            int ans = INF;
            bool poss = true;
            int ans1 = dfs_color(i, 10, 11, AL, poss);
            if(poss) ans = ans1;

            // second possibility
            resetOver10(i, AL);
            poss = true;
            int ans2 = dfs_color(i, 11, 10, AL, poss);
            if(poss) ans = min(ans, ans2);

            if(ans == INF){
                cout << "impossible" << endl;
                return;
            }else{
                ret += ans;
            }
        }
    }
    cout << ret;

    

}

