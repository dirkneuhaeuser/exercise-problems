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

void tarjan(int cur, vector<set<int>> &AL){
    dfs_num[cur] = dfs_low[cur] = dfs_idx++;
    dfs_stack.push_back(cur);
    visited[cur] = 1;
    for(int next: AL[cur]){
        if(dfs_num[next] == UNVISITED){
            tarjan(next, AL);
        }
        if(visited[next] == 1){
            dfs_low[cur] = min(dfs_low[next], dfs_low[cur]); // if it is not yet completed;
        }
    }
    if(dfs_low[cur] == dfs_num[cur]){
        // cur is start of a ssp;
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
    // find all SCC and format the answer
    int eq;
    bool first = true;
    while(cin >> eq && eq){
        if(!first)cout << endl;
        first = false;
        vector<set<int>> AL(26, set<int>());
        set<int> seen;
        FOR(i, eq){
            vector<int> ans;
            FOR(j, 5){
                char a; cin >> a;
                int aI = a - 'A';
                seen.insert(aI);
                ans.push_back(aI);
            }
            char better; cin >> better;
            int betterI = better -'A';
            seen.insert(betterI);
            FOR(j, 5){
                AL[betterI].insert(ans[j]);
            }
        }
        int n = 26;
        dfs_num.assign(n, UNVISITED);
        dfs_low.assign(n, UNVISITED);
        visited.assign(n, false);
        root.assign(n, UNVISITED);
        dfs_stack.clear();
        dfs_idx=0;
        FOR(i, n){
            if(dfs_num[i] == UNVISITED){
                tarjan(i, AL);
            }
        }
        vector<vector<int>> groups(26, vector<int>());
        FOR(i, n){
            if(seen.count(i)){
                // do sth
                groups[root[i]].push_back(i);
            }
        }
        vector<vector<int>> reduced;
        FOR(i, 26){
            if(groups[i].size()){
                sort(groups[i].begin(), groups[i].end());
                reduced.push_back(groups[i]);
                
            }
        }
        sort(reduced.begin(), reduced.end(), [](vector<int> &a, vector<int>&b){
                return a[0] <= b[0];
                });
        FOR(i, reduced.size()){
            FOR(j, reduced[i].size()){
                char let = reduced[i][j] + 'A';
                cout << let;
                if(j < reduced[i].size()-1) cout << " ";
            }
            cout << endl;
        }


    }


}

