# 1D and 2D Arrays & Contiguous Memory in C

> Row-major memory layout, pointer decay, passing arrays to functions, dynamic allocation, prefix sums, Kadane's algorithm, and Boyer-Moore voting.

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
| 1 | **LinearAndBinarySearchArray** | [`easy/01_LinearAndBinarySearchArray.c`](./easy/01_LinearAndBinarySearchArray.c) | Foundational logic, boundary checks |
| 2 | **FindMaxAndMinInArray** | [`easy/02_FindMaxAndMinInArray.c`](./easy/02_FindMaxAndMinInArray.c) | Foundational logic, boundary checks |
| 3 | **ReverseArrayInPlace** | [`easy/03_ReverseArrayInPlace.c`](./easy/03_ReverseArrayInPlace.c) | Foundational logic, boundary checks |
| 4 | **CheckSortedArray** | [`easy/04_CheckSortedArray.c`](./easy/04_CheckSortedArray.c) | Foundational logic, boundary checks |
| 5 | **RemoveDuplicatesSortedArray** | [`easy/05_RemoveDuplicatesSortedArray.c`](./easy/05_RemoveDuplicatesSortedArray.c) | Foundational logic, boundary checks |
| 6 | **MoveZeroesToEnd** | [`easy/06_MoveZeroesToEnd.c`](./easy/06_MoveZeroesToEnd.c) | Foundational logic, boundary checks |
| 7 | **RunningSumOf1DArray** | [`easy/07_RunningSumOf1DArray.c`](./easy/07_RunningSumOf1DArray.c) | Foundational logic, boundary checks |
| 8 | **TwoSumBruteAndHash** | [`easy/08_TwoSumBruteAndHash.c`](./easy/08_TwoSumBruteAndHash.c) | Foundational logic, boundary checks |
| 9 | **MatrixRowAndColumnSum** | [`easy/09_MatrixRowAndColumnSum.c`](./easy/09_MatrixRowAndColumnSum.c) | Foundational logic, boundary checks |
| 10 | **JaggedArrayDemo** | [`easy/10_JaggedArrayDemo.c`](./easy/10_JaggedArrayDemo.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **KadanesMaxSubarraySum** | [`medium/01_KadanesMaxSubarraySum.c`](./medium/01_KadanesMaxSubarraySum.c) | Optimal time/space, pointers, recursion |
| 2 | **SortColorsDutchNationalFlag** | [`medium/02_SortColorsDutchNationalFlag.c`](./medium/02_SortColorsDutchNationalFlag.c) | Optimal time/space, pointers, recursion |
| 3 | **MajorityElementMooresVoting** | [`medium/03_MajorityElementMooresVoting.c`](./medium/03_MajorityElementMooresVoting.c) | Optimal time/space, pointers, recursion |
| 4 | **SubarraySumEqualsK** | [`medium/04_SubarraySumEqualsK.c`](./medium/04_SubarraySumEqualsK.c) | Optimal time/space, pointers, recursion |
| 5 | **RotateArrayByKPlaces** | [`medium/05_RotateArrayByKPlaces.c`](./medium/05_RotateArrayByKPlaces.c) | Optimal time/space, pointers, recursion |
| 6 | **ProductOfArrayExceptSelf** | [`medium/06_ProductOfArrayExceptSelf.c`](./medium/06_ProductOfArrayExceptSelf.c) | Optimal time/space, pointers, recursion |
| 7 | **MergeIntervalsArray** | [`medium/07_MergeIntervalsArray.c`](./medium/07_MergeIntervalsArray.c) | Optimal time/space, pointers, recursion |
| 8 | **ContinuousSubarraySumModuloK** | [`medium/08_ContinuousSubarraySumModuloK.c`](./medium/08_ContinuousSubarraySumModuloK.c) | Optimal time/space, pointers, recursion |
| 9 | **SearchA2DMatrixTwo** | [`medium/09_SearchA2DMatrixTwo.c`](./medium/09_SearchA2DMatrixTwo.c) | Optimal time/space, pointers, recursion |
| 10 | **NextGreaterElementCircular** | [`medium/10_NextGreaterElementCircular.c`](./medium/10_NextGreaterElementCircular.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **FirstMissingPositiveArray** | [`hard/01_FirstMissingPositiveArray.c`](./hard/01_FirstMissingPositiveArray.c) | Complex invariants, state trees, low-level bits |
| 2 | **LargestRectangleInHistogramArray** | [`hard/02_LargestRectangleInHistogramArray.c`](./hard/02_LargestRectangleInHistogramArray.c) | Complex invariants, state trees, low-level bits |
| 3 | **TrappingRainWaterArray** | [`hard/03_TrappingRainWaterArray.c`](./hard/03_TrappingRainWaterArray.c) | Complex invariants, state trees, low-level bits |
| 4 | **MedianOfTwoSortedArrays** | [`hard/04_MedianOfTwoSortedArrays.c`](./hard/04_MedianOfTwoSortedArrays.c) | Complex invariants, state trees, low-level bits |
| 5 | **SlidingWindowMaximumArray** | [`hard/05_SlidingWindowMaximumArray.c`](./hard/05_SlidingWindowMaximumArray.c) | Complex invariants, state trees, low-level bits |
| 6 | **MaximalRectangleInBinaryMatrix** | [`hard/06_MaximalRectangleInBinaryMatrix.c`](./hard/06_MaximalRectangleInBinaryMatrix.c) | Complex invariants, state trees, low-level bits |
| 7 | **CountSubarraysWithMedianK** | [`hard/07_CountSubarraysWithMedianK.c`](./hard/07_CountSubarraysWithMedianK.c) | Complex invariants, state trees, low-level bits |
| 8 | **SubarrayWithKDifferentIntegers** | [`hard/08_SubarrayWithKDifferentIntegers.c`](./hard/08_SubarrayWithKDifferentIntegers.c) | Complex invariants, state trees, low-level bits |

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
