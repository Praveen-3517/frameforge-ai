# Topic 18: Heaps & Greedy Algorithms (PriorityQueue, Two Heaps, Huffman, Interval Scheduling)

## 1. Overview & Core Philosophy

A **Binary Heap** is a complete binary tree that satisfies the **Heap Property**:
- **Min-Heap**: The value of each node is $\ge$ the value of its parent ($A[\text{parent}] \le A[\text{child}]$). Root is the minimum element.
- **Max-Heap**: The value of each node is $\le$ the value of its parent ($A[\text{parent}] \ge A[\text{child}]$). Root is the maximum element.

A **Greedy Algorithm** makes the locally optimal choice at each stage with the hope of finding a global optimum. It succeeds when a problem exhibits:
1. **Greedy Choice Property**: A globally optimal solution can be reached by picking locally optimal choices.
2. **Optimal Substructure**: The optimal solution to the problem contains optimal solutions to subproblems.

---

## 2. Binary Heap Operations & Array Indexing

In a 0-indexed complete binary tree array:
- **Parent of index $i$**: $(i - 1) / 2$
- **Left Child of index $i$**: $2i + 1$
- **Right Child of index $i$**: $2i + 2$

| Operation | Time Complexity | Auxiliary Space |
| :--- | :--- | :--- |
| **`peek()` / Find Min/Max** | $O(1)$ | $O(1)$ |
| **`offer()` / Insert (Heapify-Up)** | $O(\log N)$ | $O(1)$ |
| **`poll()` / Extract Min/Max (Heapify-Down)** | $O(\log N)$ | $O(1)$ |
| **`buildHeap()` from Array** | $O(N)$ | $O(1)$ |

---

## 3. Major Patterns

### 1. Top-K Elements / Frequency
- Maintain a **Min-Heap of size $K$**.
- Compare each new element with `heap.peek()`. If greater, poll and offer.
- Space Complexity: strictly bounded to $O(K)$.

### 2. Dual Heaps (Median of Stream)
- Partition numbers into lower half (Max-Heap) and upper half (Min-Heap).
- Balances size difference $\le 1$.
- `findMedian()` in $O(1)$, `addNum()` in $O(\log N)$.

### 3. Interval Scheduling & Merging
- Sort intervals by start time (or end time for Activity Selection).
- Greedily merge overlapping segments or discard minimum overlapping endpoints.

### 4. Huffman Coding (Lossless Compression)
- Build a binary prefix code tree by repeatedly extracting two smallest frequency nodes from a Min-Heap and combining them.

---

## 4. Directory Structure

```
18-heaps-and-greedy/
├── README.md
├── easy/
│   ├── 01_CustomMinHeapArrayImplementation.java
│   ├── 02_KthLargestElementInStream.java
│   ├── 03_LastStoneWeight.java
│   ├── 04_AssignCookiesGreedy.java
│   ├── 05_LemonadeChangeGreedy.java
│   ├── 06_MaximumUnitsOnTruck.java
│   ├── 07_CanPlaceFlowersGreedy.java
│   ├── 08_MinimumCostToConnectSticks.java
│   ├── 09_RelativeRanksPriorityQueue.java
│   └── 10_SplitArrayIntoConsecutiveSubsequences.java
├── medium/
│   ├── 01_KthLargestElementInArray.java
│   ├── 02_TopKFrequentElements.java
│   ├── 03_KClosestPointsToOrigin.java
│   ├── 04_TaskSchedulerIntervals.java
│   ├── 05_ReorganizeStringGreedyHeap.java
│   ├── 06_GasStationGreedyCircular.java
│   ├── 07_JumpGameOneGreedy.java
│   ├── 08_JumpGameTwoGreedyMinJumps.java
│   ├── 09_NonOverlappingIntervals.java
│   └── 10_MergeIntervalsGreedySort.java
└── hard/
    ├── 01_FindMedianFromDataStreamTwoHeaps.java
    ├── 02_MergeKSortedListsMinHeap.java
    ├── 03_SlidingWindowMedianDualHeaps.java
    ├── 04_TrappingRainWaterTwo3DHeap.java
    ├── 05_IPOProjectSelectionMaxHeap.java
    ├── 06_RearrangeStringKDistanceApart.java
    ├── 07_HuffmanCodingLosslessCompression.java
    └── 08_CourseScheduleThreeGreedyMaxHeap.java
```
