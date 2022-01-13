## Order Statistic Tree
Order Statistic Tree (OST) is a balanced BST, which also saves the size of each subtree. 
This datastructure can be used to answer order-related queries like "what it the k-th smallest elment?" on dynammic data in log(n) time (as we have to find the specific node first in log(n).

An alternative to OST is a Fenwick Tree, as implemented [here](https://www.geeksforgeeks.org/order-statistic-tree-using-fenwick-tree-bit/). 
However, this only works for finding the order of indices (small integers), while the OST implemented as a balanced Red–black tree can take any type with smaller-comperator.

