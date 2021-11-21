## Shortest Paths

When the edges are not weighter we can use a **bfs** for the shortes paths, othrweise **Dijkstra**'s algorithm.
Dijkstra uses the same idea of a BFS, but instead of a normal queue, it uses a **priority queue to favour nodes with a smaller distance**. 

**Typic Examples**:

Single Source Shortest Path (SSSP) </br>
Singe Source Single Destinaion Shortest Path (SSSDSP) </br>
Multiple Sources Shortest Pahts (MSSP) </br>

### Unweighted Shortest Paths

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

Note: Similarly, A graph with only 0/1 Weights can be handeld by a deque (very similar to Dijkstra). If we have a 0 Edge we will push it to the front, else to the back.



### Weigthed Shortest Paths

If the edges are weighted, e.g. we want to minimise the time to go from a to b, we need to use a `priority_queue` instead of a normal `queue`, as the main idea is to always use the cell/node with the current lowest cost/time. This cannot improved any further, but maybe can be used to improve others.
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
1. For **reconstruction** of a single shortest path use a parent vector and whenever you can update the next element, update also the parent (Works for bfs/dijkstra).
2. To know wheter an **edge/node is part of one of the shortest paths**: Apply weighted/unweighted from begining and again from end (reversed AL).
A node is part of a shortest path if `dist[node] + distRev[node] == dist[endNode]`, analogously an edge is part of a shortest path if both connected nodes are part of the shortest path + the difference in between both `dist` values is the weight of the edge `w`.


