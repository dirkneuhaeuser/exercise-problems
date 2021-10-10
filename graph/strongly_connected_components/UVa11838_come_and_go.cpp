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

enum {UNVISITED=-1, VISITED=-2};
vector<set<int>> al;
vector<int> visited;
vector<set<int>> alReversed;
void dfsPost(int cur, vector<int> &postOrder, bool rev){
    visited[cur] = VISITED;
    vector<set<int>> &adjList = (rev?alReversed:al);
    for(int next: adjList[cur]){
        if(visited[next] == UNVISITED){
            dfsPost(next, postOrder, rev);
        }
    }
    if(!rev){
        postOrder.push_back(cur);
    }

}


void solve() 
{
    // Count Strongly Connected Components. Idea of Kosarajus: Do a postOrder 'topological sort'.
    // Reverse the Graph and go through this order in reversed. 
    int n, m; 
    while(cin >> n >> m){
        if(n==0 && m == 0) break;
        al.assign(n, set<int>());
        alReversed.assign(n, set<int>());
        FOR(i, m){
            int a, b, c; cin >> a >> b >> c;
            a--; b--;
            al[a].insert(b);
            alReversed[b].insert(a);
            if(c==2){
                al[b].insert(a);
                alReversed[a].insert(b);
            }
        }
        visited.assign(n, UNVISITED);
        vector<int> postOrder;
        FOR(i, n){
            if(visited[i] == UNVISITED){
                dfsPost(i, postOrder, false);
            }
        }
        int scc = 0;
        visited.assign(n, UNVISITED);
        for(int i=n-1; i>=0; --i){
            if(visited[postOrder[i]] == UNVISITED){
                dfsPost(postOrder[i], postOrder, true);
                scc++;
            }
        }
        if(scc <= 1){
            cout << 1 << endl;
        }else{
            cout << 0 << endl;
        }
        
    }
}

