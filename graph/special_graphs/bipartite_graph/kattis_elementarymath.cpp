#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<ll> vi;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
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
// Calculates maxFlow == minCut in O(V^2 * E)
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
        assert(cur<n && v < n);
        if(cur == v){return;}
        edges.emplace_back(v, w, 0);
        graph[cur].push_back(edges.size()-1);
        edges.emplace_back(cur, directed?0:w, 0); // backward edge
        graph[v].push_back(edges.size()-1);
    }
    long long dinic(int s, int t){  // O(V* (E + VE)) = O(V^2 * E)
         // calculates the maxFlow from s to t
         assert(s<n && t < n);
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

    void dbg_all_nodes(){
        // prints all flows towards and all flows from the node cur
        for(int j=0; j<graph.size(); ++j){
            for(int i=0; i<(int)graph[j].size(); ++i){
                cout << "cur: " << j << ", Target: " << get<0>(edges[graph[j][i]]) << ", cap: " << get<1>(edges[graph[j][i]]) << ", flow: " << get<2>(edges[graph[j][i]]) << endl;
            }
            cout << endl;
        }
    }

    void reset(){
        // rests flow of all edges back to 0. Afterwards you can use alter_edge() to change the capacity for a specific edge without rebuilding everything
        for(int i=0; i<(int)edges.size();++i){
            get<2>(edges[i]) = 0;
        }
    }

    void alter_edge_by_idx(int idx, int capacity){ // O(1)
        // Note that idx needs to be multiplictated by two (as each edge before idx puts 2 elements into the edges list (forward and backward)
        auto &forwardE = edges[idx];
        auto &backwardE = edges[idx+1];

        get<2>(forwardE) = 0; //get<> returns reference
        get<2>(backwardE) = 0;
        get<1>(forwardE) = capacity;
        get<1>(backwardE) = capacity;


    }

    void alter_edge(int cur, int v, long long w, bool directed=true){ // O(E)
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

vi idx2num;

map<ll, ll> comp(set<ll> &A){
    map<ll,ll> mem;
    for(auto p: A) mem[p] = 0;
    ll sz = 0;
    for(auto &p: mem){
        p.second = sz++;
        idx2num.push_back(p.first);
    }
    //for(auto &p: A) p = mem[p];
    return mem;
}

void solve() 
{
    // problem: https://open.kattis.com/problems/elementarymath 
    // about: Maxflow assignment problem (find matching between equations and results, s.t. each result has been used only once).
    int n; cin >> n;
    idx2num.clear();
    set<ll> possible;
    vector<pll> nums;
    FOR(i, n){
        ll a, b; cin >> a >> b;
        nums.push_back({a, b});
        possible.insert(a+b);
        possible.insert(a-b);
        possible.insert(a*b);
    }
    map<ll, ll> compressed = comp(possible);
    int m = possible.size();
    MaxFlow mf(n+m+2);
    int offset_results = n+1;
    int sink = n+m+1;
    FOR(i, n){
        auto [a, b] = nums[i];
        ll add = a+b;
        ll addIdx = compressed[add];
        ll sub = a-b;
        ll subIdx = compressed[sub];
        ll prd = a*b;
        ll prdIdx = compressed[prd];
        mf.add_edge(0, 1+i, 1);
        mf.add_edge(1+i, offset_results+addIdx, 1);
        mf.add_edge(1+i, offset_results+subIdx, 1);
        mf.add_edge(1+i, offset_results+prdIdx, 1);
    }
    FOR(i, m){
        mf.add_edge(offset_results+i, sink, 1);
    }
    ll flow = mf.dinic(0, sink);
    if(flow < n){
        cout << "impossible" << endl;
    }else{
        FOR(i, n){
            auto [a, b] = nums[i];
            auto v= mf.get_used_forward_edges(1+i);
            int targetIdx = get<0>(v[0]) - offset_results;
            ll value = idx2num[targetIdx];
            if(a - b == value){
                cout << a << " - " << b << " = " << value << endl;
            }else if(a + b == value){
                cout << a << " + " << b << " = " << value << endl;
            }else if(a * b == value){
                cout << a << " * " << b << " = " << value << endl;
            }else{
                assert(false);
            }
        }
    }

}

