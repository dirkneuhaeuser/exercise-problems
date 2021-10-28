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


vector<bool> seen;

void dfs(int cur, vector<vector<int>> &AL, vector<vector<int>> &revDfsTree){
    seen[cur] = true;
    for(int next: AL[cur]){
        if(seen[next] == false){
            revDfsTree[next].push_back(cur);
            dfs(next, AL, revDfsTree);
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
    // very interesting dfs problem. Bruteforce O(n^n) obviously does not work. However, when you can traverse via a dfs from the root (Henk) to any other node, 
    // then its possible to make Henk a winner:
    // In the dfs-spanntree, inverse the edgres and go backwards from the leaves to the root within a bfs, where the next node will be added if indegree[node] = 0.
    // It doesnt matter who will win a specific match, as long as Henk is the last element and will win against the second last node.
    int n; cin >> n;
    vector<vector<int>> AL(n, vector<int>()), ALDfsRev(n, vector<int>());
    string line;
    FOR(i, n){
        cin >> line;
        FOR(j, n){
            if(line[j] == '1'){
                AL[i].push_back(j);
            }
        }
    }
    seen.assign(n, false);

    dfs(0, AL, ALDfsRev);
    int cnt = 0;
    FOR(i, n) if(seen[i]) cnt++;
    if(cnt == n){
        vector<int> inDegree(n, 0);
        FOR(i, n){
            FOR(j, ALDfsRev[i].size()){
                inDegree[ALDfsRev[i][j]]++;
            }
        }
        queue<int> q;
        FOR(i, n){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        while(q.size()){
            int t = q.front(); q.pop();
            for(int next: ALDfsRev[t]){
                inDegree[next]--;
                if(inDegree[next] == 0){
                    q.push(next);
                }
            }
            cout << t;
            if(q.size()) cout << " ";
        }
        cout << " ";
    }else{
        cout << "impossible" << endl;
    }


}

