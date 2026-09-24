# Bit Manipulation & Low-Level Twiddling in C

> Bitwise masks, Brian Kernighan's bit-counting, XOR properties, subset generation via bitmasks, power of two checks, and bit-level arithmetic.

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
| 1 | **SingleNumberXOR** | [`easy/01_SingleNumberXOR.c`](./easy/01_SingleNumberXOR.c) | Foundational logic, boundary checks |
| 2 | **NumberOfOneBitsKernighan** | [`easy/02_NumberOfOneBitsKernighan.c`](./easy/02_NumberOfOneBitsKernighan.c) | Foundational logic, boundary checks |
| 3 | **PowerOfTwoBitCheck** | [`easy/03_PowerOfTwoBitCheck.c`](./easy/03_PowerOfTwoBitCheck.c) | Foundational logic, boundary checks |
| 4 | **CountingBitsBitmask** | [`easy/04_CountingBitsBitmask.c`](./easy/04_CountingBitsBitmask.c) | Foundational logic, boundary checks |
| 5 | **ReverseBits32BitInteger** | [`easy/05_ReverseBits32BitInteger.c`](./easy/05_ReverseBits32BitInteger.c) | Foundational logic, boundary checks |
| 6 | **MissingNumberXOR** | [`easy/06_MissingNumberXOR.c`](./easy/06_MissingNumberXOR.c) | Foundational logic, boundary checks |
| 7 | **AddBinaryStrings** | [`easy/07_AddBinaryStrings.c`](./easy/07_AddBinaryStrings.c) | Foundational logic, boundary checks |
| 8 | **HammingDistanceBits** | [`easy/08_HammingDistanceBits.c`](./easy/08_HammingDistanceBits.c) | Foundational logic, boundary checks |
| 9 | **BinaryNumberWithAlternatingBits** | [`easy/09_BinaryNumberWithAlternatingBits.c`](./easy/09_BinaryNumberWithAlternatingBits.c) | Foundational logic, boundary checks |
| 10 | **PowerOfFourBitwise** | [`easy/10_PowerOfFourBitwise.c`](./easy/10_PowerOfFourBitwise.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **SubsetsBitmaskGeneration** | [`medium/01_SubsetsBitmaskGeneration.c`](./medium/01_SubsetsBitmaskGeneration.c) | Optimal time/space, pointers, recursion |
| 2 | **SingleNumberTwoEveryElementThreeTimes** | [`medium/02_SingleNumberTwoEveryElementThreeTimes.c`](./medium/02_SingleNumberTwoEveryElementThreeTimes.c) | Optimal time/space, pointers, recursion |
| 3 | **SingleNumberThreeTwoUniqueElements** | [`medium/03_SingleNumberThreeTwoUniqueElements.c`](./medium/03_SingleNumberThreeTwoUniqueElements.c) | Optimal time/space, pointers, recursion |
| 4 | **BitwiseANDOfNumbersRange** | [`medium/04_BitwiseANDOfNumbersRange.c`](./medium/04_BitwiseANDOfNumbersRange.c) | Optimal time/space, pointers, recursion |
| 5 | **DivideTwoIntegersBitShift** | [`medium/05_DivideTwoIntegersBitShift.c`](./medium/05_DivideTwoIntegersBitShift.c) | Optimal time/space, pointers, recursion |
| 6 | **SumOfTwoIntegersWithoutPlusMinus** | [`medium/06_SumOfTwoIntegersWithoutPlusMinus.c`](./medium/06_SumOfTwoIntegersWithoutPlusMinus.c) | Optimal time/space, pointers, recursion |
| 7 | **MaximumXOROfTwoNumbersInArray** | [`medium/07_MaximumXOROfTwoNumbersInArray.c`](./medium/07_MaximumXOROfTwoNumbersInArray.c) | Optimal time/space, pointers, recursion |
| 8 | **TotalHammingDistanceAllPairs** | [`medium/08_TotalHammingDistanceAllPairs.c`](./medium/08_TotalHammingDistanceAllPairs.c) | Optimal time/space, pointers, recursion |
| 9 | **GrayCodeSequenceGeneration** | [`medium/09_GrayCodeSequenceGeneration.c`](./medium/09_GrayCodeSequenceGeneration.c) | Optimal time/space, pointers, recursion |
| 10 | **RepeatedDNASequencesBitmask** | [`medium/10_RepeatedDNASequencesBitmask.c`](./medium/10_RepeatedDNASequencesBitmask.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **TravelingSalesmanBitmaskDP** | [`hard/01_TravelingSalesmanBitmaskDP.c`](./hard/01_TravelingSalesmanBitmaskDP.c) | Complex invariants, state trees, low-level bits |
| 2 | **NumberOfValidWordsForEveryPuzzle** | [`hard/02_NumberOfValidWordsForEveryPuzzle.c`](./hard/02_NumberOfValidWordsForEveryPuzzle.c) | Complex invariants, state trees, low-level bits |
| 3 | **MaximumScoreWordsFormedByLetters** | [`hard/03_MaximumScoreWordsFormedByLetters.c`](./hard/03_MaximumScoreWordsFormedByLetters.c) | Complex invariants, state trees, low-level bits |
| 4 | **SmallestSufficientTeamBitmaskDP** | [`hard/04_SmallestSufficientTeamBitmaskDP.c`](./hard/04_SmallestSufficientTeamBitmaskDP.c) | Complex invariants, state trees, low-level bits |
| 5 | **CampusBikesIIMinCostAssignment** | [`hard/05_CampusBikesIIMinCostAssignment.c`](./hard/05_CampusBikesIIMinCostAssignment.c) | Complex invariants, state trees, low-level bits |

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
