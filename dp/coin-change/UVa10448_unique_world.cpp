#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
// 2**6 =  64                           // 4!  = 24                       
// 2**8 =  256                          // 5!  = 120                      
// 2**10 = 1,024                        // 6!  = 720
// 2**15 = 32,768                       // 7!  = 5,040
// 2**20 = 1,048,576                    // 8!  = 40,320
// 2**25 = 33,554,432                   // 9!  = 362,880
// 2**30 = 1,073,741,824                // 10! = 3,628,800
// 2**32 = 4,294,967,296                // 12! = 479,001,600
                                        // 14! = 87,178,291,200
// int up to  2*10^9 (2^31-1)           // 16! = 20,922,789,888,000
// ll up to   9*10^18 (2^63 -1)         // 18! = 6,402,373,705,728,000
// ull up to 18*10^18 (2^64-1)/         // 20! = 2,432,902,008,176,640,000                                                                    
// ld up to  10*10^307
ll smod(ll a, ll m){return((a%m) +m) %m;}
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;
const int INF = 1<<30;

int memo2[50][50];
bool visited[50];

void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/output.txt", "w", stdout); 
    #endif 
    
    int t=1; 
    cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        memset(memo2, -1, sizeof memo2);
        memset(visited, 0, sizeof visited);
        solve(); 
        if(t!=0){
            cout<<"\n";    
        }
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

int dp2(int cur, int goal, vector<vector<pii>> &g){
    int &ans = memo2[cur][goal];
    if(ans != -1) return ans;
    ans = INF;
    if(cur == goal){
        ans=0;
        return ans;
    }
    visited[cur] = true;
    for(int i=0; i<g[cur].size(); ++i){
        int to = g[cur][i].first;
        if(visited[to]) continue;
        int price = g[cur][i].second;
        int v = dp2(to, goal, g);
        if(v != INF && ans > v + 1){
            ans = v + 1;
        }
    }
    visited[cur] = false;
    return ans;
}

void dfs(int cur, int goal, vector<vector<pii>> &g, vector<int> &involved){
    if(cur == goal){
        return;
    }
    int steps = dp2(cur, goal, g);
    for(int i=0; i<g[cur].size(); ++i){
        int to = g[cur][i].first;
        int p = g[cur][i].second;
        if(dp2(to, goal, g) == steps - 1){
            involved.push_back(p);
            dfs(to, goal, g, involved);
        }
    }
}


void solve() 
{
    // idea: get edges along the unique path. subtract for each of them, the cost from the quiery-cost, the last edge can only be used once, so discard it then.
    // The remaining edges, can be applied 2*x times, for x natural number.
    //
    // with this edge-weights -> coin change problem.
    // dp[i][j], after the ith edge, what is the minimum number of edges to get to a cost of j. We drop i here -> dp[j]
    // Note it is prohibitive, to have a for loop for each dp[i][j] to subtract all possible 2*x*current_edge_cust.
    // instead go from left to right and add alwyas one time only; as left to right will double count anyway!
    //
    // NOTE: this algo didn't get accepted :(, my test cases seem to work though, even higher ones. Maybe presentation errors?
    //
    int n, m; cin >> n >> m;
    vector<vector<pii>> g(n, vector<pii>());
    FOR(i, m){
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    int q; cin >> q;
    FOR(i, q){
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        if(a == b && c == 0){
            cout << "Yes 0" << endl;
            continue;
        }
        vector<int> inv;
        dfs(a, b, g, inv);
        if(inv.size() == 0){
            cout << "No" << endl;
            continue;
        }
        c -= inv.back();
        inv.pop_back();
        sort(inv.rbegin(), inv.rend());
        FOR(l, inv.size()){
            c-= inv[l];
        }
        int dp_steps[c+1];
        fill_n(&dp_steps[0], c+1, INF);
        dp_steps[0] = 0;
        int prev = -1;
        for(int i=0; i<inv.size(); ++i){
            int v = 2*inv[i];
            if(v == prev) continue;
            prev = v;
            for(int j = v; j<=c; ++j){
                dp_steps[j] = min(dp_steps[j], dp_steps[j - v] + 2);
            }
        }

        if(dp_steps[c] != INF){
            cout <<  "Yes " << dp_steps[c] + 1 + inv.size() << endl;
        }else{
            cout << "No" <<endl;

        }

    }


}

