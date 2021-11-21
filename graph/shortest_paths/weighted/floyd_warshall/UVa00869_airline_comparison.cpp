#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
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
    
    int t=1; 
    cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
        if(t) cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
unordered_map<char, int> name2idx;
vector<char> idx2name;
int getIdx(char name){
    if(name2idx.count(name) == 0){
        name2idx[name] = idx2name.size();
        idx2name.push_back(name);
    }
    return name2idx[name];
}
void solve() 
{
    // Basic ASAP - transitive closure problem. For both graphs run boolean floyed-warshall to see if it is possible to go from i to j and compare both for differences.
    //
    // Note: The description of the problem is very bad: The description implies that edges are directed, as they talk about origin and destinations. 
    // In fact, the edges are bi-direcitonal. Also presentation-error likely (bad validator).
    int m;cin >> m;
    name2idx.clear();
    idx2name.clear();
    vector<pii> edges;
    FOR(j, m){
        char a, b; cin >> a >> b;
        int ai = getIdx(a);
        int bi = getIdx(b);
        edges.push_back({ai, bi});
    }
    int m2; cin >> m2;
    vector<pii> edges2;
    FOR(j, m2){
        char a, b; cin >> a >> b;
        int ai = getIdx(a);
        int bi = getIdx(b);
        edges2.push_back({ai, bi});
    }

    int n = idx2name.size();
    vector<vector<bool>> AM(n, vector<bool>(n, false));
    vector<vector<bool>> AM2(n, vector<bool>(n, false));
    for(auto [a, b]: edges){
        AM[b][a] = AM[a][b] = true;
    }
    for(auto [a, b]: edges2){
        AM2[b][a] = AM2[a][b] = true;
    }
    FOR(k, n) FOR(i, n) FOR(j, n){
        AM[i][j] = AM[i][j] | (AM[i][k] & AM[k][j]);
        AM2[i][j] = AM2[i][j] | (AM2[i][k] & AM2[k][j]);
    }
    bool equal = true;
    FOR(i, n) FOR(j, n){
        if(AM[i][j] != AM2[i][j]){
            equal = false;
            break;
        }
    }
    if(equal){
        cout << "YES";
    }else{
        cout << "NO";
    }
}

