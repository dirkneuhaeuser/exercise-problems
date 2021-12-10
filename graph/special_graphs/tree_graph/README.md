## Tree Graphs

A tree-graph of n nodes has n-1 edges and each node is directly or indirectly connected to any other node. 
Trees have some interesting properties:



### Diameter/Radius/Center
The **Diameter** of a (weighted) tree, is the longest shortest path between any two nodes. While the computation of longest shortest path in normal graph can be obtained
via Floyd-Warshall in <img src="https://render.githubusercontent.com/render/math?math=O(n^3)">, in trees it can be done in <img src="https://render.githubusercontent.com/render/math?math=O(n)">. The idea is to pick any random node `r`, from there go the furthest node `fst` of `r` and repeat 
that to find the furthest node `snd` from `fst`. The distance between `snd` and `fst` is the longest distance.

The diameter has either one center node, or the center lies on an edge. Either way, the center is defined to be on the half of the diameter (**radius**). 

### LCA and Binary Lifting
Given two nodes u and v, the **Least Common Ancestor** (LCA) is the first node, that lie on both pathes to the root, from u and also from v.
The <img src="https://render.githubusercontent.com/render/math?math=O(n)"> idea would be to precalculate the depth for each node in <img src="https://render.githubusercontent.com/render/math?math=O(n)">
and then to **bring u and v to the same depth** linearly. 
From there always go up to the root linearly, until both nodes are equal. However, when there are many queries, 
we can improve that to <img src="https://render.githubusercontent.com/render/math?math=O(\log(n))"> by utilising a <img src="https://render.githubusercontent.com/render/math?math=O(n \log(n))"> proprocessing, called **Binary Lifting**.
Therefore we define `up[u][i]` to be that node, that is <img src="https://render.githubusercontent.com/render/math?math=2^i"> higher than node u. That means, that `up[u][0]`(1 up) is the direct parent and `up[u][1]`(2 up) 
is the grandparent. Next `up[u][2]` would be 4 up and so on. By using this binary expansion, we can get to any arbitrary height.

**Binary Lifting**:
```
int LOG = 20; // 2^LOG should be the max depth
for(int j=1; j<=LOG; ++j){
    for(int i=0; i<n; ++i){
        up[i][j] = up[up[i][j-1]][j-1];
    }
}
```

With that, the idea of the LCA computation remains the same: First bring both nodes to the same level (via binary lifting) and then move both nodes up as 
much as possible while such that both nodes are not even. At the end of this routine, both nodes will be the direct children of the LCA:
```
int getLCA(int a, int b){
    if(depth[a] < depth[b]){
        swap(a, b);
    }
    // a is deeper;
    int dif = depth[a]-depth[b];
    for(int i=0; i<LOG; ++i){
        if(dif & (1 << i)){
            a = up[a][i];
        }
    }
    // edge-case:
    if(a == b) return a;
    // binary lifting to the predecessor of LCA
    for(int i=LOG-1; i>=0; --i){ // very important here to go from LOG-1 -> 0, as otherwise we cannnot do all jumps
        // for example the grand parent is two levels up. we cannot jump 1 and again 1...
        if(up[a][i] == up[b][i]) continue;
        a = up[a][i];
        b = up[b][i];
    }
    // return LCA
    return up[a][0];
}
```

