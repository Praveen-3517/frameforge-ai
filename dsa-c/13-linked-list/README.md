# Linked Lists & Pointer Manipulation in C

> Singly, doubly, and circular linked lists, Floyd's cycle detection, list reversal, merge sort on lists, and LRU cache with hash table in C.

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
| 1 | **DesignSinglyLinkedList** | [`easy/01_DesignSinglyLinkedList.c`](./easy/01_DesignSinglyLinkedList.c) | Foundational logic, boundary checks |
| 2 | **ReverseSinglyLinkedList** | [`easy/02_ReverseSinglyLinkedList.c`](./easy/02_ReverseSinglyLinkedList.c) | Foundational logic, boundary checks |
| 3 | **MiddleOfLinkedList** | [`easy/03_MiddleOfLinkedList.c`](./easy/03_MiddleOfLinkedList.c) | Foundational logic, boundary checks |
| 4 | **MergeTwoSortedLists** | [`easy/04_MergeTwoSortedLists.c`](./easy/04_MergeTwoSortedLists.c) | Foundational logic, boundary checks |
| 5 | **LinkedListCycleDetection** | [`easy/05_LinkedListCycleDetection.c`](./easy/05_LinkedListCycleDetection.c) | Foundational logic, boundary checks |
| 6 | **PalindromeLinkedList** | [`easy/06_PalindromeLinkedList.c`](./easy/06_PalindromeLinkedList.c) | Foundational logic, boundary checks |
| 7 | **RemoveLinkedListElements** | [`easy/07_RemoveLinkedListElements.c`](./easy/07_RemoveLinkedListElements.c) | Foundational logic, boundary checks |
| 8 | **DeleteNodeWithoutHeadPointer** | [`easy/08_DeleteNodeWithoutHeadPointer.c`](./easy/08_DeleteNodeWithoutHeadPointer.c) | Foundational logic, boundary checks |
| 9 | **IntersectionOfTwoLinkedLists** | [`easy/09_IntersectionOfTwoLinkedLists.c`](./easy/09_IntersectionOfTwoLinkedLists.c) | Foundational logic, boundary checks |
| 10 | **DesignDoublyLinkedList** | [`easy/10_DesignDoublyLinkedList.c`](./easy/10_DesignDoublyLinkedList.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **AddTwoNumbersReversedList** | [`medium/01_AddTwoNumbersReversedList.c`](./medium/01_AddTwoNumbersReversedList.c) | Optimal time/space, pointers, recursion |
| 2 | **RemoveNthNodeFromEndOfList** | [`medium/02_RemoveNthNodeFromEndOfList.c`](./medium/02_RemoveNthNodeFromEndOfList.c) | Optimal time/space, pointers, recursion |
| 3 | **LinkedListCycleTwoFindStart** | [`medium/03_LinkedListCycleTwoFindStart.c`](./medium/03_LinkedListCycleTwoFindStart.c) | Optimal time/space, pointers, recursion |
| 4 | **ReorderListHalfFold** | [`medium/04_ReorderListHalfFold.c`](./medium/04_ReorderListHalfFold.c) | Optimal time/space, pointers, recursion |
| 5 | **OddEvenLinkedList** | [`medium/05_OddEvenLinkedList.c`](./medium/05_OddEvenLinkedList.c) | Optimal time/space, pointers, recursion |
| 6 | **SortListMergeSort** | [`medium/06_SortListMergeSort.c`](./medium/06_SortListMergeSort.c) | Optimal time/space, pointers, recursion |
| 7 | **CopyListWithRandomPointer** | [`medium/07_CopyListWithRandomPointer.c`](./medium/07_CopyListWithRandomPointer.c) | Optimal time/space, pointers, recursion |
| 8 | **RotateListByKPlaces** | [`medium/08_RotateListByKPlaces.c`](./medium/08_RotateListByKPlaces.c) | Optimal time/space, pointers, recursion |
| 9 | **PartitionListAroundX** | [`medium/09_PartitionListAroundX.c`](./medium/09_PartitionListAroundX.c) | Optimal time/space, pointers, recursion |
| 10 | **SwapNodesInPairs** | [`medium/10_SwapNodesInPairs.c`](./medium/10_SwapNodesInPairs.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **ReverseNodesInKGroup** | [`hard/01_ReverseNodesInKGroup.c`](./hard/01_ReverseNodesInKGroup.c) | Complex invariants, state trees, low-level bits |
| 2 | **MergeKSortedListsDivideConquer** | [`hard/02_MergeKSortedListsDivideConquer.c`](./hard/02_MergeKSortedListsDivideConquer.c) | Complex invariants, state trees, low-level bits |
| 3 | **FlattenMultilevelDoublyLinkedList** | [`hard/03_FlattenMultilevelDoublyLinkedList.c`](./hard/03_FlattenMultilevelDoublyLinkedList.c) | Complex invariants, state trees, low-level bits |
| 4 | **LRUCacheCustomDoublyList** | [`hard/04_LRUCacheCustomDoublyList.c`](./hard/04_LRUCacheCustomDoublyList.c) | Complex invariants, state trees, low-level bits |
| 5 | **ReverseLinkedListBetweenPositions** | [`hard/05_ReverseLinkedListBetweenPositions.c`](./hard/05_ReverseLinkedListBetweenPositions.c) | Complex invariants, state trees, low-level bits |
| 6 | **SplitLinkedListInParts** | [`hard/06_SplitLinkedListInParts.c`](./hard/06_SplitLinkedListInParts.c) | Complex invariants, state trees, low-level bits |
| 7 | **RemoveDuplicatesFromSortedListTwo** | [`hard/07_RemoveDuplicatesFromSortedListTwo.c`](./hard/07_RemoveDuplicatesFromSortedListTwo.c) | Complex invariants, state trees, low-level bits |
| 8 | **LFUCacheDoublyListArchitecture** | [`hard/08_LFUCacheDoublyListArchitecture.c`](./hard/08_LFUCacheDoublyListArchitecture.c) | Complex invariants, state trees, low-level bits |

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
