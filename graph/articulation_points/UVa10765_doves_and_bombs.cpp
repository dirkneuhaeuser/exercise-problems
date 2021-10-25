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

enum {VISITED=-3, UNVISITED=-1};
vector<int> dfs_num, dfs_low, parent, artNum;
vector<bool> isArticulation;
int dfs_idx;
int root_children;
int root;

vector<int> colors;

void dfsColor(int idx, int color, int pt, vector<vector<int>> &AL){
    colors[idx] = color;
    for(int next: AL[idx]){
        if(next == pt || colors[next] != -1)  continue;
        dfsColor(next, color, pt, AL);
    }
}

void dfs(int idx, vector<vector<int>> &AL){
    dfs_num[idx] = dfs_low[idx] = dfs_idx++;
    for(int next: AL[idx]){
        if(dfs_num[next] == UNVISITED){
            parent[next] = idx;
            if(idx == root) root_children++;
            dfs(next, AL);
            // question: difference in dfs_low => both nodes are articulation points?
            // next doesnt have to be articulation, bc it might be just one ndoe
            if(dfs_num[idx] <= dfs_low[next]){
                // only check newly vistied nodes (old ones are covered in other connected components)
                isArticulation[idx] = true; 
                artNum[idx]++;
            }
            dfs_low[idx] = min(dfs_low[idx], dfs_low[next]);
        }else{
            if(parent[idx] != next){
                dfs_low[idx] = min(dfs_low[idx], dfs_num[next]);
            }
        }
    }
        

}



void solve() 
{
    int n, targets; 
    // Articulation points problem with counting at each articulation points the number of different connected components if the current vertex would be removed
    while(cin >> n >> targets && n != 0 && targets != 0){
        vector<vector<int>> AL(n, vector<int>());
        while(true){
            int a, b; cin >> a >> b;
            if(a == -1 && b == -1) break;
            AL[a].push_back(b);
            AL[b].push_back(a);
        }
        dfs_num.assign(n, UNVISITED);
        dfs_low.assign(n, UNVISITED);
        root = 0;
        root_children = 0;
        parent.assign(n, -1);
        isArticulation.assign(n, false);
        artNum.assign(n, 1);
        dfs_idx = 0;
        dfs(0, AL);
        isArticulation[0] = root_children>1;
        artNum[0] = root_children;
        vector<pii> ret;
        FOR(i, n){
            ret.push_back({artNum[i], i});
        }
        sort(ret.begin(), ret.end(), [](pii &a, pii &b){
                if(a.first < b.first) return true;
                if(a.first > b.first) return false;
                if(a.second < b.second) return false;
                if(a.second > b.second) return true;
                return true;
                });
        FOR(i, targets){
            cout << ret[n-1-i].second << " " << ret[n-1-i].first;
            cout << endl;
        }
        cout << endl;

    }

}

