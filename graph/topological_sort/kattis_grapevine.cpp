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
void solve() 
{
    // Topological sort, but instead of in-degree, use the Skepticism.
    int n, m, d; cin >> n >> m >> d;
    d--;
    unordered_map<string, int> name2idx;
    vector<int> skepts(n, 0);
    FOR(i, n){
        string name; cin >> name;
        name2idx[name] = i;

        cin >> skepts[i];
    }
    vector<unordered_set<int>> AL(n, unordered_set<int>());
    FOR(j, m){
        string a, b; cin >> a >> b;
        int ai = name2idx[a];
        int bi = name2idx[b];
        AL[ai].insert(bi);
        AL[bi].insert(ai);
    }

    string start; cin>> start;
    int startIdx = name2idx[start];

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, startIdx});
    int ret = 0;
    unordered_set<int> heard{startIdx};
    while(pq.size()){
        auto [day, name] = pq.top(); pq.pop();
        if(day > d) break; // Person knows about it and can talk about it
        for(int next: AL[name]){
            if(heard.count(next) == 0) ret++;
            heard.insert(next);
            skepts[next]--;
            if(skepts[next] == 0){
                pq.push({day+1, next});
            }
        }
    }
    cout << ret;

    


}

