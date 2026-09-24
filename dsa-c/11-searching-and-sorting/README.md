# Searching & Sorting Algorithms in C

> Linear/binary search, Quick Sort with median-of-three, Merge Sort, Counting/Radix Sort, and standard library qsort with custom comparators.

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
| 1 | **LinearSearchAllOccurrences** | [`easy/01_LinearSearchAllOccurrences.c`](./easy/01_LinearSearchAllOccurrences.c) | Foundational logic, boundary checks |
| 2 | **BinarySearchIterativeAndRecursive** | [`easy/02_BinarySearchIterativeAndRecursive.c`](./easy/02_BinarySearchIterativeAndRecursive.c) | Foundational logic, boundary checks |
| 3 | **OrderAgnosticBinarySearch** | [`easy/03_OrderAgnosticBinarySearch.c`](./easy/03_OrderAgnosticBinarySearch.c) | Foundational logic, boundary checks |
| 4 | **BubbleSortOptimized** | [`easy/04_BubbleSortOptimized.c`](./easy/04_BubbleSortOptimized.c) | Foundational logic, boundary checks |
| 5 | **SelectionSortStepByStep** | [`easy/05_SelectionSortStepByStep.c`](./easy/05_SelectionSortStepByStep.c) | Foundational logic, boundary checks |
| 6 | **InsertionSortArray** | [`easy/06_InsertionSortArray.c`](./easy/06_InsertionSortArray.c) | Foundational logic, boundary checks |
| 7 | **CountingSortNonNegative** | [`easy/07_CountingSortNonNegative.c`](./easy/07_CountingSortNonNegative.c) | Foundational logic, boundary checks |
| 8 | **SquareRootBinarySearch** | [`easy/08_SquareRootBinarySearch.c`](./easy/08_SquareRootBinarySearch.c) | Foundational logic, boundary checks |
| 9 | **SearchInsertPosition** | [`easy/09_SearchInsertPosition.c`](./easy/09_SearchInsertPosition.c) | Foundational logic, boundary checks |
| 10 | **MergeTwoSortedArraysInPlace** | [`easy/10_MergeTwoSortedArraysInPlace.c`](./easy/10_MergeTwoSortedArraysInPlace.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **SearchInRotatedSortedArray** | [`medium/01_SearchInRotatedSortedArray.c`](./medium/01_SearchInRotatedSortedArray.c) | Optimal time/space, pointers, recursion |
| 2 | **FindFirstAndLastPositionInSortedArray** | [`medium/02_FindFirstAndLastPositionInSortedArray.c`](./medium/02_FindFirstAndLastPositionInSortedArray.c) | Optimal time/space, pointers, recursion |
| 3 | **MergeSortImplementation** | [`medium/03_MergeSortImplementation.c`](./medium/03_MergeSortImplementation.c) | Optimal time/space, pointers, recursion |
| 4 | **QuickSortLomutoAndHoare** | [`medium/04_QuickSortLomutoAndHoare.c`](./medium/04_QuickSortLomutoAndHoare.c) | Optimal time/space, pointers, recursion |
| 5 | **SortColorsDutchNationalFlag** | [`medium/05_SortColorsDutchNationalFlag.c`](./medium/05_SortColorsDutchNationalFlag.c) | Optimal time/space, pointers, recursion |
| 6 | **MergeIntervalsOverlapping** | [`medium/06_MergeIntervalsOverlapping.c`](./medium/06_MergeIntervalsOverlapping.c) | Optimal time/space, pointers, recursion |
| 7 | **FindPeakElementBinarySearch** | [`medium/07_FindPeakElementBinarySearch.c`](./medium/07_FindPeakElementBinarySearch.c) | Optimal time/space, pointers, recursion |
| 8 | **KokoEatingBananasBinarySearchOnAnswer** | [`medium/08_KokoEatingBananasBinarySearchOnAnswer.c`](./medium/08_KokoEatingBananasBinarySearchOnAnswer.c) | Optimal time/space, pointers, recursion |
| 9 | **QuickSelectKthSmallestElement** | [`medium/09_QuickSelectKthSmallestElement.c`](./medium/09_QuickSelectKthSmallestElement.c) | Optimal time/space, pointers, recursion |
| 10 | **SearchA2DMatrixBinarySearch** | [`medium/10_SearchA2DMatrixBinarySearch.c`](./medium/10_SearchA2DMatrixBinarySearch.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **MedianOfTwoSortedArraysBinarySearch** | [`hard/01_MedianOfTwoSortedArraysBinarySearch.c`](./hard/01_MedianOfTwoSortedArraysBinarySearch.c) | Complex invariants, state trees, low-level bits |
| 2 | **CountInversionsMergeSort** | [`hard/02_CountInversionsMergeSort.c`](./hard/02_CountInversionsMergeSort.c) | Complex invariants, state trees, low-level bits |
| 3 | **SplitArrayLargestSum** | [`hard/03_SplitArrayLargestSum.c`](./hard/03_SplitArrayLargestSum.c) | Complex invariants, state trees, low-level bits |
| 4 | **MaximumGapBucketSort** | [`hard/04_MaximumGapBucketSort.c`](./hard/04_MaximumGapBucketSort.c) | Complex invariants, state trees, low-level bits |
| 5 | **RussianDollEnvelopes** | [`hard/05_RussianDollEnvelopes.c`](./hard/05_RussianDollEnvelopes.c) | Complex invariants, state trees, low-level bits |
| 6 | **FindKthSmallestPairDistance** | [`hard/06_FindKthSmallestPairDistance.c`](./hard/06_FindKthSmallestPairDistance.c) | Complex invariants, state trees, low-level bits |
| 7 | **CountOfSmallerNumbersAfterSelf** | [`hard/07_CountOfSmallerNumbersAfterSelf.c`](./hard/07_CountOfSmallerNumbersAfterSelf.c) | Complex invariants, state trees, low-level bits |
| 8 | **AggressiveCowsBinarySearch** | [`hard/08_AggressiveCowsBinarySearch.c`](./hard/08_AggressiveCowsBinarySearch.c) | Complex invariants, state trees, low-level bits |

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
