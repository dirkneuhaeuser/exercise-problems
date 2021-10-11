## Toplogical Sort

Topological sort allows for sorting a list according to its dependencies (dependencies first).
Therefore we need an adjacency-list `a[v] = [..u..]` which means that 'v' comes befor all elments 'u' in the topological order.

### DFS Variant (post-order)
```
void topsort(int u, vector<int> &vis, vector<int> &order){
  vis[u] = VISITED;
  for(int next: al[u]){
    if(vis[next] == UNVISITED){
      topsort(next, vis, order);
    }
  }
  order.push_back(u);
}
// in main
for(int i=0; i<n; ++i){
  topsort(i, vis, order);
}
```
Here the `order` vector only needs to be **reversed** to contain the correct topological-order.

### Kahn Algorithm
The Kahn algorithm looks at the **in-degree** of each node `v`. If it is zero then this means, that no element needs to be before `v` and we can go ahead with it.
Note that Kahn algorithm is **more flexible**, as it allows us to change the order for all elemnts which have **in-degree = zero** at the same time.

```
priority_queue<int, vector<int>, ::greater<int>> pq; // maybe chose pair<int, int> for more flexible order
for(int i=0; i<n; ++i){
  if(in_degree[i] == 0){
    pq.push(i); 
  }
}
while(pq.size()){
  int cur = pq.top(); pq.pop();
  order.push_back(cur);
  for(int next: al[cur]){
    if(--in_degree[next] == 0){
      pq.push(next);
    }
  }
}
```
