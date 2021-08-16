#nclude"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#define FORS(i, n) for(; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/templates/debug.h"
#endif

// 2**6 =  64                           // 4!  = 24                       
// 2**8 =  256                          // 5!  = 120                      
// 2**10 = 1,024                        // 6!  = 720
// 2**15 = 32,768                       // 7!  = 5,040
// 2**20 = 1,048,576                    // 8!  = 40,320
// 2**25 = 33,554,432                   // 9!  = 362,880
// 2**30 = 1,073,741,824                // 10! = 3,628,800
// 2**32 = 4,294,967,296                // 12! = 479,001,600
                                        // 14! = 87,178,291,200
// int up to  2*10^9 (2^31-1)           // 16! = 20,922,789,888,000
// ll up to   9*10^18 (2^63 -1)         // 18! = 6,402,373,705,728,000
// ull up to 18*10^18 (2^64-1)/         // 20! = 2,432,902,008,176,640,000                                                                    
// ld up to  10*10^307
ll smod(ll a, ll m){return((a%m) +m) %m;}
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*b,m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;

// Calculates maxFlow == minCut in O(V^2 E)
class MaxFlow {
private:
    int n;
    vector<tuple<int, long long, long long>> edges; // (target node, capacity, flow used)
    vector<vector<int>> graph;
    vector<int> distance, last;
    bool bfs(int s, int t){ // construct level graph and check if more flow is possible
        distance.assign(n, -1);
        distance[s]=0;
        queue<int> q({s});
        while (!q.empty()){
            int cur = q.front(); q.pop();
            if(cur == t){break;}
            for(int idx: graph[cur]){
                auto &[v, cap, flow] = edges[idx];
                if((cap - flow) > 0 && distance[v]==-1){
                    q.push(v);
                    distance[v] = distance[cur] + 1;
                }
            }

        }
        return distance[t] != -1;

    }

    long long dfs(int cur, int t, long long f=1e18){ // send multiple flows from s to t through level graph
        if(cur==t || f==0) return f;
        for(int &i = last[cur]; i<(int)graph[cur].size(); ++i){
            auto &[v, cap, flow] = edges[graph[cur][i]];
            if(distance[cur] != distance[v] -1) continue;
            if(long long pushed = dfs(v, t, min(f, cap-flow))){
                flow += pushed;
                long long &rflow = get<2>(edges[graph[cur][i]^1]); // clever way to get back edge number^1 -> number +1 if number even else number -1
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
public:
    MaxFlow(int nodes): n(nodes) {
        edges.clear();
        graph.assign(n, vector<int>());
    }
    void add_edge(int cur, int v, long long w, bool directed=true){
        if(cur == v){return;}
        edges.emplace_back(v, w, 0);
        graph[cur].push_back(edges.size()-1);
        edges.emplace_back(cur, directed?0:w, 0);
        graph[v].push_back(edges.size()-1);
    }
   long long dinic(int s, int t){ // calculates the maxFlow from s to t
        long long maxFlow = 0;
        while(bfs(s, t)){
            last.assign(n, 0); // this remembers the index for the dfs
            while(long long flow = dfs(s, t)){
                maxFlow += flow;
            }
        }
        return maxFlow;

    }
};

// MaxFlow maxFlow = MaxFlow(4);
// maxFlow.add_edge(0,1,10);
// maxFlow.add_edge(1,2,5);
// maxFlow.add_edge(2,3,10);
// long long test = maxFlow.dinic(0, 3);
// cout << test << endl;


void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 
    
    int t=1; 
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    // This is a hidden unweighted perfect matching (MCBM).
    // The bipartie graph consists of all possible vertical lines (left nodes) and horizontal lines (right nodes)
    // If perfect matching: The opponent always can play the corresponding match and we will lose
    // -> if there is not perfect matching, we win. I use Dinic for weighted MCBM.
    int n; cin >> n;
    ll INF = 1l << 62;
    set<int> xs, ys;
    vector<vector<int>> g(501, vector<int>());
    FOR(i, n){
        int x, y; cin >> x >> y;
        xs.insert(x);
        ys.insert(y);
        g[x].push_back(y);
    }
    int s = xs.size() + ys.size();
    int c = 1;
    unordered_map<int, int> alr;
    MaxFlow maxFlow = MaxFlow(s+2);

    FOR(i, g.size()){

        if(g[i].empty())continue;
        int cur = c++;
        maxFlow.add_edge(0,cur,1);
        FOR(j, g[i].size()){
            auto it = alr.find(g[i][j]);

            int nodeval;
            if(it!= alr.end()){
                nodeval = it->second;
            }else{
                nodeval = c++;
                alr[g[i][j]] = nodeval;
                maxFlow.add_edge(nodeval,s+1,1);
            }
            maxFlow.add_edge(cur,nodeval,1);
        }
    }
    long long matches = maxFlow.dinic(0, s+1);
    //cout << matches << endl;
    if(matches!=xs.size() || matches != ys.size()){
        cout << "Mirko"; // perfect matching
    }else{
        cout << "Slavko";
    }

}

