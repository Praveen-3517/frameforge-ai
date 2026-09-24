# Dynamic Programming & Optimization in C

> 1D and 2D dynamic programming, 0/1 Knapsack, Longest Common Subsequence, Longest Increasing Subsequence, Edit Distance, and Matrix Chain Multiplication.

---

## 📌 Architectural Overview & C Systems Principles

In C, data structures and algorithms execute directly against physical memory without JVM bytecode, garbage collection overhead, or object headers. Understanding:
1. **Memory Layout**: Stack (automatic allocation, rapid cache hits) vs Heap (`malloc`/`free`, dynamic sizing).
2. **Pointer Semantics**: Explicit address-of (`&`), dereference (`*`), and pointer arithmetic (`*(ptr + i)`).
3. **Data Alignment & Padding**: Hardware alignment requirements and struct padding for CPU bus efficiency.
4. **Cache Locality**: Contiguous arrays maximizing L1/L2 data cache line utilization.

---

## 🗂️ Problem Directory & Difficulty Breakdown

### 🟢 Easy Tier (Foundational & Core Syntax)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **ClimbingStairsMemoAndTab** | [`easy/01_ClimbingStairsMemoAndTab.c`](./easy/01_ClimbingStairsMemoAndTab.c) | Foundational logic, boundary checks |
| 2 | **FibonacciNumberOptimized** | [`easy/02_FibonacciNumberOptimized.c`](./easy/02_FibonacciNumberOptimized.c) | Foundational logic, boundary checks |
| 3 | **MinCostClimbingStairs** | [`easy/03_MinCostClimbingStairs.c`](./easy/03_MinCostClimbingStairs.c) | Foundational logic, boundary checks |
| 4 | **TribonacciNumber** | [`easy/04_TribonacciNumber.c`](./easy/04_TribonacciNumber.c) | Foundational logic, boundary checks |
| 5 | **HouseRobberOneLinear** | [`easy/05_HouseRobberOneLinear.c`](./easy/05_HouseRobberOneLinear.c) | Foundational logic, boundary checks |
| 6 | **PascalsTriangleGenerate** | [`easy/06_PascalsTriangleGenerate.c`](./easy/06_PascalsTriangleGenerate.c) | Foundational logic, boundary checks |
| 7 | **DivisorGameMathAndDP** | [`easy/07_DivisorGameMathAndDP.c`](./easy/07_DivisorGameMathAndDP.c) | Foundational logic, boundary checks |
| 8 | **CountingBitsDP** | [`easy/08_CountingBitsDP.c`](./easy/08_CountingBitsDP.c) | Foundational logic, boundary checks |
| 9 | **BestTimeToBuySellStockOne** | [`easy/09_BestTimeToBuySellStockOne.c`](./easy/09_BestTimeToBuySellStockOne.c) | Foundational logic, boundary checks |
| 10 | **MaximumSubarrayKadaneDP** | [`easy/10_MaximumSubarrayKadaneDP.c`](./easy/10_MaximumSubarrayKadaneDP.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **CoinChangeMinimumCoins** | [`medium/01_CoinChangeMinimumCoins.c`](./medium/01_CoinChangeMinimumCoins.c) | Optimal time/space, pointers, recursion |
| 2 | **LongestIncreasingSubsequence** | [`medium/02_LongestIncreasingSubsequence.c`](./medium/02_LongestIncreasingSubsequence.c) | Optimal time/space, pointers, recursion |
| 3 | **LongestCommonSubsequence** | [`medium/03_LongestCommonSubsequence.c`](./medium/03_LongestCommonSubsequence.c) | Optimal time/space, pointers, recursion |
| 4 | **PartitionEqualSubsetSum** | [`medium/04_PartitionEqualSubsetSum.c`](./medium/04_PartitionEqualSubsetSum.c) | Optimal time/space, pointers, recursion |
| 5 | **UniquePathsGridDP** | [`medium/05_UniquePathsGridDP.c`](./medium/05_UniquePathsGridDP.c) | Optimal time/space, pointers, recursion |
| 6 | **MinimumPathSumGrid** | [`medium/06_MinimumPathSumGrid.c`](./medium/06_MinimumPathSumGrid.c) | Optimal time/space, pointers, recursion |
| 7 | **HouseRobberTwoCircular** | [`medium/07_HouseRobberTwoCircular.c`](./medium/07_HouseRobberTwoCircular.c) | Optimal time/space, pointers, recursion |
| 8 | **WordBreakDP** | [`medium/08_WordBreakDP.c`](./medium/08_WordBreakDP.c) | Optimal time/space, pointers, recursion |
| 9 | **DecodeWaysDP** | [`medium/09_DecodeWaysDP.c`](./medium/09_DecodeWaysDP.c) | Optimal time/space, pointers, recursion |
| 10 | **TargetSumDP** | [`medium/10_TargetSumDP.c`](./medium/10_TargetSumDP.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **EditDistanceLevenshtein** | [`hard/01_EditDistanceLevenshtein.c`](./hard/01_EditDistanceLevenshtein.c) | Complex invariants, state trees, low-level bits |
| 2 | **TrappingRainWaterDP** | [`hard/02_TrappingRainWaterDP.c`](./hard/02_TrappingRainWaterDP.c) | Complex invariants, state trees, low-level bits |
| 3 | **BurstBalloonsMCMIntervalDP** | [`hard/03_BurstBalloonsMCMIntervalDP.c`](./hard/03_BurstBalloonsMCMIntervalDP.c) | Complex invariants, state trees, low-level bits |
| 4 | **RegularExpressionMatchingDP** | [`hard/04_RegularExpressionMatchingDP.c`](./hard/04_RegularExpressionMatchingDP.c) | Complex invariants, state trees, low-level bits |
| 5 | **DungeonGameKnightMinHealth** | [`hard/05_DungeonGameKnightMinHealth.c`](./hard/05_DungeonGameKnightMinHealth.c) | Complex invariants, state trees, low-level bits |
| 6 | **BestTimeToBuySellStockFourKTransactions** | [`hard/06_BestTimeToBuySellStockFourKTransactions.c`](./hard/06_BestTimeToBuySellStockFourKTransactions.c) | Complex invariants, state trees, low-level bits |
| 7 | **PalindromePartitioningTwoMinCuts** | [`hard/07_PalindromePartitioningTwoMinCuts.c`](./hard/07_PalindromePartitioningTwoMinCuts.c) | Complex invariants, state trees, low-level bits |
| 8 | **DistinctSubsequencesDP** | [`hard/08_DistinctSubsequencesDP.c`](./hard/08_DistinctSubsequencesDP.c) | Complex invariants, state trees, low-level bits |

---

## 🛠️ Compilation & Memory Verification

```bash
# Standard compilation with C11 and strict warnings
gcc -std=c11 -Wall -Wextra -O2 easy/01_ProblemName.c -o solution
./solution

# Memory leak verification with AddressSanitizer
gcc -std=c11 -Wall -Wextra -g -fsanitize=address easy/01_ProblemName.c -o solution
./solution
```
