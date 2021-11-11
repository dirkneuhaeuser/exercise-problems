#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
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
vector<string> tokenize(string s, string del = " "){
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


void solve() 
{
    // basic sssp, here again with queue and dis array.
    // Only difficulty is the transfer from names to integers and vice versa
    string line;
    vector<vector<string>> lines;
    while(getline(cin, line)){
        if(line != ""){
            vector<string> a = tokenize(line);
            lines.push_back(a);
        }
    }
    int listedN = lines.size();
    vector<string> idx2name;
    unordered_map<string, int> name2idx;
    int idx = 0;
    FOR(i, listedN){
        string name = lines[i][0];
        name2idx[name] = idx++;
        idx2name.push_back(name);
    }
    vector<set<int>> AL(listedN, set<int>());
    FOR(i, listedN){
        for(int j =1; j<lines[i].size(); ++j){
            string s = lines[i][j];
            if(name2idx.count(s) == 0){
                name2idx[s] = idx++;
                idx2name.push_back(s);

            }
            int coAuth = name2idx[s];
            if(AL.size() <= coAuth){
                AL.push_back({});
            }
            AL[coAuth].insert(i);
            AL[i].insert(coAuth);
        }
    }
    int n = AL.size();
    int idxStart = name2idx["PAUL_ERDOS"];
    vector<int> dis(n, INF);
    dis[idxStart] = 0;
    queue<int> q;
    q.push(idxStart);
    while(q.size()){
        int cur = q.front(); q.pop();
        for(int next: AL[cur]){
            if(dis[next] == INF){
                dis[next] = 1 + dis[cur];
                q.push(next);
            }
        }
    }
    FOR(i, listedN){
        if(dis[i] == INF){
            cout << idx2name[i] << " no-connection" << endl;
        }else{
            cout << idx2name[i] << " " << dis[i] << endl;
        }
    }
}

