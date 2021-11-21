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
int getIdx(string name){
    if(name2idx.count(name) == 0){
        name2idx[name] = idx2name.size();
        idx2name.push_back(name);
    }
    return name2idx[name];
}
bool equal (ld a, ld b){
    return abs(a - b) < 0.0001;
}
void solve() 
{
    // APSP Problem. If you can find a path from one currency to itself such that that you have to pay less than 1 to get 1 unit of it, you have arbitrage.
    // Note, here we work with multiplication instead of addition...
    int n; 
    while(cin >> n && n){
        name2idx.clear();
        idx2name.clear();
        FOR(i, n){
            string name;
            cin >> name;
            getIdx(name);
        }
        vector<vector<ld>> AM(n, vector<ld>(n, INF));
        int exchanges; cin >> exchanges;
        FOR(i, exchanges){
            string a, b; cin >> a >> b;
            int ai = getIdx(a);
            int bi = getIdx(b);
            int left; cin >> left;
            char mid; cin >> mid;
            int right; cin >> right;
            ld rate = (ld)left/right; // how much you give for one unit of the other. (Not the other way round, since we minimise here)
            AM[ai][bi] = rate;
        }
        vector<vector<ld>> copy = AM;
        FOR(k, n) FOR(i, n) FOR(j, n){
            AM[i][j] = min(AM[i][j], AM[i][k] * AM[k][j]);
        }
        bool arbitrage = false;
        FOR(i, n){
            if(AM[i][i] < 1){
                arbitrage = true;
            }
        }
        if(arbitrage){
            cout << "Arbitrage" << endl;
        }else{
            cout << "Ok" << endl;
        }
    }


}

