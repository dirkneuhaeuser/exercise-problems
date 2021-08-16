#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
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
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
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
    long long dfs(int cur, int t, long long f=1e18){ // sends a single flow from s to t through level graph O(E)
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
    void dfsMinCut(int cur, vector<int> &visited, vector<int> &firstClass){
        visited[cur] = true;
        firstClass.push_back(cur);
        for(int i=0; i<graph[cur].size(); ++i){
            if(get<2>(edges[graph[cur][i]]) < get<1>(edges[graph[cur][i]]) && !visited[get<0>(edges[graph[cur][i]])]){
                dfsMinCut(get<0>(edges[graph[cur][i]]), visited, firstClass);
            }
        }
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
        edges.emplace_back(cur, directed?0:w, 0); // backward edge
        graph[v].push_back(edges.size()-1);
    }
    long long dinic(int s, int t){  // O(V* (E + VE)) = O(V^2 * E)
         // calculates the maxFlow from s to t
         long long maxFlow = 0;
         while(bfs(s, t)){ // O(E)
             last.assign(n, 0); // this remembers the index for the dfs
             while(long long flow = dfs(s, t)){ // O(E)
                 maxFlow += flow;
             }
         }
         return maxFlow;
    }

    vector<int> getLeftMinCut(int source){
        // returns all nodes, which are on the left side of the min cut. Idea: Go through residual-graph and if an edge still has capacity, this is not the bottleneck of the mincut, and hence the othernode is still part
        // of the left side (->dfs)
        vector<int> visited(n, false), firstClass;
        dfsMinCut(source, visited, firstClass);
        return firstClass;
    }

    vector<tuple<int, long long, long long>> get_used_backward_edges(int cur){
        // lists all backward edges ({taret node, cap, flow}) of node cur, which have a flow<0 (that means dinic used the backward edge, SOME FLOW HAS BEEN SENT TO THE NODE CUR)
        vector<tuple<int, long long, long long>> ret;
        for(int i=0; i<(int)graph[cur].size(); ++i){
            // fasten up in layer-graphs. Works only in LAYER Graph.
            //if(get<0>(edges[graph[cur][i]]) > cur) return ret; // first edgesa are backward edges, if node is bigger: only forward eges left. 
            if(get<2>(edges[graph[cur][i]]) < 0)ret.push_back(edges[graph[cur][i]]);

        }
        return ret;
    }

    vector<tuple<int, long long, long long>> get_used_forward_edges(int cur){
        // lists all forward edges ({taret node, cap, flow}) of node cur, which have a flow<0 (that means dinic used the forward edge, SOME FLOW HAS BEEN SENT FROM NODE CUR)
        vector<tuple<int, long long, long long>> ret;
        // find first forward edge via binary search. Works only if structed in layer graph. If not start at 0.
        //auto itr = lower_bound(graph[cur].begin(), graph[cur].end(), cur, 
        //       [=](int left, int right){return get<0>(edges[left]) < right; });
        //int lb = itr - graph[cur].begin();

        for(int i=0; i<(int)graph[cur].size(); ++i){
            if(get<2>(edges[graph[cur][i]]) > 0)ret.push_back(edges[graph[cur][i]]);
        }
        return ret;
    }

    void dbg_node(int cur){
        // prints all flows towards and all flows from the node cur
        for(int i=0; i<(int)graph[cur].size(); ++i){
            cout << "cur: " << cur << ", Target: " << get<0>(edges[graph[cur][i]]) << ", cap: " << get<1>(edges[graph[cur][i]]) << ", flow: " << get<2>(edges[graph[cur][i]]) << endl;
        }
    }

    void reset(){
        // rests flow of all edges back to 0. Afterwards you can use alter_edge() to change the capacity for a specific edge without rebuilding everything
        for(int i=0; i<(int)edges.size();++i){
            get<2>(edges[i]) = 0;
        }
    }

    void alter_edge(int cur, int v, long long w, bool directed=true){
        // changes the capacity of a specific edge (cur -> v) to w.
        for(int i=0; i<graph[cur].size(); ++i){
            if(get<0>(edges[graph[cur][i]]) == v){
                get<1>(edges[graph[cur][i]]) = w;
                break;
            }
        }
        if(!directed){
            for(int i=0; i<graph[v].size(); ++i){
                if(get<0>(edges[graph[v][i]]) == cur){
                    get<1>(edges[graph[v][i]]) = w;
                    break;
                }
            }
        }
    }
};

