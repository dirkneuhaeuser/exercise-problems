#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
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
const int INF = 1<<30;

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

    bool is_j_activated_from_cur(int cur, int j){
        // lists all forward edges ({taret node, cap, flow}) of node cur, which have a flow<0 (that means dinic used the forward edge, SOME FLOW HAS BEEN SENT FROM NODE CUR)
        // find first forward edge via binary search. Works only if structed in layer graph. If not start at 0.
        //auto itr = lower_bound(graph[cur].begin(), graph[cur].end(), cur, 
        //       [=](int left, int right){return get<0>(edges[left]) < right; });
        //int lb = itr - graph[cur].begin();

        for(int i=0; i<(int)graph[cur].size(); ++i){
            if(get<2>(edges[graph[cur][i]]) > 0 && get<0>(edges[graph[cur][i]]) == j) return true;
        }
        return false;
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

    void reset_edge(int n, int m, int i, int j){
        int cell = i*(m) + j;
        int idx = n*2 + m*2 + cell *2;
        auto &forwardE = edges[idx];
        auto &backwardE = edges[idx+1];
        ll &activatedFlow = get<2>(forwardE);
        if(activatedFlow == 1){
            // edge to source adj
            auto &forwardSource = edges[2*i];
            auto &backwardSource = edges[2*i+1];
            ll &ff = get<2>(forwardSource);
            ll &bf = get<2>(backwardSource);
            ff--;
            bf++;
            
            // edge to sink adj
            auto &forwardSink = edges[n*2+ 2*j];
            auto &backwardSink = edges[n*2 + 2*j+1];
            ll &ff2 = get<2>(forwardSink);
            ll &bf2 = get<2>(backwardSink);
            ff2--;
            bf2++;

            // edge in-between adj
            alter_edge_in_between(n, m, i, j, 0);
            
        }
    }
    void undo_reset_edge(int n, int m, int i, int j){
        int cell = i*(m) + j;
        int idx = n*2 + m*2 + cell *2;
        auto &forwardE = edges[idx];
        auto &backwardE = edges[idx+1];
        // edge to source adj
        auto &forwardSource = edges[2*i];
        auto &backwardSource = edges[2*i+1];
        ll &ff = get<2>(forwardSource);
        ll &bf = get<2>(backwardSource);
        ff++;
        bf--;
        
        // edge to sink adj
        auto &forwardSink = edges[n*2+ 2*j];
        auto &backwardSink = edges[n*2 + 2*j+1];
        ll &ff2 = get<2>(forwardSink);
        ll &bf2 = get<2>(backwardSink);
        ff2++;
        bf2--;

        // edge in-between adj
        undo_edge_in_between(n, m, i, j);
            
    }

    void undo_edge_in_between(int n, int m, int i, int j){
        int cell = i*(m) + j;
        int idx = n*2 + m*2 + cell *2;
        auto &forwardE = edges[idx];
        auto &backwardE = edges[idx+1];

        ll &ff3 = get<2>(forwardE);
        ll &bf3 = get<2>(backwardE);
        ff3 = 1;
        bf3 = -1;
        ll &fc3 = get<1>(forwardE);
        ll &bc3 = get<1>(backwardE);
        fc3=1;
        bc3=0;


    }

    void alter_edge_in_between(int n, int m, int i, int j, int capacity){
        int cell = i*(m) + j;
        int idx = n*2 + m*2 + cell *2;
        auto &forwardE = edges[idx];
        auto &backwardE = edges[idx+1];

        ll &ff3 = get<2>(forwardE);
        ll &bf3 = get<2>(backwardE);
        ff3 = 0;
        bf3 = 0;
        ll &fc3 = get<1>(forwardE);
        ll &bc3 = get<1>(backwardE);
        fc3=capacity;
        bc3=0;


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
    
    solve(); 
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void printResult(int n, int m,  MaxFlow &mf, int offsetMSums){
    FOR(i, n){
        int curNode = i+1;
        auto e = mf.get_used_forward_edges(curNode);
        FOR(j, m){
            bool found = false;
            FOR(k, e.size()){
                if(get<0>(e[k])-offsetMSums == j){
                    found = true;
                    break;
                }
                if(get<0>(e[k])-offsetMSums > j){
                    break;
                }
            }
            //cout << endl;
            if(found){
                cout << "Y";
            }else{
                cout <<  "N";
            }
        }
        cout << endl;
    }
}
void solve() 
{
    // findings:
    // 1. Two dinics after each othr will lead that the flows alreayd been processesd -> 2nd will have a flow of 0.
    // 2. reducing a capcity and then do dinic again -> 2nd will have flow of 0.
    //
    // idea: repeated maxflow: frist route the rowsums to colsums accordingly. Now in order to get the lowest lexicographical order, we want to set N as early as possible.
    // Therefore, we go through the grid and see if the edge between rowsum i and colsum j has been acticated. If so, we reset it 0 (here is the actual problem of this problem.
    // We can't brueforce all n*m - times the max flow. We are only allowed to reset a specific edges in order to keep us from TLE). So find the right index of all contributing edges (so from source to row i, from row i to col j and from col j to sink) and subtract 1 from forward flow and add 1 to backward flow. Now try dinic again. If the result is 1, then the network found an alternative way activating any cell after the current cell (as all the others have already been fixed).
    int n, m;
    bool start = true;
    while(cin >> n >> m){
        if(n==0 && m ==0 ) break;
        if(!start)cout << endl;
        start = false;
        vector<int> nsums, msums;

        // structure: source, n rows, m cols, sink
        MaxFlow mf(n + m+ 2);
        int offsetNSums = 1;
        int offsetMSums = n+1;
        int sink = n + m+ 1;
        ll totaln = 0, totalm =0;
        FOR(i, n){
            int rowSum; cin >> rowSum;
            totaln += rowSum;
            mf.add_edge(0,offsetNSums + i, rowSum);
        }
        FOR(j, m){
            int colSum; cin >> colSum;
            totalm += colSum;
            mf.add_edge(offsetMSums + j, sink, colSum);
        }
        if(totaln != totalm){
            cout << "Impossible" << endl;
            continue;
        }
        FOR(i, n){
            FOR(j, m){
                mf.add_edge(offsetNSums + i, offsetMSums + j, 1);
            }
        }
        ll flow = mf.dinic(0, sink);
        if(flow < totaln){
            cout << "Impossible" << endl;
            continue;
        }
        FOR(i, n){
            FOR(j, m){
                bool isSet = mf.is_j_activated_from_cur(i+1, j+n+1);
                if(!isSet){
                    mf.alter_edge_in_between(n, m, i, j,0);
                    continue;
                }
                mf.alter_edge(i+1, j+offsetMSums, 0);
                mf.reset_edge(n, m, i, j);
                flow = mf.dinic(0, sink); // should be 1 if it finds annother way
                if(flow != 1){
                    // alternative 1 to establish old graph, set edge to one and run dinic to fulfil all
                    //mf.alter_edge_in_between(n, m, i, j,1);
                    //flow = mf.dinic(0, sink);
                    // alternative 2: just update all involving edges manually
                    mf.undo_reset_edge(n, m, i, j);
                }
            }
        }
        flow = mf.dinic(0, sink);
        printResult(n, m, mf, offsetMSums);

    }

}

