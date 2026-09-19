# Topic 17: Dynamic Programming (1D, 2D, Knapsack, LCS, LIS, MCM, & State Machines)

## 1. Overview & Core Philosophy

**Dynamic Programming (DP)** is an algorithmic technique for solving optimization problems by breaking them down into simpler overlapping subproblems and storing subproblem results to avoid redundant recomputations.

### Two Mandatory Properties:
1. **Optimal Substructure**: The optimal solution to the problem contains within it optimal solutions to its subproblems.
2. **Overlapping Subproblems**: The same subproblems are solved repeatedly during naive recursion.

---

## 2. Top-Down (Memoization) vs. Bottom-Up (Tabulation)

| Aspect | Top-Down (Memoization) | Bottom-Up (Tabulation) |
| :--- | :--- | :--- |
| **Approach** | Starts at original problem, breaks into subproblems via recursion. | Starts at base cases and builds upward iteratively. |
| **Storage** | Hash table or lookup array + Call stack. | DP table (1D, 2D, or space-optimized variables). |
| **Overhead** | Function recursion call-stack overhead. | No recursion overhead; faster execution. |
| **Subproblem Coverage** | Computes only states required for final answer. | Computes all states systematically. |

---

## 3. Canonical DP Archetypes & Patterns

### 1. 1D Array Transition
- **Examples**: Climbing Stairs, House Robber, Decode Ways, Coin Change.
- **State**: `dp[i]` = optimal answer for prefix of length $i$.
- **Space Optimization**: When `dp[i]` depends only on `dp[i-1]` and `dp[i-2]`, reduce space from $O(N)$ to $O(1)$!

### 2. 2D / Grid Path DP
- **Examples**: Unique Paths, Minimum Path Sum, Dungeon Game.
- **State**: `dp[r][c]` = cost or count reaching cell $(r, c)$.
- **Transition**: `dp[r][c] = cost[r][c] + min(dp[r-1][c], dp[r][c-1])`.
- **Space Optimization**: Can be reduced to a single 1D array of size $O(C)$ using rolling updates.

### 3. Knapsack Family
- **0/1 Knapsack**: Each item can be picked at most once. Iterate backwards on capacity to reuse previous state in 1D array:
  $$\text{dp}[w] = \max(\text{dp}[w], \text{val}[i] + \text{dp}[w - \text{weight}[i]])$$
- **Unbounded Knapsack**: Each item can be picked arbitrarily many times. Iterate forwards on capacity.

### 4. String Match / Longest Common Subsequence (LCS)
- **Examples**: LCS, Edit Distance, Distinct Subsequences, Interleaving String.
- **State**: `dp[i][j]` considers prefixes `s1[0..i-1]` and `s2[0..j-1]`.
- **Match**: `dp[i][j] = 1 + dp[i-1][j-1]` if characters match.

### 5. Longest Increasing Subsequence (LIS)
- Standard DP: $O(N^2)$.
- Patience Sorting + Binary Search: $O(N \log N)$ maintaining tails of increasing subsequences.

### 6. Interval / Matrix Chain Multiplication (MCM)
- **Examples**: Burst Balloons, Palindrome Partitioning II, Minimum Cost Tree From Leaf Values.
- **State**: `dp[i][j]` = optimal cost to solve subproblem for range $[i, j]$.
- **Transition**: Loop over range length $L$, then left boundary $i$, then split point $k \in [i, j-1]$.

---

## 4. Directory Structure

```
17-dynamic-programming/
├── README.md
├── easy/
│   ├── 01_ClimbingStairsMemoAndTab.java
│   ├── 02_FibonacciNumberOptimized.java
│   ├── 03_MinCostClimbingStairs.java
│   ├── 04_TribonacciNumber.java
│   ├── 05_HouseRobberOneLinear.java
│   ├── 06_PascalsTriangleGenerate.java
│   ├── 07_DivisorGameMathAndDP.java
│   ├── 08_CountingBitsDP.java
│   ├── 09_BestTimeToBuySellStockOne.java
│   └── 10_MaximumSubarrayKadaneDP.java
├── medium/
│   ├── 01_CoinChangeMinimumCoins.java
│   ├── 02_LongestIncreasingSubsequence.java
│   ├── 03_LongestCommonSubsequence.java
│   ├── 04_PartitionEqualSubsetSum.java
│   ├── 05_UniquePathsGridDP.java
│   ├── 06_MinimumPathSumGrid.java
│   ├── 07_HouseRobberTwoCircular.java
│   ├── 08_WordBreakDP.java
│   ├── 09_DecodeWaysDP.java
│   └── 10_TargetSumDP.java
└── hard/
    ├── 01_EditDistanceLevenshtein.java
    ├── 02_TrappingRainWaterDP.java
    ├── 03_BurstBalloonsMCMIntervalDP.java
    ├── 04_RegularExpressionMatchingDP.java
    ├── 05_DungeonGameKnightMinHealth.java
    ├── 06_BestTimeToBuySellStockFourKTransactions.java
    ├── 07_PalindromePartitioningTwoMinCuts.java
    └── 08_DistinctSubsequencesDP.java
```
