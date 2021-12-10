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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
unordered_map<string, int> name2idx;
vector<string> idx2name;
int idx;
void addToNames(string name){
    if(name2idx.count(name) == 0){
        name2idx[name] = idx++;
        idx2name.push_back(name);
    }
}
void solve() 
{
    // Weihgted APSP (Floyd-Warshall) Problem with retrieval of solution. 
    int n, m; cin >> n >> m;
    idx2name.clear();
    name2idx.clear();
    idx = 0;
    vector<vector<pll>> AM(n, vector<pll>(m, {INF, 0}));
    FOR(j, m){
        string a, b; cin >> a >> b;
        int cost; cin >> cost;
        addToNames(a);
        addToNames(b);
        int aI = name2idx[a];
        int bI = name2idx[b];
        AM[aI][bI]={cost, 1};
        AM[bI][aI]={cost, 1};
    }
    vector<vector<int>> par(n, vector<int>(m));
    FOR(i, n){
        FOR(j, m){
            par[i][j] = i;
        }
    }
    for(int k=0; k<n; ++k){
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                pll potential = {AM[i][k].first + AM[k][j].first, AM[i][k].second + AM[k][j].second};
                if(potential < AM[i][j]){
                    AM[i][j] = potential;
                    // save the parent;
                    par[i][j] = par[k][j];
                }
            }
        }
    }
    int q; cin >> q;
    FOR(i, q){
        string a, b; cin >> a >> b;
        int aI = name2idx[a];
        int bI = name2idx[b];
        vector<string> ans;
        // Retrieve the solution:
        while(true){
            ans.push_back(idx2name[bI]);
            if(aI == bI){
                break;
            }
            bI = par[aI][bI];
        }
        FOR(j, ans.size()){
            cout << ans[ans.size()-1-j];
            if(j < ans.size() - 1) cout << " ";
        }
        cout << endl;
    }

}

