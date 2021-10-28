#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
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

vector<ld> blood;
void dfs(int cur, vector<vector<int>> &AL, vector<int> &indegree){
    indegree[cur] = -1;
    for(int next: AL[cur]){
        indegree[next]--;
        blood[next] += blood[cur]/2;
        if(indegree[next] == 0){
            dfs(next, AL, indegree);
        }
    }
}



void solve() 
{
    // basic dfs
    int m, n; cin >> m >> n;
    vector<vector<int>> AL(1, vector<int>());
    unordered_map<string, int> name2idx;
    vector<string> idx2name;
    string king; cin >> king;
    int idx = 0;
    name2idx[king] = idx++;
    idx2name.push_back(king);
    vector<int> inDegree{0};

    FOR(i, m){
        string a, b, c; cin >> a >> b >> c;
        if(name2idx.count(a)==0){
            name2idx[a] = idx++;
            idx2name.push_back(a);
            inDegree.push_back(0);
            AL.push_back({});
        }
        if(name2idx.count(b)==0){
            name2idx[b] = idx++;
            idx2name.push_back(b);
            inDegree.push_back(0);
            AL.push_back({});
        }
        if(name2idx.count(c)==0){
            name2idx[c] = idx++;
            idx2name.push_back(c);
            inDegree.push_back(0);
            AL.push_back({});
        }
        int ai = name2idx[a];
        int bi = name2idx[b];
        int ci = name2idx[c];
        AL[bi].push_back(ai);
        AL[ci].push_back(ai);
        inDegree[ai] = 2;
    }
    vector<int> query;
    FOR(i, n){
        string q; cin >> q;
        if(name2idx.count(q)==0){
            name2idx[q] = idx++;
            idx2name.push_back(q);
            inDegree.push_back(0);
            AL.push_back({});
        }
        query.push_back(name2idx[q]);
    }
    int totalPersons = AL.size();
    blood.assign(totalPersons, 0);
    blood[0] = 1;
    FOR(i, totalPersons){
        // inorder to stop double counting here, set indegree ton -1 when actually using the current i;
        if(inDegree[i] == 0){
            dfs(i, AL, inDegree);
        }
    }
    int maxI = -1;
    ld maxBlood = -1;
    FOR(i, query.size()){
        if(blood[query[i]] > maxBlood){
            maxBlood = blood[query[i]];
            maxI = i;
        }
    }
    cout << idx2name[query[maxI]];


}

