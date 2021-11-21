## Shortest Paths

When the edges are not weighter we can use a **bfs** for the shortes paths, othrweise **Dijkstra**'s algorithm.
Dijkstra uses the same idea of a BFS, but instead of a normal queue, it uses a **priority queue to favour nodes with a smaller distance**.
Often when problem appear to be a **DP problem**, but are **not** defined on a **DAG**, then most certainly these are BFS problems.

**Typic Examples**:

Single Source Shortest Path (SSSP) </br>
Singe Source Single Destinaion Shortest Path (SSSDSP) </br>
Multiple Sources Shortest Pahts (MSSP) </br>

### Unweighted Shortest Paths - BFS

The normal **BFS** provides us with the shortest distance to all nodes in <img src="https://render.githubusercontent.com/render/math?math=O(V %2B E)">.

Typical 2D Grid example:
```
queue<pii>q; 
q.insert({startI, startJ})
vector<pii> dir {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
while(q.size()){
    auto [i, j] = q.front(); q.pop();
    for(auto [di, dj]: dir){
        int nextI = i + di;
        int nextJ = j + dj;
        if(nextI < 0 || nextJ < 0 || nextI > n-1 || nextJ >n-1) continue;
        if(dis[nextI][nextJ] < INF) continue;
        dis[nextI][nextJ] = dis[i][j] + 1;
        q.push({nextI, nextJ});
    }
}
```

Note: Similarly, A graph with only **0/1 Weights** can be handeld by a **deque** (very similar to Dijkstra). If we have a 0 Edge we will push it to the front, else to the back. Dijkstra would works just as fine, but this way we save us from using an expensive priority-queue.



### Weigthed Shortest Paths (no negative cycles) - Dijkstra

If the edges are weighted, e.g. we want to minimise the time to go from a to b, we need to use a `priority_queue` instead of a normal `queue`, as the main idea is to always use the cell/node with the current lowest cost/time. This node cannot improved any further, but maybe can be used to improve others.
Unfortunately, the `priority_queue` in c++ doesn't allowe to update keys, therefore we use `set` here. The complexity is <img src="https://render.githubusercontent.com/render/math?math=O((V %2B E) \log V)">.

Note Dijkstra does not work, when there is a negative cycle.


```
vector<ll> dijkstra(ll start, vector<vector<pll>> &AL){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHT CYCLES
    ll n = AL.size();
    vector<ll> dist(AL.size(), INF);
    dist[start] = 0;
    set<pll> pq;
    pq.emplace(dist[start], start);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [next, w]: AL[cur]){
            if(dist[cur] + w >= dist[next]) continue;
            auto it = pq.find({dist[next], next});
            if(it != pq.end()){
                pq.erase(it); // O(E * log(V));
            }
            dist[next] = dist[cur] + w;
            pq.emplace(dist[next], next);

        }
    }
    return dist;
}
```

Notes:
1. For **reconstruction** of a single shortest path use a **parent vector** and whenever you can update the next element, update also the parent (Works for bfs/dijkstra).
2. To know wheter an **edge/node is part of one of the shortest paths**: Apply weighted/unweighted from begining and again from end (reversed AL).
A node is part of a shortest path if `dist[node] + distRev[node] == dist[endNode]`, analogously an edge is part of a shortest path if both connected nodes are part of the shortest path + the difference in between both `dist` values is the weight of the edge `w`.
3. When there are some further monoton restrictions, apply them during the for-loop inside Dijkstra.

### Weigthed Shortest Paths with negative Cycle - Bellmann-Ford
When there are negative Cycles then Dijkstra would run forever without stopping. **Bellmann-Ford** alleviates this issue by running the **exact amount** of **iterations** needed to calculate the shortest path from the rooot to any other node, assuming there are no negative cycles. To check if there is a negative cycle, another single iteration can be made. If any weight improves, then there is a negative cycle. The algorithm runs in <img src="https://render.githubusercontent.com/render/math?math=O(V^3)"> and therfore requires a `V <= 450`.

```
vector<int> bellmann_ford(int start, vector<vector<pii>> &AL){ // O(V^3)
    // Get the distance from start node to all other nodes and works with negative cycles (no infinite queue)
    // Stops after n iterations, if afterwars still relaxations are possible -> negative cycle
    // Limit ~ V<450
    int n = AL.size();
    vector<int> dist = vector<int>(n, INF);
    dist[start] = 0;
    for(int i=0; i<n; ++i){ // O(V^3)
        for(int v=0; v<n; ++v){
            if(dist[v] != INF){
                for(auto [next, w]: AL[v]){
                    dist[next] = min(dist[next], dist[v] + w);
                }
            }
        }
    }
    return dist;
}

vector<bool> NINFS;
void dfsGetNINF(int cur, vector<vector<pii>> &AL){
    NINFS[cur] = true;
    for(auto [next,w]: AL[cur]){
        if(NINFS[next] == 0){
            dfsGetNINF(next, AL);
        }
    }
}

vector<bool> getNegativeCycleStarts(int start, vector<int> &dist, vector<vector<pii>> &AL){
    // Gets nodes which are part of a negtive cycle. BUT is does not return ALL nodes of this cycle. Do a dfs to get all nodes after this being detected.
    int n = AL.size();
    vector<bool> isNINF = vector<bool>(n, false);
    for(int v=0; v<n; ++v){
        if(dist[v] != INF){
            for(auto [next, w]: AL[v]){
                if(dist[next] > dist[v] + w){
                    dist[next] = dist[v] + w;
                    isNINF[next] = true;
                    isNINF[v] = true;
                }
            }
        }
    }
    return isNINF;
}

// vector<int> dist = bellmann_ford(0, AL);
// vector<bool> starts = getNegativeCycleStarts(0, dist, AL);
// NINFS.assign(n, false);
// FOR(i, n){
//     if(starts[i] && NINFS[i] == 0){
//         dfsGetNINF(i, AL);
//     }
// }
// // now if not NINFS[i] == true, dist[i] has the exact distance from 0 to i. Else we can say its negative INF.

```
Note: 
- Sometimes the task is about positive cycles, than **changing the sign** might do the trick.
- Bellmann-Ford sometimes come also with further <img src="https://render.githubusercontent.com/render/math?math=O(V %2B E)">, which then need to be incorporated into the <img src="https://render.githubusercontent.com/render/math?math=O(V^3)"> loop.


### Applications
- Shortest Cycle: Shortest Path from i to j and from j to i. Within Floyd-Warshall, we can just look at `AM[i][i]`.


