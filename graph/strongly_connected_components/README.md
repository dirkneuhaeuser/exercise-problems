## Strongly Connected Components
On an undirected graph, the connected components can be found with an easy dfs. When the graph is **directed** however, we call a strongly connected component (SSC)
a subset of the vertexes in the graph, within **each vertex can reach each other vertex in the same SSC**. 
```
vector<int> dfs_num, dfs_low, dfs_stack, visited, root;
int dfs_idx;

void tarjan(int cur, vector<vector<int>> &AL){
    dfs_num[cur] = dfs_low[cur] = dfs_idx++;
    dfs_stack.push_back(cur);
    visited[cur] = 1;
    for(int next: AL[cur]){
        if(dfs_num[next] == UNVISITED){
            tarjan(next, AL);
        }
        if(visited[next] == 1){
            dfs_low[cur] = min(dfs_low[next], dfs_low[cur]); // if it is not yet completed;
        }
    }
    if(dfs_low[cur] == dfs_num[cur]){
        // cur is start of a ssp;
        while(true){
            int last = dfs_stack.back(); dfs_stack.pop_back();
            root[last] = cur;
            visited[last] = 0;
            if(last == cur) break;
        }
    }

}
// in main:
dfs_num.assign(n, UNVISITED);
dfs_low.assign(n, UNVISITED);
visited.assign(n, false);
root.assign(n, UNVISITED);
dfs_stack.clear();
dfs_idx=0;
FOR(i, n){
    if(dfs_num[i] == UNVISITED){
        tarjan(i, AL);
    }
}
```
Often, a task is to reduce all SSC to single node and
afterwards check for some critera (e.g. count all `in_degree == 0` nodes).
