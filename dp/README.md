# Dynamic Programming

Requirement:
1. **Optimal Substructure**: You can break down the given problem into a smaller subproblem; This then needs to be solved optimal.
2. **Overlapping SubProblems**: The main advantage (over Backtracking) is that DP saves sates and therfore we do not need to recalculate subproblems.


Variants:
1. **Top-Down**:
    - Pro: natural way of thinking (like Backtracking)
    - Pro: A subproblem will only be computed when needed
    - Con: Slower than Bottom-up when we need all subproblems
2. **Bottom-Up**:
    - Pro: Faster when all subproblems are needed
    - Pro: Memory saving technique (get rid of one Dimension)
    - Con: Also not needed states will be computed


Syntactic sugar for Top-Down pattern:
```
int dp(int state1, state2){
  // check base cases
  int &ans = memo[state1][state2];
  if(ans != 0) return ans;
  // else ... ans = ...
}
```

## Classical Types:

- **Kadane and Prefix-Sums**
  1. **1D-Sum**
  Given an Array A, find the subarray (continues elements), which summed up will lead to the maximal possible number.
  The naive Approach would try all O(n^2) possibilites.
  Kadane only needs a linear scan O(n): We sum up a current counter (`curSum`) and each time it falls below 0, we reset to 0, as now its better to start again.
  Note, this is bottom-up DP but with dimension-reduction. You could also have an array `dp` of lenght n, in which `dp[i]` stands for the best result up to index i.
  ```
  int curSum = 0, overallSum =0;
  for(int i=0; i<n; ++i){
      curSum += nums[i];
      curSum = max(curSum, 0);
      overallSum = max(overallSum, curSum);
  }
  ```
    
  2. **2D-Sum or ND-Sum** 1D-Sum can be expanded to 2D-Sum or even further. To do so, calculate prefix sum for all dimensions but the last.
     Now, for all possible field sizes of the first n-1 dimensions, calculate a separate Kadane within the last dimension.
     For example, for the 2D-Sum, precalculate the prefixsum for each row and then Kadane for each colum combination over the rows.
     For 2D you get the **maximal sum of a submatrix** in O(n^3). This submatrix is of **variable size**.
     If we would instead precalculate **2D prefix-sum**, we would end up with O(n^4), as for each cell we still need to investigate O(n^2) potential submatrices.
     However, sometimes the **window-size is fixed**, we don't need need kadane and can check the few possible windows with 2D prefix-sum. 
     Don't forget the **inclusion-exclusion-principle** when calculating 2D prefix-sums.
     
     **2D-sum Kadane** O(n*m), maximal sum of submatrix of any size:
     ```
     // calculate prefix sum for each row
     for(int i=0; i<n; ++i){
         int rowSum = 0;
         for(int j=0; j<m; ++j){
            rowSum += grid[i][j];
            grid[i][j] = rowSum;
         }
     }
     for(int left_col =0; left_col<m; ++left_col){
          for(int right_col =i; right_col<m; ++right_col){
              // do Kadana over rows:
              int curSum = 0;
              int overallSum = 0;
              for(int i=0; i<n; ++i){
                  if(l>0){
                      curSum += grid[i][right_col] - grid[i][left_col-1];
                  }else{
                      curSum += grid[i][right_col];
                  }
              }
              curSum = max(curSum, 0);
              overallSum = max(overallSum, curSum);
          }
     }
     ```
     **2D Prefix-Sum** better for fixed window sized or as requirement to do 3D Kadane:
     ```
     for(int i=0; i<n; ++i){
        int rowSum = 0;
        for(int j=0; j<m; ++j){
            rowSum += grid[i][j];
            grid[i][j] = rowSum;
            if(i>0){
                grid[i][j] += grid[i-1][j];
            }
        }
     }
     ```
