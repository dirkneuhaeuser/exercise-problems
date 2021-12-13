## Minimum Spanning Tree (MST)
There are two well known algorithms for the MST, **Krusal**, which uses the **disjoint-set datastructure**, and **prim's** algorithm, which works similarly to
dijkstra's SSSP. 
The difference is that dijsktra looks at nodes and minimises the distance from a given starting node to it,
while prime just takes the next lowes edge which endpoint has not been seen yet. Both algorithm work in
<img src="https://render.githubusercontent.com/render/math?math=O(E \log E)">.

### Kruskal DJS
```
class DJS{ // O(E Log E)
public:
    vector<int> rank, par;
    int forrests;
    DJS(int n){
        par = vector<int>(n, 0);
        for(int i=0; i<n; ++i)par[i] = i;
        forrests = n;
        rank.assign(n, 1);
    }
    int getPar(int x){
        if(par[x] == x) return x;
        return par[x] = getPar(par[x]);
    }
    bool isSame(int x, int y){
        return getPar(x) == getPar(y);
    }
    bool unionfy(int x, int y){
        if(isSame(x, y)) return false;
        forrests--;
        int px = getPar(x), py = getPar(y);
        if(rank[px] < rank[py]){
            swap(px, py);
        }
        par[py] = px;
        rank[px] += rank[py];
        return true;
    }
};
// in main;
vector<tiii> edges; // add all edges
sort(edges.begin(), edges.end());
DJS djs(n);
long long ret = 0;
for(int j=0; j<edges.size(); ++j){
  auto [cost, a, b] = edges[i];
  if(djs.unionfy(a, b)){
    ret += cost;
  }
}
```

To check whether a spanntree exist, check that `djs.forrests == 1`.

### Prim
```
int startIdx = 0;
priority_queue<pii, vector<pii>, greater<pii>> pq
pq.push({0, startIdx});
vector<bool> seen(n, false)
long long ret = 0;
while(pq.size()){
  auto [tCost, tIdx] = pq.top(); pq.pop();
  if(seen[tIdx]) continue;
  ret += tCost;
  for(auto [next, w]: AL[tIdx]){
    if(seen[next] == false){
      pq.push({w, next});
    }
  }
}
```
### When to use:
Per default use DJS
- Minimum/Maximum Spanning Tree
- Minimum Spanning **Subgraph** (part of the edges are already given)
- **Minimum Spanning Forrest** (stop when `djs.forrests == k`)
- **MiniMax** (Connect all nodes and try to minimise the maximum edge weight used for that). Vice verca for MaxiMin. The result is given just by the MST
- **Second Best Spanning Tree**. (run normal MST, then you have n edges.
  For each of theses edges run MST again and don't include it) O(sorting + MST + Second Best MST) = <img src="https://render.githubusercontent.com/render/math?math=O(E log E %2B E %2B VE)">.
  Alternatively if E is huge, calculate the MST and get the minimal cost. Then for each v run a dfs and get the maximum distance between any two nodes in <img src="https://render.githubusercontent.com/render/math?math=O(V^2)">. 
  Now just pass though all edges which are not part of the MST. Add its weight and subtract the maximum distance between these two nodes within the orginal MST (See kattis spider).
- When there are **several starting points**, use **Prim**'s Algorithm (aksed for optimal forrests here)
