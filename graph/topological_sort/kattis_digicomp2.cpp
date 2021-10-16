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


void topSort(queue<int> &q, vector<char> &ret, vector<ll> &ballsAtSwitch, vector<int> &inDegree, vector<vector<int>> &AL){
    while(q.size()){
        int cur = q.front(); q.pop();
        ll halfBig = ballsAtSwitch[cur] >> 1;
        ll halfSmall = halfBig;
        if(ballsAtSwitch[cur]&1) halfBig++;
        int l = AL[cur][0];
        int r = AL[cur][1];
        if(ret[cur] == 'L'){
            if(l != -1) ballsAtSwitch[l]+=halfBig;
            if(r != -1) ballsAtSwitch[r]+=halfSmall;
        }else{
            if(l != -1) ballsAtSwitch[l]+=halfSmall;
            if(r != -1) ballsAtSwitch[r]+=halfBig;
        }
        if(l!=-1){
            inDegree[l]--;
            if(inDegree[l] == 0){
                q.push(l);
            }
        }
        if(r!=-1){
            inDegree[r]--;
            if(inDegree[r] == 0){
                q.push(r);
            }
        }
        if(ballsAtSwitch[cur]&1){
            ret[cur] = ret[cur] ^ 'R' ^ 'L'; // flipps the current selection;
        }
        
    }
}

void solve() 
{
    // Actually just a dfs problem, but in order to decrease computation, we only want to compute a vertex when its indegree==0.
    // Therefore we use the topological order within the Kahns algorithm.
    ll balls, n; cin >> balls >> n;
    vector<vector<int>> AL(n, vector<int>());
    vector<char> ret(n, '.');
    vector<int> inDegree(n, 0);
    FOR(i, n){
        cin >> ret[i];
        int a, b; cin >> a >> b;
        a--; b--;
        AL[i].push_back(a);
        AL[i].push_back(b);
        if(a != -1){
            inDegree[a]++;
        }
        if(b != -1){
            inDegree[b]++;
        }
    }
    vector<ll>ballsAtSwitch(n, 0);
    queue<int> q;
    for(int i=1; i<n; ++i){
        if(inDegree[i] == 0) q.push(i);
    }
    topSort(q, ret, ballsAtSwitch, inDegree, AL);
    q.push(0);
    ballsAtSwitch[0] = balls;
    topSort(q, ret, ballsAtSwitch, inDegree, AL);
    

    FOR(i, n){
        cout << ret[i];
    }


}

