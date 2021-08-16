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
        //cout << cur << " " << v <<  " || " << w << endl;
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
//cout << flow << endl;


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
    int n, q, s; cin >> n >> q >> s;
    vector<int>s2q, q_cap;
    FOR(i, s){
        int qq; cin >> qq;
        qq--;
        s2q.push_back(qq);
    }

    FOR(i, q){
        int ql; cin >> ql;
        q_cap.push_back(ql);
    }
    // max flow with back-coupling (to next time periods)
    // maxFlow problem: source, sensor*times, queues*time (sum up previous and current), queues*time(vertex restriction: sum < cap), times (window restriction), sink
    // 1 + s*n + q*n + q*n + n + 1
    MaxFlow maxFlow = MaxFlow( 2 + s*n + 2*q*n + n);
    int sum_offset = n*s + 1;
    int sum_restriction_offset = n*s + n*q + 1;
    int window_offset = n*s + 2*n*q + 1;
    int sink = 2 + s*n + 2*q*n + n - 1;
    ll all_data = 0;
    FOR(i, n){
        int window; cin >> window;
        //vector<int> s_data;
        int q_offset = i*q;
        FOR(j, s){
            int data; cin >>data;
            all_data += data;
            //s_data.push_back(data);
            int node = i*s +j;
            maxFlow.add_edge(0, 1 + node, data); // sensor pro time
            int cur_q = s2q[j];
            int cur_q_cap = q_cap[s2q[j]];
            // add to sum
            maxFlow.add_edge(1 + node, sum_offset + q_offset + cur_q, cur_q_cap); // add the current sensor flow to the sum of current and previous.

        }
        FOR(cur_q, q){
            int cur_q_cap = q_cap[cur_q];
            // sum restrition: veretex restriction
            maxFlow.add_edge(sum_offset + q_offset + cur_q, sum_restriction_offset + q_offset + cur_q ,cur_q_cap); // restriction sum can only be at max current

            // get rid of current data in this q either now
            maxFlow.add_edge(sum_restriction_offset + q_offset + cur_q , window_offset + i, cur_q_cap); // sensor pro time

            // or save it up for future (back-coupling)
            if(i < n-1){
                maxFlow.add_edge(sum_restriction_offset + q_offset + cur_q , sum_offset + q_offset + q + cur_q, cur_q_cap); // sensor pro time
            }

        }
        maxFlow.add_edge(window_offset + i, sink, window); // after each window, we can get rid of window -restriction
    }
    // nodes = O(s*n) - > dinix = O((s*n)^4) = 3000^4. But as we know that edges are O(V) - > dinic = (3000^3)
    ll flow = maxFlow.dinic(0, sink);
    if(flow == all_data){
        cout << "possible" << endl;
    }else{
        cout << "impossible" << endl;
    }
        





}

