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

enum{UNVISITED=-1};
vector<int> dfs_num, dfs_low, dfs_stack, visited, root;
int dfs_idx;
int groups;

void tarjan(int cur, vector<vector<bool>> &AM){
    dfs_num[cur] = dfs_low[cur] = dfs_idx++;
    dfs_stack.push_back(cur);
    visited[cur] = 1;
    for(int next=0; next<AM[cur].size(); ++next){
        if(AM[cur][next] == false) continue;
        if(dfs_num[next] == UNVISITED){
            tarjan(next, AM);
        }
        if(visited[next] == 1){
            dfs_low[cur] = min(dfs_low[next], dfs_low[cur]); // if it is not yet completed;
        }
    }
    if(dfs_low[cur] == dfs_num[cur]){
        // cur is start of a ssp;
        groups++;
        while(true){
            int last = dfs_stack.back(); dfs_stack.pop_back();
            root[last] = cur;
            visited[last] = 0;
            if(last == cur) break;
        }
    }

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
    // Check if graph is SCC. If not, brute-force all edges and flip them and for each check again, if graph is SCC.
    // To do so, it might be easier with an AM instead of an AL
    int n, m;
    int cnt = 1;
    while(cin >> n >> m){
        cout << "Case " << cnt++ << ": ";
        vector<pii> EL;
        vector<vector<bool>> AM(n, vector<bool>(n, false));
        FOR(i, m){
            int a, b; cin >> a >> b;
            AM[a][b]= true;
            EL.push_back({a, b});
        }
        dfs_num.assign(n, UNVISITED);
        dfs_low.assign(n, UNVISITED);
        visited.assign(n, false);
        root.assign(n, UNVISITED);
        dfs_stack.clear();
        dfs_idx=0;
        groups = 0;
        FOR(i, n){
            if(dfs_num[i] == UNVISITED){
                tarjan(i, AM);
            }
        }
        if(groups == 1){
            cout << "valid" << endl;
            continue;
        }
        bool found = false;
        for(auto [a, b]: EL){
            // flipping edge
            AM[a][b] = false;
            AM[b][a] = true;
            dfs_num.assign(n, UNVISITED);
            dfs_low.assign(n, UNVISITED);
            visited.assign(n, false);
            root.assign(n, UNVISITED);
            dfs_stack.clear();
            dfs_idx=0;
            groups = 0;
            FOR(i, n){
                if(dfs_num[i] == UNVISITED){
                    tarjan(i, AM);
                }
            }
            if(groups == 1){
                cout << a << " " << b << endl;
                found = true;
                break;
            }
            AM[a][b] = true;
            AM[b][a] = false;
        }
        if(!found){
            cout << "invalid" << endl;
        }
    }
}

