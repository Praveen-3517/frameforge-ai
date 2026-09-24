# Recursion & Backtracking Algorithms in C

> State space exploration, N-Queens, Sudoku solver, Rat in a Maze, subsets, permutations, and tree pruning techniques.

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
| 1 | **PrintAllSubsequencesString** | [`easy/01_PrintAllSubsequencesString.c`](./easy/01_PrintAllSubsequencesString.c) | Foundational logic, boundary checks |
| 2 | **BinaryWatchCombinations** | [`easy/02_BinaryWatchCombinations.c`](./easy/02_BinaryWatchCombinations.c) | Foundational logic, boundary checks |
| 3 | **FactorialAndFibonacciMemoized** | [`easy/03_FactorialAndFibonacciMemoized.c`](./easy/03_FactorialAndFibonacciMemoized.c) | Foundational logic, boundary checks |
| 4 | **SumOfSubsetsEqualsTarget** | [`easy/04_SumOfSubsetsEqualsTarget.c`](./easy/04_SumOfSubsetsEqualsTarget.c) | Foundational logic, boundary checks |
| 5 | **GenerateAllBinaryStringsLengthN** | [`easy/05_GenerateAllBinaryStringsLengthN.c`](./easy/05_GenerateAllBinaryStringsLengthN.c) | Foundational logic, boundary checks |
| 6 | **CountPathsInGridSimpleRecursion** | [`easy/06_CountPathsInGridSimpleRecursion.c`](./easy/06_CountPathsInGridSimpleRecursion.c) | Foundational logic, boundary checks |
| 7 | **ReverseStringRecursively** | [`easy/07_ReverseStringRecursively.c`](./easy/07_ReverseStringRecursively.c) | Foundational logic, boundary checks |
| 8 | **RecursivelyCheckPalindrome** | [`easy/08_RecursivelyCheckPalindrome.c`](./easy/08_RecursivelyCheckPalindrome.c) | Foundational logic, boundary checks |
| 9 | **CombinationsOfSizeK** | [`easy/09_CombinationsOfSizeK.c`](./easy/09_CombinationsOfSizeK.c) | Foundational logic, boundary checks |
| 10 | **ClimbingStairsWaysRecursion** | [`easy/10_ClimbingStairsWaysRecursion.c`](./easy/10_ClimbingStairsWaysRecursion.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **SubsetsTwoWithDuplicates** | [`medium/01_SubsetsTwoWithDuplicates.c`](./medium/01_SubsetsTwoWithDuplicates.c) | Optimal time/space, pointers, recursion |
| 2 | **CombinationSumTwoUnique** | [`medium/02_CombinationSumTwoUnique.c`](./medium/02_CombinationSumTwoUnique.c) | Optimal time/space, pointers, recursion |
| 3 | **CombinationSumThreeFixedK** | [`medium/03_CombinationSumThreeFixedK.c`](./medium/03_CombinationSumThreeFixedK.c) | Optimal time/space, pointers, recursion |
| 4 | **RatInAMazeAllPaths** | [`medium/04_RatInAMazeAllPaths.c`](./medium/04_RatInAMazeAllPaths.c) | Optimal time/space, pointers, recursion |
| 5 | **PalindromePartitioningAllCuts** | [`medium/05_PalindromePartitioningAllCuts.c`](./medium/05_PalindromePartitioningAllCuts.c) | Optimal time/space, pointers, recursion |
| 6 | **TargetSumExpressionWays** | [`medium/06_TargetSumExpressionWays.c`](./medium/06_TargetSumExpressionWays.c) | Optimal time/space, pointers, recursion |
| 7 | **PartitionToKEqualSumSubsets** | [`medium/07_PartitionToKEqualSumSubsets.c`](./medium/07_PartitionToKEqualSumSubsets.c) | Optimal time/space, pointers, recursion |
| 8 | **RestoreIPAddressesBacktracking** | [`medium/08_RestoreIPAddressesBacktracking.c`](./medium/08_RestoreIPAddressesBacktracking.c) | Optimal time/space, pointers, recursion |
| 9 | **BeautifulArrangementBacktracking** | [`medium/09_BeautifulArrangementBacktracking.c`](./medium/09_BeautifulArrangementBacktracking.c) | Optimal time/space, pointers, recursion |
| 10 | **KnightTourProblemWarnsdorff** | [`medium/10_KnightTourProblemWarnsdorff.c`](./medium/10_KnightTourProblemWarnsdorff.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **WordSearchTwoTrieBacktracking** | [`hard/01_WordSearchTwoTrieBacktracking.c`](./hard/01_WordSearchTwoTrieBacktracking.c) | Complex invariants, state trees, low-level bits |
| 2 | **NQueensTwoDistinctSolutionsCount** | [`hard/02_NQueensTwoDistinctSolutionsCount.c`](./hard/02_NQueensTwoDistinctSolutionsCount.c) | Complex invariants, state trees, low-level bits |
| 3 | **SudokuSolverBitmaskOptimized** | [`hard/03_SudokuSolverBitmaskOptimized.c`](./hard/03_SudokuSolverBitmaskOptimized.c) | Complex invariants, state trees, low-level bits |
| 4 | **MColoringGraphBacktracking** | [`hard/04_MColoringGraphBacktracking.c`](./hard/04_MColoringGraphBacktracking.c) | Complex invariants, state trees, low-level bits |
| 5 | **HamiltonianCycleBacktracking** | [`hard/05_HamiltonianCycleBacktracking.c`](./hard/05_HamiltonianCycleBacktracking.c) | Complex invariants, state trees, low-level bits |
| 6 | **OptimalAccountBalancingDebt** | [`hard/06_OptimalAccountBalancingDebt.c`](./hard/06_OptimalAccountBalancingDebt.c) | Complex invariants, state trees, low-level bits |
| 7 | **WordBreakTwoSentenceGeneration** | [`hard/07_WordBreakTwoSentenceGeneration.c`](./hard/07_WordBreakTwoSentenceGeneration.c) | Complex invariants, state trees, low-level bits |
| 8 | **RemoveInvalidParenthesesBFSDFS** | [`hard/08_RemoveInvalidParenthesesBFSDFS.c`](./hard/08_RemoveInvalidParenthesesBFSDFS.c) | Complex invariants, state trees, low-level bits |

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
