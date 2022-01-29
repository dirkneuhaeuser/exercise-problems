## Dynammic Datastructures

Until now, we have mainly seen static problems, so for example given an array of numbers, we need a quick way to calculate the sum from the index `i` to index `j` (prefix sum). When dealing with dynammic data, i. e. data which is modified continuously, we want to avoid to linearly recalculate the array.

### Binary-Index-Tree (BIT) or Fenwick-Tree
<img align="right" width="640" alt="Fenwick-Tree(https://ioinformatics.org/journal/v9_2015_39_44.pdf)" src="https://user-images.githubusercontent.com/44442845/151425400-974740f4-9141-4f2f-9a8c-3eadbb20840a.png">

A quick datastructure and in particular good for point update and range queries (PURQ). As a requirement, the operation needs to be inversable (sum): `range_query_from_left(j) - range_query_from_left(i-1);`. Given an array of length `n`, our datastructure has `n+1` nodes (0 is dummy variable) and each node `i` saves the result for the segment `[(i-LSOne(i) + 1),...,i]`. The building of the array needs <img src="https://render.githubusercontent.com/render/math?math=O(n \log n)">, and each update or sum query  <img src="https://render.githubusercontent.com/render/math?math=O(\log n)">.


```

// Least secnificant bit
#define LSOne(S) ((S) & -(S))


class PURQ {
private:
    vector<long long> ft;
public:
    PURQ(int n) { // without leading 0
        ft.assign(n+1, 0); // idx 0 is bound, no value asigned to it
    }
    PURQ(vi &vals){
        build(vals);
    }
    // builds in O(n), as oposed to O(n*logn)
    void build(vector<long long> vals){ // vals idx are keys of Fenwick-tree -> first in vector needs to be 0:
        int n = vals.size();
        ft.assign(n, 0);
        for(int i=0;i<n; i++){
            ft[i] += vals[i];
            if(i+LSOne(i)<n){
                ft[i+LSOne(i)] += ft[i];
            }
        }
    }
    // 1-based index
    long long range_query_from_left(int j){ // interval [1,...,j]
        assert(j>=0 && j < ft.size());
        long long ret = 0;
        while(j!=0){
            ret += ft[j];
            j-=LSOne(j);
        }
        return ret;
    }
    // 1-based index
    long long range_query(int i, int j){ // interval [i,...,j]
        assert(j>=i && j < ft.size());
        assert(i>=0 && i < ft.size());
        return range_query_from_left(j) - range_query_from_left(i-1);
    }
    // 1-based index
    void point_update(int i, int val){
        assert(i>0 && i < ft.size());
        while(i < ft.size()){
            ft[i]+=val;
            i += LSOne(i);
        }
    }
};

//vector<long long> test{0,1,1};
//PURQ fw = PURQ(test); 
//fw.range_query(1, 2);

```

