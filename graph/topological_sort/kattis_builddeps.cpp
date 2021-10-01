#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                          // ld up to  10*10^307
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

vector<string> tokenize2(string s, string del = " "){
    int current, next = -1;
    vector<string> separatedWords;
    string delimiters = ", ";
    do
    {
        current = next + 1;
        next = s.find_first_of( delimiters, current );
        string token =  s.substr( current, next - current );
        if(token != ""){
            separatedWords.push_back(token);
        }
    }while (next != string::npos);
    return separatedWords;
}

enum {VISITED=-1, UNVISITED=-2};

// get topological order with a dfs
void dfs(int cur, vector<int> &v, vector<vector<int>> &al, vector<int> &result){
    v[cur]=VISITED;
    for(int next: al[cur]){
        if(v[next] == UNVISITED){
            dfs(next, v, al, result);
        }
    }
    result.push_back(cur);
}


void solve() 
{
    // Topological sort. Convert strings to indicies. Also here we need to take a look at the reversed dependency graph ('is part of' rather than 'depends on')
    int n; cin >> n;
    int idx = 0;
    unordered_map<string, int> file2Idx;
    vector<string> idx2File;
    string line; getline(cin, line);

    vector<vector<int>> al(n, vector<int>());
    FOR(i, n){
        getline(cin, line);
        vector<string> words = tokenize2(line);
        string base = words[0].substr(0, words[0].size()-1);
        int idxBase;
        if(file2Idx.count(base)){
            idxBase = file2Idx[base];
        }else{
            idxBase = file2Idx[base] = idx++;
            idx2File.push_back(base);
        }
        for(int i=1; i<words.size(); ++i){
            string word = words[i];
            int idxThis;
            if(file2Idx.count(word)){
                idxThis = file2Idx[word];
            }else{
                idxThis = file2Idx[word] = idx++;
                idx2File.push_back(word);
            }
            // important: we need here the reveresed dependency graph (is part of)
            al[idxThis].push_back(idxBase);
        }
    }
    string change; cin >> change;
    int idxChange;
    if(file2Idx.count(change)){
        idxChange = file2Idx[change];
    }else{
        idxChange = file2Idx[change] = idx++;
        idx2File.push_back(change);
    }
    int programms = file2Idx.size();
    vector<int> v(programms, UNVISITED);
    vector<int> ret;
    dfs(idxChange, v, al, ret);
    for(int i=ret.size()-1;i >=0; --i){
        cout << idx2File[ret[i]];
        if(i > 0) cout << endl;
    }
}

