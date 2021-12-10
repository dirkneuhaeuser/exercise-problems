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
void solve() 
{
    // Frequent check if a path from char a to char b exist -> Warshall's transitive closure
    int n, q; cin >> n >> q;
    vector<vector<bool>> AM(26, vector<bool>(26, false));
    FOR(i, n){
        char a, b; cin >> a >> b;
        int ai = a-'a';
        int bi = b-'a';
        AM[ai][bi] = true;
    }
    FOR(i, 26){
        AM[i][i] = true;
    }

    FOR(k, 26) FOR(i, 26) FOR(j, 26){
        AM[i][j] = AM[i][j] | (AM[i][k] & AM[k][j]);
    }
    FOR(k, q){
        string a, b; cin >> a >> b;
        if(a.size() != b.size()){
            cout << "no" << endl;
            continue;
        }
        bool poss = true;
        FOR(i, a.size()){
            int ai = a[i] - 'a';
            int bi = b[i] - 'a';
            if(!AM[ai][bi]){
                poss = false;
                break;
            }
        }
        if(!poss){
            cout << "no" << endl;
        }else{
            cout << "yes" << endl;
        }

    }

}