Also note, that this data-structure also supports, Range-Updates with Point-Queries (RUPQ) as well as Range-Updates with Range-Queries (RURQ). The implementation is [here](https://github.com/dirkneuhaeuser/algorithms/blob/master/templates/fenwick.cpp). Moreover, we can also use it, for [2D-grids]([here](https://github.com/dirkneuhaeuser/algorithms/blob/master/templates/fenwick2D.cpp)), where we normally would use 2D Prefix-Sums or kadane.



Often n numbers, and q queries of 2 types. 
For the first type, we need to change the some range/point of our initial numbers. `update(idx, val)`. </br>
For the second type, we need to calculate the sum of a given range `query(idxLeft, idxRight)`. Note any associative function (it doesn't matter which operation is done first) can be used instad of the sum-operation, e.g. minimum, maximum, multiplication (also modulo), matrix-multiplication (associative but not commutative, e.g. multiplication form left and right are differnt), bitwise operations (`&`, `|`, `^`) or GCD (which doesn't run in O(1), so it will change the overall complexity).


## Order Statistic Tree
Order Statistic Tree (**OST**) is a balanced BST, which also saves the size of each subtree. 
This datastructure can be used to answer order-related queries like "what it the k-th smallest elment?" on dynammic data in  <img src="https://render.githubusercontent.com/render/math?math=O(\log n)"> time (as we have to find the specific node first in <img src="https://render.githubusercontent.com/render/math?math=O(\log n)">).

```
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <typename T>
using ost = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// To use ordered use ordered_multiset<type>S something like this

//int x=1;
//ost<ll> tree;
//tree.insert(x);
//ll low=tree.order_of_key(x); // this is not possible with normal multiset. There you must have use distance(s.begin(), iterator), which takes O(n);
//tree.lower_bound(x)
//ll secondSmallest = *tree.find_by_order(1); 
 ```

When using it as a **multiset** (and allow the same value several times), we have to take the operator `less_equal`. However, this comes with some pitfalls as well:

`find` will always return end. </br>
`lower_bound` works like upper_bound in normal set (to return the first element > it)</br>
`upper_bound` works like lower_bound in normal set (to return the first element >= it)</br>
`order_of_key(x)` will get you the order of the first key==x (even though this key might be available by many orders)</br>
`find_by_order(x)` works as expected</br>
`erase` by value does not work anymore. Use `t.erase(t.upper_bound(1))`</br>


Instead of using an OST, we could also rely on the **BIT/Fenwick** to to order-related queries. If we have an elment `a`, we just add +1 to it and now, we can query, the sum to a specific answer, getting the number of elements before it. However, **often an OST is prefable**, as it is not restricted to low numbers (roughly 1M), but its tree can have anthing which is sortable (e.g. strings).

## Segment-Tree 

Within a Segment-Tree (ST) the operatin does **not need to be inversable** and thus, a ST is more powerful than a BIT/Fenwick. Moreover, it is a good choice, when the operation and states are a bit more complicated. ST use slightly more memory (we need up to 4t imes the space of the initial array).
The idea is that each node within the ST is in charge of a segment `L` to `R`. When quering or updating, we give a range `i` to `j`, and we go down the tree, trying find nodes, which are fully captured by thins range and directly update or return.
With **Lazy Propagation** we can go for efficient (log n) range updates as well. The reasoning is, that ones we are at a node, which is fully captured, we set a lazy flag and stop here. Only the time, when we really need to go deeper, we will take this lazy-value and also compute the up-to-date values for the children.
Figuratively, we can say, that old operations are further down in the root tree, while new ones are up. Each time we visit a node, we **propagate it's lazy flag furhter down**. Take into consideration, that for the lazy propagation to work, you might need to **merge lazy-flags**, if the kid already has one.

When the states are more complicated it is useful to implement a `struct Node`. This also allows for defining `operator +`, such that we don't need to do this within our conq function inside the segment-tree. An example of how to implement a node to get the minimum and also the count of all the elements having this min is defined below:
```
struct Node{
    ll minN, cnt;
    Node(){
        minN = INF;
        cnt = 1;
    }
    Node operator+(const Node &o) const{
        if(minN > o.minN) return o;
        if(minN < o.minN) return *this;
        Node ret;
        ret.minN = minN;
        ret.cnt = cnt + o.cnt;
        return ret;
    }
};
```


To apply lazy-propagation, and stop at an inner node, the update function needs to distributive relative to the calc(query)function.
E.g. when applying the operation \* with x, we don't need to recurse to the children, but instead just use their old intermediate values: query(a\*x, b\*x) = query(a, b) \* x.

Distributive are: </br>
\* (update) and + (query) </br>
& and | </br>
\+ and max/min </br>
\:= and min </br>


Not distribute are: </br>
/+ and + </br>
:= and + </br>
but we can still do it, if we are smart within propagation

Normal implementation works with `NEUTRAL_UPDATE` and `NEUTRAL_QUERY`. However some operation, like assignment do not have a neutral, then, we need a dummy, or a value out of range.

Possibility of SparseSegment-Trees


## BIT or Fenwick-Tree
Very good for point update and range queries (PURQ), operation needs to be inversable (sum). Can be used for orders, but often OST is better.
Some more sophiscated variants allow also for range update and point queries (RUPQ) as well as range update and range queries (RURQ)

## 2D Data

### 2D BIT
2D Bit allows for point update and range queries (PURQ) and is implemented quickly.

### 2D ST
When we have 2 Dimensions and each node of the first dimension contains another ST. The implementaion is a bit tedious and also we cannot use lazy propagation thus only have point-updates at our disposal

### Quadtree
A quadtree is a tree, in which each inner node has 4 children. This helps to divide the 2D-grid recursively into north-east, north-west, south-easth and south-west, such that each node can dicide what to do with values of its children. Note that the runtime of the quadtree is worse than of a 2D-Segmenttree. Proof by Mastertheorem.


