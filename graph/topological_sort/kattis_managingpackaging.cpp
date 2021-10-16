#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
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

vector<string> tokenize(string &s, string del = " "){
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
enum {VISITED=-1, UNVISITED=-2, EXPLORED=-3};
vector<int> visited;

bool hasCycle(int cur, vector<vector<int>> &AL){
    visited[cur] = EXPLORED;
    for(int next: AL[cur]){
        if(visited[next] == EXPLORED){
            return true;
        }
        if(visited[next] == UNVISITED && hasCycle(next, AL)){
            return true;
            
        }
    }
    visited[cur] = VISITED;
    return false;
}


void solve() 
{
    // Topological Sort with cycle check
    // Use Kahn algorithm to prefere lexicographically smaller strings
    string line;
    while(true){
        getline(cin, line);
        int n = stoi(line);
        if(n == 0) break;
        int idx = 0;
        unordered_map<string, int> name2idx;
        vector<vector<int>> AL(n, vector<int>());
        vector<int> inDegree(n,0);

        vector<vector<string>> tokenLines;
        unordered_set<string> seen;

        FOR(i, n){ // O(n * stringlength)
            getline(cin, line);
            vector<string> packs = tokenize(line);
            for(string s: packs){
                seen.insert(s);
            }
            tokenLines.push_back(packs);
        }
        // create mapping packages(idx2name) which is already lexicographically sorted
        vector<string> packages(seen.begin(), seen.end()); // O(n log n)
        sort(packages.begin(), packages.end());
        FOR(i, n){ 
            name2idx[packages[i]] = i;
        }


        // create AL
        FOR(i, n){ // O(m)
            int curIdx = name2idx[tokenLines[i][0]];
            for(int j=1; j<tokenLines[i].size(); ++j){

                AL[name2idx[tokenLines[i][j]]].push_back(curIdx);
                inDegree[curIdx]++;
            }
        }

        // check for cycles;
        visited.assign(n, UNVISITED);
        bool existCycle = false;
        FOR(i, n){ // O(n+m);
            if(visited[i] == UNVISITED){
                if(hasCycle(i, AL)){
                    existCycle = true;
                    break;
                }
            }
        }
        if(existCycle){
            cout << "cannot be ordered" << endl;
            continue;
        }

        // get topological order O(n log(n))
        priority_queue<int, vector<int>, greater<int>> pq;
        FOR(i, n){
            if(inDegree[i]==0) pq.push(i);
        }
        while(pq.size() >0){
            int curI = pq.top(); pq.pop();
            cout << packages[curI] << endl;
            for(int next: AL[curI]){
                inDegree[next]--;
                if(inDegree[next] == 0){
                    pq.push(next);
                }
            }
        }

        cout  << endl;
    }
}

