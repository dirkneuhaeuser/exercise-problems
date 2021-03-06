#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int> tiii;
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
void solve() 
{
    // Going simultanously in both graphs saving the sate for both simultanously. Each time we end at the dormitory at the first graph,
    // we also have to be in the dormitory in the second graph
    int n; cin >> n;
    vector<vector<int>> doors1, doors2;
    for(int i= 0; i< n; ++i){
        vector<int> next(4);
        FOR(j, 4) cin >> next[j];
        doors1.push_back(next);
    }
    for(int i= 0; i< n; ++i){
        vector<int> next(4);
        FOR(j, 4) cin >> next[j];
        doors2.push_back(next);
    }
    

    set<pair<int, int>> seen;
    queue<pii> q;
    q.push({1, 1});
    seen.insert({1, 1});
    bool doesAnyInstructionWork = true;
    bool isPossible = false;

    while(q.size()){
        auto [room1, room2] = q.front(); q.pop();
        if(room1 == n) isPossible = true;
        if(room1 == n && room2 != n) doesAnyInstructionWork = false;
        for(int i=0;i<4;++i){
            if(doors1[room1-1][i] == 0) continue;
            pii next;
            if(room2 == -1 || doors2[room2-1][i] == 0 ){
                next = {doors1[room1-1][i], -1};
            }else{
                next = {doors1[room1-1][i], doors2[room2-1][i]};
            }
            if(seen.count(next) == 0){
                q.push(next);
                seen.insert(next);
            }
        }
    }
    if(!isPossible){
        cout <<"Impossible";
        return;
    }
    if(doesAnyInstructionWork){
        cout << "Yes";
    }else{
        cout << "No";
    }


}

