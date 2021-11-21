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
vector<string> idx2name;
unordered_map<string, int> name2idx;
int getIdx(string name){
    if(name2idx.count(name) == 0){
        name2idx[name] = idx2name.size();
        idx2name.push_back(name);
    }
    return name2idx[name];
}
void solve() 
{
    // Finding shortest cycle usually involves getting the shortest distance from i to j and then back from j to i.
    // To get ASAP fast, we can use Floyd-Warshall.
    // Note, instead of going from i to j and back and then having trouble reconstructing the cycle right, we can simply get the cycle that starts in i ends in i.
    // So the smallest AM[i][i] is our start, and then we only need to recurse on cylce unit.
    int n; cin >> n;
    FOR(i, n){
        string name; cin >> name;
        getIdx(name);
    }
    vector<vector<ll>> AM(n, vector<ll>(n, INF));
    vector<vector<int>> par(n, vector<int>(n));
    vector<vector<int>> after(n, vector<int>(n));
    FOR(i, n){
        FOR(j, n){
            par[i][j] = i;
            after[i][j] = j;
        }
    }
    FOR(i, n){
        string name; cin >> name;
        int idxFile = getIdx(name);
        int imps; cin >> imps;
        string line; getline(cin, line);
        FOR(ii, imps){
            getline(cin, line);
            stringstream ss;
            ss << line;
            string offset;
            ss >> offset;
            string nextImport;
            while(ss >> nextImport ){
                if(nextImport.size() == 0) continue;
                if(nextImport.back() == ','){
                    nextImport = nextImport.substr(0, nextImport.size() - 1);
                }
                int idxImp = getIdx(nextImport);
                AM[idxFile][idxImp] = 1;
            }
        }
    }
    FOR(k, n) FOR(i, n) FOR(j, n){
        if(AM[i][j] > AM[i][k] + AM[k][j]){
            AM[i][j] = AM[i][k] + AM[k][j];
            par[i][j] = par[k][j]; // alwyas points to the penultimate element in the path
        }
    }
    int s = -1;
    ll cycleWeight = INF;
    FOR(i, n){
        if(AM[i][i] < cycleWeight){
            cycleWeight = AM[i][i];
            s = i;
        }
    }
    if(s==-1){
        cout << "SHIP IT";
        return;
    }
    int cur = s;
    vector<bool> seen(n, false);
    vector<string> path;
    while(true){
        if(seen[cur])break;
        path.push_back(idx2name[cur]);
        seen[cur] = true;
        cur = par[s][cur];
    }
    FOR(i, path.size()){
        cout << path[path.size()-1 - i];
        if(i < path.size()-1) cout << " ";
    }



}

