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
void solve() 
{
    // Advanced transitive closure problem (Floyd-Warshall). For is-A relation it is a basic transitive closure. For the has-A relation on the other hand, we carefully need to
    // construct the inital matrix, such that the algorithm can reconstruct the whole transitive relation.
    //
    // Therefore: we set all normal hasA, all detours over isA (isA->hasA), and also all hasA of these (isA -> hasA -> hasA) in the initial matrix.
    int m, q; cin >> m >> q;
    name2idx.clear();
    idx2name.clear();
    int maxNames = 500;
    vector<vector<bool>> isA(maxNames, vector<bool>(maxNames, false));
    vector<vector<bool>> hasA(maxNames, vector<bool>(maxNames, false));
    FOR(i, maxNames){
        isA[i][i] = true;
    }
    FOR(i, m){
        string a, b, c; cin >> a >> b >> c;
        int ai = getIdx(a);
        int bi = getIdx(c);
        if(b == "has-a"){
            hasA[ai][bi] = true;
        }else{
            isA[ai][bi] = true;
        }
    }

    int n = idx2name.size();
    FOR(k, n) FOR(i, n) FOR(j, n){ // O(n^3)
        isA[i][j] = isA[i][j] | (isA[i][k] & isA[k][j]);
    }
    // hasA relation is a bit more complicated, as you can incorporate as man isA until you go for hasA.
    // However, we can easily set up the first transtion in the hasA matrix. As these relations are transitive, the rest will be done by Floyd-Warshall. 
    //
    // Note: Order matters, here first go through all isA of current(i) and copy all hasA to the current. (isA-hasA);
    FOR(i, n){
        FOR(j, n){
            if(i==j) continue;
            if(isA[i][j]){
                for(int k=0; k<n; ++k){
                    if(hasA[j][k]){
                        hasA[i][k] = true;
                    }
                }
            }
        }
    }
    // Then you over all hasA of current(i) and copy it to the current. By doint it in this order, we assure that we also have all isA-hasA-hasA
    FOR(i, n){
        FOR(j, n){
            if(hasA[i][j]){
                for(int k=0; k<n; ++k){ // O(N^3)
                    if(isA[j][k]){
                        hasA[i][k] = true;
                    }
                }
            }
        }
    }

    FOR(k, n) FOR(i, n) FOR(j, n){ // O(n^3)
        hasA[i][j] = hasA[i][j] | (hasA[i][k] & hasA[k][j]);
    }
    FOR(k, q){
        cout << "Query " << k+1 <<": ";
        string a, b, c; cin >> a >> b >> c;
        int ai = getIdx(a);
        int bi = getIdx(c);
        
        if(ai >= n || bi >= n) continue;
        if(b == "is-a"){
            if(isA[ai][bi]){
                cout << "true";
            }else{
                cout << "false";
            }
        }else{
            if(hasA[ai][bi]){
                cout << "true";
            }else{
                cout << "false";
            }
        }
        cout << endl;
    }

}

