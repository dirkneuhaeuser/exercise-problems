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
enum {UNVISITED = -1};

unordered_map<string, int> dfs_num, dfs_low, visited;
unordered_map<string, string> roots;
stack<string> s;
int dfs_idx;
void tarjan(string cur, unordered_map<string, vector<string>> &AL, vector<string> &paradox){
    dfs_num[cur] = dfs_low[cur] = dfs_idx++;
    visited[cur] = 1;
    s.push(cur);
    for(string next: AL[cur]){
        if(dfs_num[next] == UNVISITED){
            tarjan(next, AL, paradox);
        }
        if(visited[next] == 1){
            dfs_low[cur] = min(dfs_low[cur], dfs_low[next]);
        }
    }
    if(dfs_low[cur] == dfs_num[cur]){
        bool isParadox = false;
        while(true){
            string p = s.top(); s.pop();
            if(p != cur) isParadox = true; //self edges not included;
            visited[p] = 0;
            roots[p] = cur;
            if(isParadox) paradox.push_back(p);
            if(p == cur) break;
        }
    }

}


void solve() 
{
    // 1. detect paradox constructs
    //    - paradox are strongly connected components (ssc)
    //    - reduce all ssc to one node (these cannot be part of hillybillys)
    // 2. detect hillybilly
    //    topological sort with passing set of parents
    //
    //    NOTE: THIS POGRAMME DOESN'T PASS THE TESTS. Let me know if you find the error :P
    string line;
    bool first = true;
    set<string> directMama;
    set<pair<string, string>> alr;
    while(getline(cin, line) && line != ""){
        if(!first)cout << endl;
        first = false;
        unordered_map<string, vector<string>> AL;
        unordered_set<string> seen;
        while(true){
            if(line == "done")break;
            stringstream ss; ss << line;
            string a, b, c; ss >> a >> b >> c;
            if(alr.count({a, c})==0){
                alr.insert({a, c});
                AL[a].push_back(c);
                seen.insert(a);
                seen.insert(c);
                if(a == c) directMama.insert(a);
            }
            getline(cin, line);
        }


        // calculating all SSC (paradox);
        dfs_num.clear();
        dfs_low.clear();
        visited.clear();
        roots.clear();
        dfs_idx=0;
        s = stack<string>();

        for(string name:seen){
            dfs_num[name] = UNVISITED;
            dfs_low[name] = UNVISITED;
            visited[name] = 0;
            roots[name] = name;
        }
        vector<string> paradox;
        for(string name:seen){
            if(dfs_num[name] == UNVISITED){
                tarjan(name, AL, paradox);
            }
        }
        set<string>paradoxSet(paradox.begin(), paradox.end());
        for(string direct: directMama){
            paradoxSet.insert(direct);
        }
        //dbg(paradoxSet);

        // init indegree
        unordered_map<string, int> inDegree;
        for(string s: seen){
            if(roots[s] != s) continue;
            inDegree[s] = 0;
        }
        for(auto [k, val]: AL){
            string rk = roots[k];
            for(string next: val){
                string rnext = roots[next];
                if(rk == rnext) continue; // same ssc doens't count
                inDegree[rnext]++;
            }
        }
        //dbg(inDegree);


        // top sort
        queue<string> q;
        unordered_map<string, unordered_set<string>> diffParents;
        unordered_set<string> hillbilliesSet;

        for(string s: seen){
            if(roots[s] != s) continue;
            diffParents[s] = unordered_set<string>();
            if(inDegree[s] == 0 && paradoxSet.count(s) == 0){ // TODO:check for paradoxSet
                q.push(s);
            }
        }
        while(q.size()> 0){
            string cur = q.front(); q.pop(); // always a root
            //cout << cur << endl;
            //dbg(diffParents);
            assert(paradoxSet.count(cur) == 0);
            assert(hillbilliesSet.count(cur) == 0);
            assert(diffParents[cur].count(cur) == 0); // else paradox
            diffParents[cur].insert(cur);
            for(string next: AL[cur]){
                string r = roots[next];
                if(cur == r) continue;
                for(string pp: diffParents[cur]){
                    if(diffParents[r].count(pp) && paradoxSet.count(r) == 0){
                        hillbilliesSet.insert(r);
                    }
                    diffParents[r].insert(pp);
                }
                inDegree[r]--;

                // no pushing hillbillies -> all kids of them will be left over to -> hillbillies later (same for paradoxes as it implies all kids are hillbillies too);
                if(inDegree[r] == 0 && hillbilliesSet.count(r) == 0 && paradoxSet.count(r)==0){ 
                    q.push(r);
                }
            }
        }
        //dbg(diffParents);
        for(auto [k, val]: inDegree){
            if(val>0 && paradoxSet.count(k) == 0){
                hillbilliesSet.insert(k);
            }
        }
        //dbg(paradoxSet);
        //dbg(hillbilliesSet);

        map<string, string> types; // already sorted
        for(string h: hillbilliesSet){
            types[h] = "hillbilly";
        }
        for(string p: paradoxSet){
            types[p] = "paradox";
        }
        for(auto [k, val]: types){
            cout << k << " " << val << endl;
        }
    }



}