- **Longest Increasing Subsequence** (LIS)

    Let A be an array of integers. The LIS can be found with **DP** in <img src="https://render.githubusercontent.com/render/math?math=O(n^2)">. <br/>
    dp[i] := The length of the longest increasing subsequence, which is ending on i.
    ```
    int dp[n];
    memset(dp, 1, sizeof dp);
    for(int i=0; i<n; ++i){
        for(int j=0; j<i; ++j){
            if(A[j]<A[i]){
                dp[i] = max(dp[i], dp[j]);
            }
        }
    }
    ```
    Often better solution: **Greedy + Divide & Conquer** in <img src="https://render.githubusercontent.com/render/math?math=O(n \log k)">, where k is the length of the LIS.
    ```
    vector<int> LIS(n), par(-1, n), LIS_id(n);
    int k=0, idxEnd=0;
    for(int i=0; i<n; ++i){
        int pos = lower_bound(LIS.begin(), LIS.begin()+k, A[i]) - LIS.begin();
        if(pos == k){
            k++;
            idxEnd = i;
        }
        LIS[pos] = A[i];
        LIS_id[pos] = i; // only as help for the parent vector par
        if(pos > 0){
            par[i] = LIS_id[pos - 1];
        }
    }

    vector<int> ret; // ret contains the LIS (but reversed)
    for(int i=0; i<k; ++k){
        ret.push_back(A[idxEnd]);
        idxEnd = par[idxEnd];
    }
    ```
    Note:
    - Use `upper_bound` instead of `lower_bound` if **not strictly increasing**. Then you will replace the first larger element with you current element and not the same element
    - **LDS** (decreasing version) can be computed in two ways:
      - Reverse the Array A and then do LIS
      - Change the way you compare: `int pos = lower_bound(LIS.begin(), LIS.begin()+k, A[i], ::greater<int>()) - LIS.begin();` This will give the first element in LDS, which is equal or smaller. Recap, in LDS, you want to keep the values large as long (and early) as possible, such that you have more chances to add new elements.
    - Sometimes the **greedy version is not possible**. For example in [UVa11790 - Muricia's Skyline](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=2890), you want the max. Number of increasing buildings, but you measure with the **width**.  Then you can greedily exchange a taller building with a smaller one, because the taller might be more useful in terms of weights.
    - Often there are **2D LIS**, like in [UVa_01196 - Tiling Up Blocks](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=3637), [kattis - manhattanmornings](https://open.kattis.com/problems/manhattanmornings) or [kattis - nesteddolls](https://open.kattis.com/problems/nesteddolls). The basic idea here is **sort** the elements in **ascending order for the first dimension** and then for **the second**. If the requirment is given, that the LIS needs to be strictly increasing, then the second dimension needs to be sorted descending (you don't want that theses are building on top of each other). When you now go through the elements, then you know, that all preprocessed have a lower first dimension and you don't need to worry about that. Only you need to LIS in the second dimension.
- **Knapsack or Subset Sum**

  Pseudo-polynomial DP solution in <img src="https://render.githubusercontent.com/render/math?math=O(nw)">, where n is the number of items and w the maximal capacity of the backpack. `dp[i][j]` then describes the **maximal value** you can get **after** you have processed the **first i items and using j weight**. **Boolean Subset-Sum** vie: Is there a subset of a set of numbers, which sumed up is equal to a given value t?
  
  Note: 
    - You can often **reduce the first dimension**. 
      However, if you need to **reconstruct the actual solution**, then, you need it, as you have to backtrack throught the table.
      Recap, that you then need, to go from right to left, in order to not double count.
    - **Infinit Knapsack**. When each element can be used infinite times, than just for each item, go from left to right `dp[j] = max(dp[j], dp[j-w]+v)`.
    - Restricted Usage. If you can only use m<=n items, add an additonal state


  **Standard Subset-Sum**

  ```
  vector<vector<int>> dp(n+1, vector<int>(c+1, 0));
  vector<pii> nums;      
  for(int i=1; i<=n; ++i){
      int v = nums[i-1].first;
      int w = nums[i-1].second;
      for(int j=c; j>=0; j--){
          dp[i][j] = dp[i-1][j]; // might be optimal to skip current
          if(j>=w){
              dp[i][j] = max(dp[i-1][j], dp[i-1][j-w] + v); // or take it
          }
      }
  }
  ```
  **Reconstruct solution**:
  ```
  vector<int> dp_get_solution(int weight, int value, vector<vector<int>> &dp, vector<pii> &nums){
  // check for each number if it has been taken
    vector<int> ret;
    for(int i=n; i>0; --i){
        if(weight >= nums[i-1].second && ((dp[i-1][weight - nums[i-1].second] + nums[i-1].first)   ==  dp[i][weight])){
            ret.push_back(i-1);
            weight -=  nums[i-1].second;
        }

    }
    return ret;
  ```
- **Coin Change**

  Very similar to Knapsack, but instead of maximising the value, we want either **minimise the used coins** or we want to **count the possiblities** to give a certain amount in different coins. <br/>
  **Minimise Used Coins:** <br/>
  `dp[i][j]` denotes the min. number of coins used to get to the values j by using up to the first i coins. Set the dp to 0 and only set `dp[0][0] = 1`. <br/>
  **Count the possibities:** <br/>
  `dp[i][j]` denotes the number of possibilities to give the values j by using up to the first i coins. Set the dp to INF and only set `dp[0][0] = 0`. Then just add up possibilities. <br/>
        




