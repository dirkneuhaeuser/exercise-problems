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
    // Transitive Closure connectivity check (Floyd-Warshall). If we can reach the same connector label we are unbound.
    // Note: 
    //    - the different labels are inportant, not the number of modecules
    //    - when there is a moducule with 4 labels, connect each of them with the opposite of the other three. Meaning: we could use this label to connect to the matching label of the other three.
    int n;cin >> n;
    int maxSigns = 26*2;
    vector<vector<bool>>AM(maxSigns, vector<bool>(maxSigns, false));
    FOR(i, n){
        string s; cin >> s;
        vector<int> idxes;
        FOR(j, 4){
            char a = s[j*2];
            char b = s[j*2 + 1];
            if(a == '0'){
                continue;
            }else{
                int let = a-'A';
                let*=2;
                if(b=='-'){
                    let++;
                }
                idxes.push_back(let);
            }
        }
        FOR(ii, idxes.size()){
            FOR(jj, idxes.size()){
                if(ii == jj) continue;
                AM[idxes[ii]][idxes[jj]^1] = true; // there is a possible edge from ii to the opposite of jj
            }
        }
    }
    FOR(k, maxSigns) FOR(i, maxSigns) FOR(j, maxSigns){
        AM[i][j] = AM[i][j] || (AM[i][k] && AM[k][j]);
    }
    bool unbounded = false;
    FOR(i, 26){
        if(AM[2*i+1][2*i+1] || AM[2*i][2*i]){
            unbounded = true;
            break;
        }
    }
    if(unbounded){
        cout << "unbounded" << endl;
    }else{
        cout << "bounded" << endl;
    }

}

