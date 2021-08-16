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


Symantic-sugar for Top-Down pattern:
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


