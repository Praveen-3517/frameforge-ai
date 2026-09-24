# Sliding Window & Two-Pointer Techniques in C

> Fixed-size and dynamically expanding sliding windows, two-pointer inward and outward scans, container with most water, and subarray optimizations.

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
| 1 | **MaxSumSubarraySizeK** | [`easy/01_MaxSumSubarraySizeK.c`](./easy/01_MaxSumSubarraySizeK.c) | Foundational logic, boundary checks |
| 2 | **ContainsDuplicateIISlidingWindow** | [`easy/02_ContainsDuplicateIISlidingWindow.c`](./easy/02_ContainsDuplicateIISlidingWindow.c) | Foundational logic, boundary checks |
| 3 | **TwoSumIISortedArrayTwoPointer** | [`easy/03_TwoSumIISortedArrayTwoPointer.c`](./easy/03_TwoSumIISortedArrayTwoPointer.c) | Foundational logic, boundary checks |
| 4 | **MinSizeSubarraySum** | [`easy/04_MinSizeSubarraySum.c`](./easy/04_MinSizeSubarraySum.c) | Foundational logic, boundary checks |
| 5 | **MoveZeroesToEnd** | [`easy/05_MoveZeroesToEnd.c`](./easy/05_MoveZeroesToEnd.c) | Foundational logic, boundary checks |
| 6 | **RemoveDuplicatesSortedArrayTwoPointer** | [`easy/06_RemoveDuplicatesSortedArrayTwoPointer.c`](./easy/06_RemoveDuplicatesSortedArrayTwoPointer.c) | Foundational logic, boundary checks |
| 7 | **SquaresOfSortedArrayTwoPointer** | [`easy/07_SquaresOfSortedArrayTwoPointer.c`](./easy/07_SquaresOfSortedArrayTwoPointer.c) | Foundational logic, boundary checks |
| 8 | **ValidPalindromeTwoPointer** | [`easy/08_ValidPalindromeTwoPointer.c`](./easy/08_ValidPalindromeTwoPointer.c) | Foundational logic, boundary checks |
| 9 | **AverageOfSubarraysSizeK** | [`easy/09_AverageOfSubarraysSizeK.c`](./easy/09_AverageOfSubarraysSizeK.c) | Foundational logic, boundary checks |
| 10 | **ReverseStringInPlaceTwoPointer** | [`easy/10_ReverseStringInPlaceTwoPointer.c`](./easy/10_ReverseStringInPlaceTwoPointer.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **LongestSubstringWithoutRepeatingChars** | [`medium/01_LongestSubstringWithoutRepeatingChars.c`](./medium/01_LongestSubstringWithoutRepeatingChars.c) | Optimal time/space, pointers, recursion |
| 2 | **LongestRepeatingCharacterReplacement** | [`medium/02_LongestRepeatingCharacterReplacement.c`](./medium/02_LongestRepeatingCharacterReplacement.c) | Optimal time/space, pointers, recursion |
| 3 | **PermutationInStringFixedWindow** | [`medium/03_PermutationInStringFixedWindow.c`](./medium/03_PermutationInStringFixedWindow.c) | Optimal time/space, pointers, recursion |
| 4 | **ThreeSumSortedTwoPointer** | [`medium/04_ThreeSumSortedTwoPointer.c`](./medium/04_ThreeSumSortedTwoPointer.c) | Optimal time/space, pointers, recursion |
| 5 | **ContainerWithMostWaterTwoPointer** | [`medium/05_ContainerWithMostWaterTwoPointer.c`](./medium/05_ContainerWithMostWaterTwoPointer.c) | Optimal time/space, pointers, recursion |
| 6 | **SubarrayProductLessThanK** | [`medium/06_SubarrayProductLessThanK.c`](./medium/06_SubarrayProductLessThanK.c) | Optimal time/space, pointers, recursion |
| 7 | **MaxConsecutiveOnesIIIAtMostKZeros** | [`medium/07_MaxConsecutiveOnesIIIAtMostKZeros.c`](./medium/07_MaxConsecutiveOnesIIIAtMostKZeros.c) | Optimal time/space, pointers, recursion |
| 8 | **FindAllAnagramsInString** | [`medium/08_FindAllAnagramsInString.c`](./medium/08_FindAllAnagramsInString.c) | Optimal time/space, pointers, recursion |
| 9 | **MinimumWindowSubstringVariableWindow** | [`medium/09_MinimumWindowSubstringVariableWindow.c`](./medium/09_MinimumWindowSubstringVariableWindow.c) | Optimal time/space, pointers, recursion |
| 10 | **LongestSubarrayOnesAfterDeletingOne** | [`medium/10_LongestSubarrayOnesAfterDeletingOne.c`](./medium/10_LongestSubarrayOnesAfterDeletingOne.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **SlidingWindowMaximumMonotonicDeque** | [`hard/01_SlidingWindowMaximumMonotonicDeque.c`](./hard/01_SlidingWindowMaximumMonotonicDeque.c) | Complex invariants, state trees, low-level bits |
| 2 | **SubstringConcatenationAllWords** | [`hard/02_SubstringConcatenationAllWords.c`](./hard/02_SubstringConcatenationAllWords.c) | Complex invariants, state trees, low-level bits |
| 3 | **MinimumKConsecutiveBitFlips** | [`hard/03_MinimumKConsecutiveBitFlips.c`](./hard/03_MinimumKConsecutiveBitFlips.c) | Complex invariants, state trees, low-level bits |
| 4 | **CountSubarraysWithBoundedMaximum** | [`hard/04_CountSubarraysWithBoundedMaximum.c`](./hard/04_CountSubarraysWithBoundedMaximum.c) | Complex invariants, state trees, low-level bits |
| 5 | **JumpGameVIMaxScoreMonotonicDeque** | [`hard/05_JumpGameVIMaxScoreMonotonicDeque.c`](./hard/05_JumpGameVIMaxScoreMonotonicDeque.c) | Complex invariants, state trees, low-level bits |

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
