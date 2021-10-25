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

void dfs(int cur, int root, int col, vector<vector<int>> &AL){
    colors[cur] = col;
    for(int next: AL[cur]){
        if(cur == root){
            if(colors[next] == -1){
                dfs(next, root, col, AL);
            }
            col++;
        }else{
            if(colors[next] == -1){
                dfs(next, root, col, AL);
            }
        }
    }
}


void solve() 
{
    // very complicated articulation problem. This programme doesnt wotk. Ideas: within a certain branch there is optimisation
    int n, h;cin >> n >> h;
    vector<int> inDegree(n, 0);
    vector<vector<int>> AL(n, vector<int>());
    FOR(i, n-1){
        int a, b; cin >> a >> b;
        AL[a].push_back(b);
        AL[b].push_back(a);
        inDegree[a]++;
        inDegree[b]++;
    }

    colors.assign(n, -1);
    dfs(h, h, 0, AL);


    map<int, vector<int>> colToInsec;

    for(int i=0; i<n; ++i){
        if(inDegree[i] == 1){
            if(i == h) continue;
            colToInsec[colors[i]].push_back(i);
        }
    }
    vector<pii> ret;
    priority_queue<pii> pq;
    for(auto [k, v]: colToInsec){
        pq.push({v.size(), k});
    }
    while(pq.size() > 1){
        auto [times, color] = pq.top(); pq.pop();
        auto [times2, color2] = pq.top(); pq.pop();
        if(times2 == 0){
            FOR(i, times){
                int l = colToInsec[color].back();
                colToInsec[color].pop_back();
                ret.push_back({h, l});
            }
            break;
        }
        if(pq.size()){
            auto [times3, color3] = pq.top();
            int diff = times2 - times3;
            if(diff > 0){
                FOR(i, diff){
                    int l = colToInsec[color].back();
                    int r = colToInsec[color2].back();
                    colToInsec[color].pop_back();
                    colToInsec[color2].pop_back();
                    ret.push_back({l, r});
                }
                if(times-diff > 0) pq.push({times-diff, color});
                if(times2-diff > 0) pq.push({times2-diff, color2});
                continue;
            }
        }
        times--;
        times2--;
        int l = colToInsec[color].back();
        int r = colToInsec[color2].back();
        colToInsec[color].pop_back();
        colToInsec[color2].pop_back();
        ret.push_back({l, r});
        if(times > 0) pq.push({times, color});
        if(times2 > 0) pq.push({times2, color2});
    }
    if(pq.size()){
        auto [times, color] = pq.top(); pq.pop();
        FOR(i, times){
            int l = colToInsec[color].back();
            colToInsec[color].pop_back();
            ret.push_back({h, l});
        }
    }
    cout << ret.size() << endl;
    FOR(i, ret.size()){
        cout << ret[i].first << " " << ret[i].second << endl;
    }



}

