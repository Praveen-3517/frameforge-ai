# Operators, Precedence & Bit-Level Manipulation in C

> Arithmetic, logical, relational, bitwise operators, operator precedence/associativity tables, sequence points, and branchless arithmetic.

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
| 1 | **ArithmeticOperationsAndModDemo** | [`easy/01_ArithmeticOperationsAndModDemo.c`](./easy/01_ArithmeticOperationsAndModDemo.c) | Foundational logic, boundary checks |
| 2 | **PrePostIncrementPitfalls** | [`easy/02_PrePostIncrementPitfalls.c`](./easy/02_PrePostIncrementPitfalls.c) | Foundational logic, boundary checks |
| 3 | **RelationalAndLogicalDemo** | [`easy/03_RelationalAndLogicalDemo.c`](./easy/03_RelationalAndLogicalDemo.c) | Foundational logic, boundary checks |
| 4 | **TernaryMaxOfThree** | [`easy/04_TernaryMaxOfThree.c`](./easy/04_TernaryMaxOfThree.c) | Foundational logic, boundary checks |
| 5 | **CompoundAssignmentImplicitCast** | [`easy/05_CompoundAssignmentImplicitCast.c`](./easy/05_CompoundAssignmentImplicitCast.c) | Foundational logic, boundary checks |
| 6 | **BitwiseBasicOperations** | [`easy/06_BitwiseBasicOperations.c`](./easy/06_BitwiseBasicOperations.c) | Foundational logic, boundary checks |
| 7 | **CheckPowerOfTwo** | [`easy/07_CheckPowerOfTwo.c`](./easy/07_CheckPowerOfTwo.c) | Foundational logic, boundary checks |
| 8 | **SwapOddEvenBits** | [`easy/08_SwapOddEvenBits.c`](./easy/08_SwapOddEvenBits.c) | Foundational logic, boundary checks |
| 9 | **CheckOppositeSigns** | [`easy/09_CheckOppositeSigns.c`](./easy/09_CheckOppositeSigns.c) | Foundational logic, boundary checks |
| 10 | **MultiplyBySevenBitwise** | [`easy/10_MultiplyBySevenBitwise.c`](./easy/10_MultiplyBySevenBitwise.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **AddWithoutPlusOperator** | [`medium/01_AddWithoutPlusOperator.c`](./medium/01_AddWithoutPlusOperator.c) | Optimal time/space, pointers, recursion |
| 2 | **SubtractWithoutMinusOperator** | [`medium/02_SubtractWithoutMinusOperator.c`](./medium/02_SubtractWithoutMinusOperator.c) | Optimal time/space, pointers, recursion |
| 3 | **MultiplyWithoutMultiplicationOperator** | [`medium/03_MultiplyWithoutMultiplicationOperator.c`](./medium/03_MultiplyWithoutMultiplicationOperator.c) | Optimal time/space, pointers, recursion |
| 4 | **MinMaxWithoutBranching** | [`medium/04_MinMaxWithoutBranching.c`](./medium/04_MinMaxWithoutBranching.c) | Optimal time/space, pointers, recursion |
| 5 | **PowerOfFourBitwise** | [`medium/05_PowerOfFourBitwise.c`](./medium/05_PowerOfFourBitwise.c) | Optimal time/space, pointers, recursion |
| 6 | **ReverseBits32BitInteger** | [`medium/06_ReverseBits32BitInteger.c`](./medium/06_ReverseBits32BitInteger.c) | Optimal time/space, pointers, recursion |
| 7 | **BitwiseHammingDistance** | [`medium/07_BitwiseHammingDistance.c`](./medium/07_BitwiseHammingDistance.c) | Optimal time/space, pointers, recursion |
| 8 | **TotalHammingDistance** | [`medium/08_TotalHammingDistance.c`](./medium/08_TotalHammingDistance.c) | Optimal time/space, pointers, recursion |
| 9 | **ModuloWithoutModOperator** | [`medium/09_ModuloWithoutModOperator.c`](./medium/09_ModuloWithoutModOperator.c) | Optimal time/space, pointers, recursion |
| 10 | **NextHigherPowerOfTwo** | [`medium/10_NextHigherPowerOfTwo.c`](./medium/10_NextHigherPowerOfTwo.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **BitwiseSubsetsPowerSet** | [`hard/01_BitwiseSubsetsPowerSet.c`](./hard/01_BitwiseSubsetsPowerSet.c) | Complex invariants, state trees, low-level bits |
| 2 | **BitwiseMaximumXOROfTwoNumbers** | [`hard/02_BitwiseMaximumXOROfTwoNumbers.c`](./hard/02_BitwiseMaximumXOROfTwoNumbers.c) | Complex invariants, state trees, low-level bits |
| 3 | **NumberOfValidWordsForPuzzle** | [`hard/03_NumberOfValidWordsForPuzzle.c`](./hard/03_NumberOfValidWordsForPuzzle.c) | Complex invariants, state trees, low-level bits |
| 4 | **SubmaskEnumerationBitwise** | [`hard/04_SubmaskEnumerationBitwise.c`](./hard/04_SubmaskEnumerationBitwise.c) | Complex invariants, state trees, low-level bits |
| 5 | **MissingTwoNumbersBitwise** | [`hard/05_MissingTwoNumbersBitwise.c`](./hard/05_MissingTwoNumbersBitwise.c) | Complex invariants, state trees, low-level bits |
| 6 | **SmallestSufficientTeamBitmaskDP** | [`hard/06_SmallestSufficientTeamBitmaskDP.c`](./hard/06_SmallestSufficientTeamBitmaskDP.c) | Complex invariants, state trees, low-level bits |
| 7 | **BitwiseOperatorPrecedenceTrapEvaluator** | [`hard/07_BitwiseOperatorPrecedenceTrapEvaluator.c`](./hard/07_BitwiseOperatorPrecedenceTrapEvaluator.c) | Complex invariants, state trees, low-level bits |
| 8 | **CountTripletsEqualXOR** | [`hard/08_CountTripletsEqualXOR.c`](./hard/08_CountTripletsEqualXOR.c) | Complex invariants, state trees, low-level bits |

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
