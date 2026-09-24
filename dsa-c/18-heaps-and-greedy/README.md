# Heaps, Priority Queues & Greedy Algorithms in C

> Binary Min/Max-heap array representations, heapify, Priority Queue, Huffman lossless compression, Activity Selection, and Fractional Knapsack.

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
| 1 | **CustomMinHeapArrayImplementation** | [`easy/01_CustomMinHeapArrayImplementation.c`](./easy/01_CustomMinHeapArrayImplementation.c) | Foundational logic, boundary checks |
| 2 | **KthLargestElementInStream** | [`easy/02_KthLargestElementInStream.c`](./easy/02_KthLargestElementInStream.c) | Foundational logic, boundary checks |
| 3 | **LastStoneWeight** | [`easy/03_LastStoneWeight.c`](./easy/03_LastStoneWeight.c) | Foundational logic, boundary checks |
| 4 | **AssignCookiesGreedy** | [`easy/04_AssignCookiesGreedy.c`](./easy/04_AssignCookiesGreedy.c) | Foundational logic, boundary checks |
| 5 | **LemonadeChangeGreedy** | [`easy/05_LemonadeChangeGreedy.c`](./easy/05_LemonadeChangeGreedy.c) | Foundational logic, boundary checks |
| 6 | **MaximumUnitsOnTruck** | [`easy/06_MaximumUnitsOnTruck.c`](./easy/06_MaximumUnitsOnTruck.c) | Foundational logic, boundary checks |
| 7 | **CanPlaceFlowersGreedy** | [`easy/07_CanPlaceFlowersGreedy.c`](./easy/07_CanPlaceFlowersGreedy.c) | Foundational logic, boundary checks |
| 8 | **MinimumCostToConnectSticks** | [`easy/08_MinimumCostToConnectSticks.c`](./easy/08_MinimumCostToConnectSticks.c) | Foundational logic, boundary checks |
| 9 | **RelativeRanksPriorityQueue** | [`easy/09_RelativeRanksPriorityQueue.c`](./easy/09_RelativeRanksPriorityQueue.c) | Foundational logic, boundary checks |
| 10 | **SplitArrayIntoConsecutiveSubsequences** | [`easy/10_SplitArrayIntoConsecutiveSubsequences.c`](./easy/10_SplitArrayIntoConsecutiveSubsequences.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **KthLargestElementInArray** | [`medium/01_KthLargestElementInArray.c`](./medium/01_KthLargestElementInArray.c) | Optimal time/space, pointers, recursion |
| 2 | **TopKFrequentElements** | [`medium/02_TopKFrequentElements.c`](./medium/02_TopKFrequentElements.c) | Optimal time/space, pointers, recursion |
| 3 | **KClosestPointsToOrigin** | [`medium/03_KClosestPointsToOrigin.c`](./medium/03_KClosestPointsToOrigin.c) | Optimal time/space, pointers, recursion |
| 4 | **TaskSchedulerIntervals** | [`medium/04_TaskSchedulerIntervals.c`](./medium/04_TaskSchedulerIntervals.c) | Optimal time/space, pointers, recursion |
| 5 | **ReorganizeStringGreedyHeap** | [`medium/05_ReorganizeStringGreedyHeap.c`](./medium/05_ReorganizeStringGreedyHeap.c) | Optimal time/space, pointers, recursion |
| 6 | **GasStationGreedyCircular** | [`medium/06_GasStationGreedyCircular.c`](./medium/06_GasStationGreedyCircular.c) | Optimal time/space, pointers, recursion |
| 7 | **JumpGameOneGreedy** | [`medium/07_JumpGameOneGreedy.c`](./medium/07_JumpGameOneGreedy.c) | Optimal time/space, pointers, recursion |
| 8 | **JumpGameTwoGreedyMinJumps** | [`medium/08_JumpGameTwoGreedyMinJumps.c`](./medium/08_JumpGameTwoGreedyMinJumps.c) | Optimal time/space, pointers, recursion |
| 9 | **NonOverlappingIntervals** | [`medium/09_NonOverlappingIntervals.c`](./medium/09_NonOverlappingIntervals.c) | Optimal time/space, pointers, recursion |
| 10 | **MergeIntervalsGreedySort** | [`medium/10_MergeIntervalsGreedySort.c`](./medium/10_MergeIntervalsGreedySort.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **FindMedianFromDataStreamTwoHeaps** | [`hard/01_FindMedianFromDataStreamTwoHeaps.c`](./hard/01_FindMedianFromDataStreamTwoHeaps.c) | Complex invariants, state trees, low-level bits |
| 2 | **MergeKSortedListsMinHeap** | [`hard/02_MergeKSortedListsMinHeap.c`](./hard/02_MergeKSortedListsMinHeap.c) | Complex invariants, state trees, low-level bits |
| 3 | **SlidingWindowMedianDualHeaps** | [`hard/03_SlidingWindowMedianDualHeaps.c`](./hard/03_SlidingWindowMedianDualHeaps.c) | Complex invariants, state trees, low-level bits |
| 4 | **TrappingRainWaterTwo3DHeap** | [`hard/04_TrappingRainWaterTwo3DHeap.c`](./hard/04_TrappingRainWaterTwo3DHeap.c) | Complex invariants, state trees, low-level bits |
| 5 | **IPOProjectSelectionMaxHeap** | [`hard/05_IPOProjectSelectionMaxHeap.c`](./hard/05_IPOProjectSelectionMaxHeap.c) | Complex invariants, state trees, low-level bits |
| 6 | **RearrangeStringKDistanceApart** | [`hard/06_RearrangeStringKDistanceApart.c`](./hard/06_RearrangeStringKDistanceApart.c) | Complex invariants, state trees, low-level bits |
| 7 | **HuffmanCodingLosslessCompression** | [`hard/07_HuffmanCodingLosslessCompression.c`](./hard/07_HuffmanCodingLosslessCompression.c) | Complex invariants, state trees, low-level bits |
| 8 | **CourseScheduleThreeGreedyMaxHeap** | [`hard/08_CourseScheduleThreeGreedyMaxHeap.c`](./hard/08_CourseScheduleThreeGreedyMaxHeap.c) | Complex invariants, state trees, low-level bits |

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
