
## 2.1 Master-Theorem

The **Master-Theorem** provides a runtime analysis for **divide and conquer** algorithms and therefore is often found when travesing throug graphs.

<img src="https://render.githubusercontent.com/render/math?math=n \:\:\:\:\: "> is the input-size <br/>
<img src="https://render.githubusercontent.com/render/math?math=t(n)"> is the effor in the inner node (time to create subproblems, time to merge results of subproblems) <br/>
<img src="https://render.githubusercontent.com/render/math?math=a  \:\:\:\:\:"> is the number of subproblems in the recursion <br/> 
<img src="https://render.githubusercontent.com/render/math?math=b  \:\:\:\:\:"> is the factor by which the subproblem size is reduced in each recursive call 


<img src="https://render.githubusercontent.com/render/math?math=T(N) = aT(\frac{n}{b}) %2B t(n)">


The criterium is the **complexity of the subproblems** is now:  <img src="https://render.githubusercontent.com/render/math?math=\text{crit} = O(aT(\frac{n}{b})) = O(n^{\log_b(a)})"> <br/>

**Proof**: As The depth of the tree is given by <img src="https://render.githubusercontent.com/render/math?math=\log_b(n)"> and at depth i
there are <img src="https://render.githubusercontent.com/render/math?math=a^i"> subproblems. 
This means, there are <img src="https://render.githubusercontent.com/render/math?math=a^{\log_b(n)} = n^{\log_b(a)}"> leaves (log-law).
So, the overall complexit of the tree <img src="https://render.githubusercontent.com/render/math?math=O(n^{\log_b(a)})">.


There are three  possibilities:

1. Subproblems **dominate** the splitting and merging: <br/> 
    <img src="https://render.githubusercontent.com/render/math?math=t(n) = O(n^{\log_b(a)}) \rightarrow T(n) = O(n^{\log_b(a)})">
      
2. Subproblems are **comparabel** to splitting and merging, thus at each level, we add the complexity for<img src="https://render.githubusercontent.com/render/math?math=t(n)">:<br/> 
   <img src="https://render.githubusercontent.com/render/math?math=t(n) = \theta(n^{\log_b(a)}) \rightarrow T(n) = \theta(n^{\log_b(a)} \log_b(n))"> <br/>
   
3. Subproblems are **dominated** by spitting and merging: <br/>
   <img src="https://render.githubusercontent.com/render/math?math=t(n) = \omega(n^{\log_b(a)}) \rightarrow T(n) = \theta(t(n))"> <br/>
   

</br>
</br>
</br>
</br>
</br>
