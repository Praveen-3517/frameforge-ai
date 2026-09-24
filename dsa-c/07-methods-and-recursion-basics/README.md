# Functions, Stack Frames & Recursion Basics in C

> Pass-by-value vs pass-by-pointer, activation records in call stack, base conditions, tail call optimization (-O2), and function pointers as callbacks.

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
| 1 | **PassByValueDemonstration** | [`easy/01_PassByValueDemonstration.c`](./easy/01_PassByValueDemonstration.c) | Foundational logic, boundary checks |
| 2 | **MethodOverloadingRules** | [`easy/02_MethodOverloadingRules.c`](./easy/02_MethodOverloadingRules.c) | Foundational logic, boundary checks |
| 3 | **VarargsSumAndAverage** | [`easy/03_VarargsSumAndAverage.c`](./easy/03_VarargsSumAndAverage.c) | Foundational logic, boundary checks |
| 4 | **RecursiveFactorialAndStack** | [`easy/04_RecursiveFactorialAndStack.c`](./easy/04_RecursiveFactorialAndStack.c) | Foundational logic, boundary checks |
| 5 | **RecursiveSumOfDigits** | [`easy/05_RecursiveSumOfDigits.c`](./easy/05_RecursiveSumOfDigits.c) | Foundational logic, boundary checks |
| 6 | **RecursivePowerCalculation** | [`easy/06_RecursivePowerCalculation.c`](./easy/06_RecursivePowerCalculation.c) | Foundational logic, boundary checks |
| 7 | **RecursivePrint1ToN** | [`easy/07_RecursivePrint1ToN.c`](./easy/07_RecursivePrint1ToN.c) | Foundational logic, boundary checks |
| 8 | **RecursiveArraySumAndMax** | [`easy/08_RecursiveArraySumAndMax.c`](./easy/08_RecursiveArraySumAndMax.c) | Foundational logic, boundary checks |
| 9 | **CheckArraySortedRecursion** | [`easy/09_CheckArraySortedRecursion.c`](./easy/09_CheckArraySortedRecursion.c) | Foundational logic, boundary checks |
| 10 | **DecimalToBinaryRecursion** | [`easy/10_DecimalToBinaryRecursion.c`](./easy/10_DecimalToBinaryRecursion.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **TowerOfHanoiClassic** | [`medium/01_TowerOfHanoiClassic.c`](./medium/01_TowerOfHanoiClassic.c) | Optimal time/space, pointers, recursion |
| 2 | **PowXNFastDivideConquer** | [`medium/02_PowXNFastDivideConquer.c`](./medium/02_PowXNFastDivideConquer.c) | Optimal time/space, pointers, recursion |
| 3 | **SubsetsRecursiveGeneration** | [`medium/03_SubsetsRecursiveGeneration.c`](./medium/03_SubsetsRecursiveGeneration.c) | Optimal time/space, pointers, recursion |
| 4 | **PermutationsRecursive** | [`medium/04_PermutationsRecursive.c`](./medium/04_PermutationsRecursive.c) | Optimal time/space, pointers, recursion |
| 5 | **CombinationSumRecursive** | [`medium/05_CombinationSumRecursive.c`](./medium/05_CombinationSumRecursive.c) | Optimal time/space, pointers, recursion |
| 6 | **LetterCombinationsPhoneKeypad** | [`medium/06_LetterCombinationsPhoneKeypad.c`](./medium/06_LetterCombinationsPhoneKeypad.c) | Optimal time/space, pointers, recursion |
| 7 | **GenerateParenthesesRecursion** | [`medium/07_GenerateParenthesesRecursion.c`](./medium/07_GenerateParenthesesRecursion.c) | Optimal time/space, pointers, recursion |
| 8 | **JosephusProblemRecursion** | [`medium/08_JosephusProblemRecursion.c`](./medium/08_JosephusProblemRecursion.c) | Optimal time/space, pointers, recursion |
| 9 | **WordSearchGridRecursion** | [`medium/09_WordSearchGridRecursion.c`](./medium/09_WordSearchGridRecursion.c) | Optimal time/space, pointers, recursion |
| 10 | **FlattenNestedListIteratorRecursion** | [`medium/10_FlattenNestedListIteratorRecursion.c`](./medium/10_FlattenNestedListIteratorRecursion.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **PermutationsTwoWithDuplicates** | [`hard/01_PermutationsTwoWithDuplicates.c`](./hard/01_PermutationsTwoWithDuplicates.c) | Complex invariants, state trees, low-level bits |
| 2 | **NQueensPuzzleSolver** | [`hard/02_NQueensPuzzleSolver.c`](./hard/02_NQueensPuzzleSolver.c) | Complex invariants, state trees, low-level bits |
| 3 | **SudokuSolverRecursion** | [`hard/03_SudokuSolverRecursion.c`](./hard/03_SudokuSolverRecursion.c) | Complex invariants, state trees, low-level bits |
| 4 | **PalindromePartitioningMinCuts** | [`hard/04_PalindromePartitioningMinCuts.c`](./hard/04_PalindromePartitioningMinCuts.c) | Complex invariants, state trees, low-level bits |
| 5 | **ExpressionAddOperatorsRecursion** | [`hard/05_ExpressionAddOperatorsRecursion.c`](./hard/05_ExpressionAddOperatorsRecursion.c) | Complex invariants, state trees, low-level bits |
| 6 | **ParseLispExpressionRecursion** | [`hard/06_ParseLispExpressionRecursion.c`](./hard/06_ParseLispExpressionRecursion.c) | Complex invariants, state trees, low-level bits |
| 7 | **KthSymbolInGrammarRecursion** | [`hard/07_KthSymbolInGrammarRecursion.c`](./hard/07_KthSymbolInGrammarRecursion.c) | Complex invariants, state trees, low-level bits |
| 8 | **SpecialBinaryStringRecursion** | [`hard/08_SpecialBinaryStringRecursion.c`](./hard/08_SpecialBinaryStringRecursion.c) | Complex invariants, state trees, low-level bits |

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
