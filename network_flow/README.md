# Network Flow / Max-Flow

Given a weighted directed graph as pipeline network, then </br>
**Edges**: Pipe with given capacity</br>
**Vertices**: Splitting point</br>
**2 Special vertices**: Source s and sink t</br>


**Question**: What is the max-flow/min-cut through the network from s to t?

## Set up the Residual-Graph

**Forward edge**: Normal directed edge as a given pipeline</br>
**Backward edge** (to cancel out incorrect forward flows): each backward edge has capacity 0 at the beginning, when choosing a forward edge,
then the forward edge has +flow, and its corresponding residual edge -flow</br>
**Residual Graph**: All edges in the network which still have flow < capacity </br>

## Maxflow Algorithms

1. Ford-Fulerson Method O(Maxflow * E): A potential bottleneck with capacity of 1 is used all the time (back and forth with forward and residual graph)
2. Edmonds-Karp Algorithm O(V * E^2)
3. **Dinic’s Algorithm** O(V^2 * E)
4. Push-Relabel Algorithm O(V^3), on dense graphs theoretically faster than Dinic, but Dinic is good enough for all Network problems.


Algorithm Edmonds-Karp and Dinic
Run BFS to create level graph:
  - The L-level Graph stops after L iterations
  - The Edmonds-Karp algorithm: uses this graph to only augment one s-t path (if found)
  - The Dinic algorithm: sends a blocking flow, to augment all possible s-t paths

Problems to solve with Network-Flow
Often Problem are disguised and the difficulty is to see the max-flow behind it and model it accordingly

## When to use
1. Normal **MaxFlow** problems (check max bandwith)
2. Unweighted Maximum Cardinality Bipartite Matching (**MCBM**, The easiest kind of matching)
3. **Assignment Problem** </br>
   Example: Emeis are thirsty between a and b, but at time x only 2 emeis can drink at a lake. Assign emeis to the lake.
4. **Min-cut** </br>
   Example: [kattis - thekingofthenorth](https://open.kattis.com/problems/thekingofthenorth). Defend your ground with as few soldiers as possible.
6. **Ad-hoc** problems


## Possible Difficulties: 

1. **Vertex Capacity** (add another node after that node and add edge with capacity)
2. **Back-Coupling** (time, add sum-up nodes for current and previous not used flows, see kattis_jupiter)
3. Blowing verteces up to consider **time**
4. **Extract** how many **edges** are used, or the flow within each edge (`get_used_forward_edges(node)` and `get_used_backward_edges(node)`); this is particular useful in assignment problems.
5. Get the **partition of the min_cut** (left and right side; for left side use (`getLeftMinCut(0)`): Do a dfs from sink and only pass through residual edges (not saturated edge)
6. Get **max. Independent Paths**: Each vertex can only be used once (use vertex capacity = 1), this implies disjoint paths.
7. Get **max. Disjoint Paths**: Use each edge only once. 

## Note

Often you need to work with many offsets. Better save them as a variable
```
MaxFlow maxFlow = MaxFlow(2 + sites + people);
int offsetSites = 1;
int offsetPeople = sites+1;
int sink = 2+sites+people -1;

// add edges...

long long flow = maxFlow.dinic(0, sink);
```