//MaxFlow maxFlow = MaxFlow(5); // O(V^2 * E)
//maxFlow.add_edge(0,1,10);
//maxFlow.add_edge(1,3,5);
//maxFlow.add_edge(1,2,5);
//maxFlow.add_edge(3,4,10);
//maxFlow.add_edge(2,4,10);
//long long flow = maxFlow.dinic(0, 4); // max_flow or min_cut or unweighted MCBM (bipartite matching)
//cout << flow << endl;




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
    cin >> t;
    int count = 1;
    while(t--) 
    { 
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    // idea: Create flows from row sums to col sums via cells. In order to properly model '>', '<' and '=' you need to construct 2 graphs.
    // The first will take care of all mandatory flows ('=' and if > x, then you also need at least a flow of x+1)
    // The remaining row-sums can be allocated/flowed via another graph.
    // Note you can't take the same graph, as then the algorithm might revoke some must flows.
    int m, n; cin >> m >> n;
    int INF = 1<<30;
    vector<int> msums, nsums;
    int totalm=0, totaln =0;
    FOR(i, m){
        int rowSum; cin >> rowSum;
        totalm+=rowSum;
        msums.push_back(rowSum);
    }
    FOR(j, n){
        int colSum; cin >> colSum;
        totaln+=colSum;
        nsums.push_back(colSum);
    }
    int k; cin >> k;
    vector<vector<pair<char, int>>> allCons(n*m, vector<pair<char,int>>());
    FOR(i, k){
        int r, c; cin >> r >> c;
        char op; cin >> op;
        int con; cin >> con;
        if(r==0 || c==0){
            if(r==0 && c==0){
                FOR(k, m*n){
                    allCons[k].push_back({op, con});
                }
            }else if(r == 0){
                for(int k = c-1; k<m*n; k+=n){
                    allCons[k].push_back({op, con});
                }
            }else if(c == 0){
                for(int k = (r-1)*n; k<r*n; ++k){
                    allCons[k].push_back({op, con});
                }
            }
        }else{
            int curNode = (r-1) * n + (c-1);
            allCons[curNode].push_back({op, con});
        }
    }
    vector<int> must(m*n, 0), can(m*n, 0);
    FOR(i, m*n){
        // transform all possible constraints to either must-flow or can-flow
        // Equality needs to flow -> must flow
        int even = -1;
        for(auto p: allCons[i]){
            if(p.first == '='){
                if(even != -1 && even != p.second){
                    cout << "IMPOSSIBLE" << endl;
                    return;
                }
                even = p.second;
            }
        }
        // greater than: part must-flow, part can-flow
        int greater = -1;
        for(auto p: allCons[i]){
            if(p.first == '>'){
                greater = max(greater, p.second);
            }
        }
        if(even != -1 && greater != -1 && greater+1>even){
            cout << "IMPOSSIBLE" << endl;
            return;
        }
        // greater than: only can-flow
        int smaller = INF;
        for(auto p: allCons[i]){
            if(p.first == '<'){
                smaller = min(smaller, p.second);
            }
        }
        if(even != -1 && smaller != INF && smaller-1 < even){
            cout << "IMPOSSIBLE" << endl;
            return;
        }
        if(greater != -1 && smaller != INF && smaller-1 < greater+1){
            cout << "IMPOSSIBLE" << endl;
            return;
        }
        if(even!= -1){
            must[i] = even;
        }else{
            if(smaller != INF && greater != -1){
                must[i] = greater+1;
                int additional = smaller -1 - (greater + 1);
                can[i] = additional;
            }else if(greater != -1){
                must[i] = greater+1;
                can[i] = INF;
            }else if(smaller != INF){
                int additional = smaller -1;
                can[i] = additional;
            }else{
                can[i] = INF;
            }
        }
    }


    // Now we do a two step max flow.
    // 1. step try to allocate all must-flows
    // 2. step create new graph and then try to allocate the remaining sums via can-cells.
    // VERY IMPORTANT: You have to use two different graphs. If you use the same graph, in the second step it might revoke some must-flows.


    // First: Must-flow
    //structure: source, m row sums, n col sums, sink
    MaxFlow mf(m*n + m + n + 2);
    int offsetRowSum = m*n + 1;
    int offsetColSum = m*n + m + 1;
    int sink = m*n + m + n + 1;
    FOR(i, m){
        mf.add_edge(0, i + offsetRowSum, msums[i]);
    }
    FOR(j, n){
        mf.add_edge(j + offsetColSum, sink, nsums[j]);
    }
    ll mustFlow = 0;
    FOR(i, m*n){
        int row = i/n;
        int col = i % n;
        if(must[i]){
            mustFlow += must[i];
            mf.add_edge(row + offsetRowSum, i+1, must[i]);
            mf.add_edge(i+1, col + offsetColSum, must[i]);
        }
    }
    ll firstFlow = mf.dinic(0, sink);
    if(firstFlow != mustFlow){
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    vector<vector<int>> ret(m, vector<int>(n, 0));
    FOR(i, m){
        FOR(j, n){
            int idx = i*n + j;
            auto usedEdges =  mf.get_used_forward_edges(idx+1);
            ll f = 0;
            for(auto e: usedEdges){
                f += get<2>(e);
            }
            ret[i][j] += f;
            nsums[j]-=f;
            msums[i]-=f;
        }
        
    }

    // Second: Can-flow
    // Now allocate the remaining sums to the cells which are not obligatory..
    MaxFlow mf2(m*n + m + n + 2);
    FOR(i, m){
        mf2.add_edge(0, i + offsetRowSum, msums[i]);
    }
    FOR(j, n){
        mf2.add_edge(j + offsetColSum, sink, nsums[j]);
    }
    FOR(i, m*n){
        int row = i/n;
        int col = i % n;
        if(can[i]){
            mustFlow += can[i];
            mf2.add_edge(row + offsetRowSum, i+1, can[i]);
            mf2.add_edge(i+1, col + offsetColSum, can[i]);
        }
    }
    ll additionalFlow = mf2.dinic(0, sink);
    if(firstFlow + additionalFlow != totalm){
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    FOR(i, m){
        FOR(j, n){
            int idx = i*n + j;
            auto usedEdges =  mf2.get_used_forward_edges(idx+1);
            ll f = 0;
            for(auto e: usedEdges){
                f += get<2>(e);
            }
            ret[i][j] += f;
            cout << ret[i][j];
            if(j < n-1) cout << " ";
            nsums[j]-=f;
            msums[i]-=f;
        }
        cout << endl;
        
    }




}

