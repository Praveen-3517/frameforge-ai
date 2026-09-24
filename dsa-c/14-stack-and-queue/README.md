# Stacks, Queues & Monotonic Structures in C

> Array and linked list stack/queue implementations, circular queues, monotonic stacks (Next Greater Element), and double-ended queues.

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
| 1 | **CustomArrayStack** | [`easy/01_CustomArrayStack.c`](./easy/01_CustomArrayStack.c) | Foundational logic, boundary checks |
| 2 | **CustomArrayQueue** | [`easy/02_CustomArrayQueue.c`](./easy/02_CustomArrayQueue.c) | Foundational logic, boundary checks |
| 3 | **MinStackConstantTime** | [`easy/03_MinStackConstantTime.c`](./easy/03_MinStackConstantTime.c) | Foundational logic, boundary checks |
| 4 | **ImplementQueueUsingStacks** | [`easy/04_ImplementQueueUsingStacks.c`](./easy/04_ImplementQueueUsingStacks.c) | Foundational logic, boundary checks |
| 5 | **ImplementStackUsingQueues** | [`easy/05_ImplementStackUsingQueues.c`](./easy/05_ImplementStackUsingQueues.c) | Foundational logic, boundary checks |
| 6 | **BackspaceStringCompare** | [`easy/06_BackspaceStringCompare.c`](./easy/06_BackspaceStringCompare.c) | Foundational logic, boundary checks |
| 7 | **MakeStringGreatAdjacentRemoval** | [`easy/07_MakeStringGreatAdjacentRemoval.c`](./easy/07_MakeStringGreatAdjacentRemoval.c) | Foundational logic, boundary checks |
| 8 | **CrawlerLogFolderDepth** | [`easy/08_CrawlerLogFolderDepth.c`](./easy/08_CrawlerLogFolderDepth.c) | Foundational logic, boundary checks |
| 9 | **BaseballGameRecordStack** | [`easy/09_BaseballGameRecordStack.c`](./easy/09_BaseballGameRecordStack.c) | Foundational logic, boundary checks |
| 10 | **FinalPricesSpecialDiscount** | [`easy/10_FinalPricesSpecialDiscount.c`](./easy/10_FinalPricesSpecialDiscount.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **NextGreaterElementMonotonicStack** | [`medium/01_NextGreaterElementMonotonicStack.c`](./medium/01_NextGreaterElementMonotonicStack.c) | Optimal time/space, pointers, recursion |
| 2 | **DailyTemperaturesMonotonicStack** | [`medium/02_DailyTemperaturesMonotonicStack.c`](./medium/02_DailyTemperaturesMonotonicStack.c) | Optimal time/space, pointers, recursion |
| 3 | **EvaluateReversePolishNotation** | [`medium/03_EvaluateReversePolishNotation.c`](./medium/03_EvaluateReversePolishNotation.c) | Optimal time/space, pointers, recursion |
| 4 | **DesignCircularQueueArray** | [`medium/04_DesignCircularQueueArray.c`](./medium/04_DesignCircularQueueArray.c) | Optimal time/space, pointers, recursion |
| 5 | **AsteroidCollisionStack** | [`medium/05_AsteroidCollisionStack.c`](./medium/05_AsteroidCollisionStack.c) | Optimal time/space, pointers, recursion |
| 6 | **DecodeStringNestedStack** | [`medium/06_DecodeStringNestedStack.c`](./medium/06_DecodeStringNestedStack.c) | Optimal time/space, pointers, recursion |
| 7 | **SimplifyFilePathUnixStack** | [`medium/07_SimplifyFilePathUnixStack.c`](./medium/07_SimplifyFilePathUnixStack.c) | Optimal time/space, pointers, recursion |
| 8 | **RemoveAllAdjacentDuplicatesTwo** | [`medium/08_RemoveAllAdjacentDuplicatesTwo.c`](./medium/08_RemoveAllAdjacentDuplicatesTwo.c) | Optimal time/space, pointers, recursion |
| 9 | **OnlineStockSpanMonotonicStack** | [`medium/09_OnlineStockSpanMonotonicStack.c`](./medium/09_OnlineStockSpanMonotonicStack.c) | Optimal time/space, pointers, recursion |
| 10 | **DesignCircularDeque** | [`medium/10_DesignCircularDeque.c`](./medium/10_DesignCircularDeque.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **LargestRectangleInHistogramMonotonicStack** | [`hard/01_LargestRectangleInHistogramMonotonicStack.c`](./hard/01_LargestRectangleInHistogramMonotonicStack.c) | Complex invariants, state trees, low-level bits |
| 2 | **MaximalRectangleInBinaryMatrix** | [`hard/02_MaximalRectangleInBinaryMatrix.c`](./hard/02_MaximalRectangleInBinaryMatrix.c) | Complex invariants, state trees, low-level bits |
| 3 | **TrappingRainWaterTwoPointersAndStack** | [`hard/03_TrappingRainWaterTwoPointersAndStack.c`](./hard/03_TrappingRainWaterTwoPointersAndStack.c) | Complex invariants, state trees, low-level bits |
| 4 | **BasicCalculatorParenthesesExpressions** | [`hard/04_BasicCalculatorParenthesesExpressions.c`](./hard/04_BasicCalculatorParenthesesExpressions.c) | Complex invariants, state trees, low-level bits |
| 5 | **SlidingWindowMaximumMonotonicDeque** | [`hard/05_SlidingWindowMaximumMonotonicDeque.c`](./hard/05_SlidingWindowMaximumMonotonicDeque.c) | Complex invariants, state trees, low-level bits |
| 6 | **ShortestSubarrayWithSumAtLeastK** | [`hard/06_ShortestSubarrayWithSumAtLeastK.c`](./hard/06_ShortestSubarrayWithSumAtLeastK.c) | Complex invariants, state trees, low-level bits |
| 7 | **ConstrainedSubsequenceSumDeque** | [`hard/07_ConstrainedSubsequenceSumDeque.c`](./hard/07_ConstrainedSubsequenceSumDeque.c) | Complex invariants, state trees, low-level bits |
| 8 | **MaxChunksToMakeSortedTwo** | [`hard/08_MaxChunksToMakeSortedTwo.c`](./hard/08_MaxChunksToMakeSortedTwo.c) | Complex invariants, state trees, low-level bits |

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
