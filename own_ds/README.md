## ST
Often it is sufficient to use BIT, but if the operation is not inversable like max or min, or when the states are a bit more complicated then we can still use a ST. A ST uses slightly more memory, and implementationwise a bit more sophisicated.
With Lazy Propagation we can go for efficient (log n) range updates as well.

### 2D ST
When we have 2 Dimensions and each node of the first dimension contains another ST. The implementaion is a bit tedious and also we cannot use lazy propagation thus only have point-updates at our disposal


## BIT or Fenwick-Tree
Very good for point update and range queries (PURQ), operation needs to be inversable (sum). Can be used for orders, but often OST is better.
Some more sophiscated variants allow also for range update and point queries (RUPQ) as well as range update and range queries (RURQ)

### 2D BIT
2D Bit allows for point update and range queries (PURQ) and is implemented quickly.

## Order Statistic Tree
Order Statistic Tree (OST) is a balanced BST, which also saves the size of each subtree. 
This datastructure can be used to answer order-related queries like "what it the k-th smallest elment?" on dynammic data in log(n) time (as we have to find the specific node first in log(n).

An alternative to OST is a Fenwick Tree, as implemented [here](https://www.geeksforgeeks.org/order-statistic-tree-using-fenwick-tree-bit/). 
However, this only works for finding the order of indices (small integers), while the OST implemented as a balanced Red–black tree can take any type with smaller-comperator.

When using it as a **multiset** (and allow the same value several times), we have to take the operator `less_equal`. However, this comes with some pitfalls as well:

`find` will always return end. </br>
`lower_bound` works like upper_bound in normal set (to return the first element > it)</br>
`upper_bound` works like lower_bound in normal set (to return the first element >= it)</br>
`order_of_key` will get you the first order of the key (even though this key might be available by many orders)</br>
`find_by_order` works as expected</br>
`erase` by value does not work anymore. Use `t.erase(t.upper_bound(1))`</br>