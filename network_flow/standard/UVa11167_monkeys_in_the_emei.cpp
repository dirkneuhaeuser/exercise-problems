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
public:
    MaxFlow(int nodes): n(nodes) {
        edges.clear();
        graph.assign(n, vector<int>());
    }
    void add_edge(int cur, int v, long long w, bool directed=true){
        if(cur == v){return;}
        edges.emplace_back(v, w, 0);
        graph[cur].push_back(edges.size()-1);
        edges.emplace_back(cur, directed?0:w, 0); // residual graph
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

    // lists all residual edges ({taret node, cap, flow}) of node cur, which have a flow<0 (that means dinic used the forward edge)
    vector<tuple<int, long long, long long>> get_used_residual_edges(int cur){
        vector<tuple<int, long long, long long>> ret;
        for(int i=0; i<(int)graph[cur].size(); ++i){
            if(get<0>(edges[graph[cur][i]]) > cur) return ret; // first edgesa are residual edges, if node is bigger: only forward eges left. 
            if(get<2>(edges[graph[cur][i]]) < 0)ret.push_back(edges[graph[cur][i]]);
            //cout << "cur: " << cur << ", Target: " << get<0>(edges[graph[cur][i]]) << ", cap: " << get<1>(edges[graph[cur][i]]) << ", flow: " << get<2>(edges[graph[cur][i]]) << endl;

        }
        return ret;
    }

    // lists all residual edges ({taret node, cap, flow}) of node cur, which have a flow<0 (that means dinic used the forward edge)
    vector<tuple<int, long long, long long>> get_used_forward_edges(int cur){
        // find first forward edge via binary search
        vector<tuple<int, long long, long long>> ret;
        auto itr = lower_bound(graph[cur].begin(), graph[cur].end(), cur, 
               [=](int left, int right){return get<0>(edges[left]) < right; });
        int lb = itr - graph[cur].begin();

        for(int i=lb; i<(int)graph[cur].size(); ++i){
            if(get<2>(edges[graph[cur][i]]) > 0)ret.push_back(edges[graph[cur][i]]);
            //cout << "Target: " << get<0>(edges[graph[cur][i]]) << ", cap: " << get<1>(edges[graph[cur][i]]) << ", flow: " << get<2>(edges[graph[cur][i]]) << endl;
        }
        return ret;
    }
};

//MaxFlow maxFlow = MaxFlow(5); // O(V^2 * E)
//maxFlow.add_edge(0,1,10);
//maxFlow.add_edge(1,3,5);
//maxFlow.add_edge(1,2,5);
//maxFlow.add_edge(3,4,10);
//maxFlow.add_edge(2,4,10);
//long long flow = maxFlow.dinic(0, 4); // max_flow or min_cut or unweighted MCBM (bipartite matching)
// cout << flow << endl;


// backwards flow to get the actual assignment:
//vector<tuple<int, long long, long long>> res_edges = maxFlow.get_used_residual_edges(4);
//for(int i=0; i<res_edges.size(); ++i){
//    cout <<  "The node 4 has used the edge towards " << get<0>(res_edges[i]) << "." <<endl;
//}

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
    //cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        //cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    int monkeys, same_time; 
    int count = 1;
    while(cin >> monkeys >> same_time){
        // Assignment Problem: If allocation possible, if so, generate possible allocation.
        // idea: max flow: source, possible times, monkey_time_windows, sink -> 1 + 50K + 100 + 1 = 50102;
        int monkey_offset = 50001;
        int sink = 50101;
        int INF = 1<<30;
        

        MaxFlow maxFlow = MaxFlow(50102); // O(V^2 * E)
        for(int i =0; i<50000; ++i){
            maxFlow.add_edge(0,i+1, same_time);
        }
        ll goal = 0;
        FOR(i, monkeys){
            int v, a, b; cin >> v >> a >> b;
            for(int j=a; j<b;++j){ 
                // 1 betwen times and ape
                maxFlow.add_edge(j+1,monkey_offset + i, 1);
            }
            maxFlow.add_edge(monkey_offset + i, sink , v);
            goal += v;
        }
        long long flow = maxFlow.dinic(0, sink); // max_flow or min_cut or unweighted MCBM (bipartite matching)
        if(goal == flow){
        cout<<"Case " << count++ << ": Yes" << endl;
        vector<pair<int, int>> periods;
        FOR(i, monkeys){
            int start = -1, end = -1;
            periods.clear();
            auto b_edges = maxFlow.get_used_residual_edges(monkey_offset + i);
            for(auto e: b_edges){
                int time = get<0>(e) -1;
                if(start == -1){
                    start = time;
                    end = time + 1;
                }else{
                    if(end == time){
                        end++;
                    }else{
                        periods.push_back({start, end});
                        start = time; end = time + 1;
                    }
                }
            }
            if(start!= -1){
                periods.push_back({start, end});
            }
            FOR(i, periods.size()){
                if(i==0){
                    cout << periods.size();
                    
                }
                cout << " (" <<  periods[i].first << "," << periods[i].second << ")";
            }
            cout << endl;
        }

        }else{
        cout<<"Case " << count++ << ": No" << endl;
        }
    }

}

