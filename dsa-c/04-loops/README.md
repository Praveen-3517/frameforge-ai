# Iteration, Loops & Pattern Algorithms in C

> For, while, and do-while loops, loop unrolling for cache performance, nested pattern algorithms, and convergence series.

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
| 1 | **PrintNumberPatterns** | [`easy/01_PrintNumberPatterns.c`](./easy/01_PrintNumberPatterns.c) | Foundational logic, boundary checks |
| 2 | **ReverseNumberAndPalindrome** | [`easy/02_ReverseNumberAndPalindrome.c`](./easy/02_ReverseNumberAndPalindrome.c) | Foundational logic, boundary checks |
| 3 | **FibonacciSeriesUpToN** | [`easy/03_FibonacciSeriesUpToN.c`](./easy/03_FibonacciSeriesUpToN.c) | Foundational logic, boundary checks |
| 4 | **GCDAndLCMUsingEuclid** | [`easy/04_GCDAndLCMUsingEuclid.c`](./easy/04_GCDAndLCMUsingEuclid.c) | Foundational logic, boundary checks |
| 5 | **ArmstrongNumberChecker** | [`easy/05_ArmstrongNumberChecker.c`](./easy/05_ArmstrongNumberChecker.c) | Foundational logic, boundary checks |
| 6 | **LabeledBreakAndContinue** | [`easy/06_LabeledBreakAndContinue.c`](./easy/06_LabeledBreakAndContinue.c) | Foundational logic, boundary checks |
| 7 | **CountDigitsAndSumOfDigits** | [`easy/07_CountDigitsAndSumOfDigits.c`](./easy/07_CountDigitsAndSumOfDigits.c) | Foundational logic, boundary checks |
| 8 | **CollatzConjectureHailstone** | [`easy/08_CollatzConjectureHailstone.c`](./easy/08_CollatzConjectureHailstone.c) | Foundational logic, boundary checks |
| 9 | **MultiplicationTableGrid** | [`easy/09_MultiplicationTableGrid.c`](./easy/09_MultiplicationTableGrid.c) | Foundational logic, boundary checks |
| 10 | **DoWhileInputValidationSimulation** | [`easy/10_DoWhileInputValidationSimulation.c`](./easy/10_DoWhileInputValidationSimulation.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **SpiralMatrixTraversal** | [`medium/01_SpiralMatrixTraversal.c`](./medium/01_SpiralMatrixTraversal.c) | Optimal time/space, pointers, recursion |
| 2 | **SpiralMatrixTwoGeneration** | [`medium/02_SpiralMatrixTwoGeneration.c`](./medium/02_SpiralMatrixTwoGeneration.c) | Optimal time/space, pointers, recursion |
| 3 | **PascalsTriangleGeneration** | [`medium/03_PascalsTriangleGeneration.c`](./medium/03_PascalsTriangleGeneration.c) | Optimal time/space, pointers, recursion |
| 4 | **RotateImage90Degrees** | [`medium/04_RotateImage90Degrees.c`](./medium/04_RotateImage90Degrees.c) | Optimal time/space, pointers, recursion |
| 5 | **LongestConsecutiveSequenceLoop** | [`medium/05_LongestConsecutiveSequenceLoop.c`](./medium/05_LongestConsecutiveSequenceLoop.c) | Optimal time/space, pointers, recursion |
| 6 | **SetMatrixZeroes** | [`medium/06_SetMatrixZeroes.c`](./medium/06_SetMatrixZeroes.c) | Optimal time/space, pointers, recursion |
| 7 | **GameOfLifeLoopSimulation** | [`medium/07_GameOfLifeLoopSimulation.c`](./medium/07_GameOfLifeLoopSimulation.c) | Optimal time/space, pointers, recursion |
| 8 | **DiagonalTraverseMatrix** | [`medium/08_DiagonalTraverseMatrix.c`](./medium/08_DiagonalTraverseMatrix.c) | Optimal time/space, pointers, recursion |
| 9 | **IntegerBreakMaxProduct** | [`medium/09_IntegerBreakMaxProduct.c`](./medium/09_IntegerBreakMaxProduct.c) | Optimal time/space, pointers, recursion |
| 10 | **FindDuplicateNumberFloydCycle** | [`medium/10_FindDuplicateNumberFloydCycle.c`](./medium/10_FindDuplicateNumberFloydCycle.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **SudokuSolverBacktrackLoop** | [`hard/01_SudokuSolverBacktrackLoop.c`](./hard/01_SudokuSolverBacktrackLoop.c) | Complex invariants, state trees, low-level bits |
| 2 | **NQueensPuzzleBacktrack** | [`hard/02_NQueensPuzzleBacktrack.c`](./hard/02_NQueensPuzzleBacktrack.c) | Complex invariants, state trees, low-level bits |
| 3 | **TrappingRainWaterTwoPointers** | [`hard/03_TrappingRainWaterTwoPointers.c`](./hard/03_TrappingRainWaterTwoPointers.c) | Complex invariants, state trees, low-level bits |
| 4 | **LargestRectangleInHistogramLoop** | [`hard/04_LargestRectangleInHistogramLoop.c`](./hard/04_LargestRectangleInHistogramLoop.c) | Complex invariants, state trees, low-level bits |
| 5 | **SlidingWindowMaximumLoop** | [`hard/05_SlidingWindowMaximumLoop.c`](./hard/05_SlidingWindowMaximumLoop.c) | Complex invariants, state trees, low-level bits |
| 6 | **FirstMissingPositiveLoop** | [`hard/06_FirstMissingPositiveLoop.c`](./hard/06_FirstMissingPositiveLoop.c) | Complex invariants, state trees, low-level bits |
| 7 | **BasicCalculatorThreeAllOperators** | [`hard/07_BasicCalculatorThreeAllOperators.c`](./hard/07_BasicCalculatorThreeAllOperators.c) | Complex invariants, state trees, low-level bits |
| 8 | **MaxPointsOnALineGCDLoop** | [`hard/08_MaxPointsOnALineGCDLoop.c`](./hard/08_MaxPointsOnALineGCDLoop.c) | Complex invariants, state trees, low-level bits |

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
