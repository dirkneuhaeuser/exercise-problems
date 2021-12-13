## Eulerian Path

A graph has an **Euler Path**, if it is possible to start at an arbitrary node and then **traverse through each edge exactly once**.
Analoguousely, an Euler tour needs to start and end at the same vertex.

### Requirements Undirected Graph.
1. Graph is **connected**
2. Each vertex has an **even edge-degree** (tour). For a euler path two vertices may have an odd degree.

### Requirements Directed Graph.
1. Graph is **connected** (No need for strongly connection. Pretend the graph is undirected and check for connection, this is enough together with condition 2)
2. For each vertex `i` holds `inDegree[i] == outDegree[i]`. For an euler path, the endnode may have `inDegree[i] +1 == outDegree[i]`, together with `inDegree[i] == outDegree[i]+1` for the start node.

### Hierholzer Algorithm 
After checking the above requirements, **Hierholzer-algorithm** finds a possible euler-path. It runs in  <img src="https://render.githubusercontent.com/render/math?math=O(E)"> and works in a post-order fashion.
Therefore, the result needs to be **reversed** eventually. Note the gloabl `idx` array to memorise the progress for each node. 

```
vector<int> hierholzer(int s, vector<vector<int>> &AL){
    // Finds the euler path within a graph in O(E).
    // The algorithm passes through the graph rather arbitrarily. 
    // Idea: If you start u and at some point come back to u, you either have each edge passed (save the progress in vi idx) or you can still have another detour starting from u.
    // With the stack you have this kind of post-order (similar to topological sort) -> REVERSE the result
    vector<int> ret, stack, idx(AL.size(), 0);
    stack.push_back(s);
    while(stack.size()){
        int cur = stack.back();
        if(idx[cur] < AL[cur].size()){
            stack.push_back(AL[cur][idx[cur]]);
            idx[cur]++;
        }else{
            int justFinishedCycle = stack.back(); stack.pop_back();
            ret.push_back(justFinishedCycle);
        }
    }
    return ret; // needs to be reversed.
}

```
