# Custom Data Structures & Containers in C

> Building standard containers from scratch in C: dynamic vector (ArrayList), hash table with chaining/open addressing, and generic void* collections.

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
| 1 | **ArrayListOperationsAndTraversal** | [`easy/01_ArrayListOperationsAndTraversal.c`](./easy/01_ArrayListOperationsAndTraversal.c) | Foundational logic, boundary checks |
| 2 | **LinkedListAsDequeAndQueue** | [`easy/02_LinkedListAsDequeAndQueue.c`](./easy/02_LinkedListAsDequeAndQueue.c) | Foundational logic, boundary checks |
| 3 | **HashSetUniqueElements** | [`easy/03_HashSetUniqueElements.c`](./easy/03_HashSetUniqueElements.c) | Foundational logic, boundary checks |
| 4 | **LinkedHashSetPreserveOrder** | [`easy/04_LinkedHashSetPreserveOrder.c`](./easy/04_LinkedHashSetPreserveOrder.c) | Foundational logic, boundary checks |
| 5 | **TreeSetNaturalAndCustomOrder** | [`easy/05_TreeSetNaturalAndCustomOrder.c`](./easy/05_TreeSetNaturalAndCustomOrder.c) | Foundational logic, boundary checks |
| 6 | **HashMapFrequencyCounter** | [`easy/06_HashMapFrequencyCounter.c`](./easy/06_HashMapFrequencyCounter.c) | Foundational logic, boundary checks |
| 7 | **LinkedHashMapAccessOrder** | [`easy/07_LinkedHashMapAccessOrder.c`](./easy/07_LinkedHashMapAccessOrder.c) | Foundational logic, boundary checks |
| 8 | **TreeMapNavigableKeyLookups** | [`easy/08_TreeMapNavigableKeyLookups.c`](./easy/08_TreeMapNavigableKeyLookups.c) | Foundational logic, boundary checks |
| 9 | **ArrayDequeAsStackAndQueue** | [`easy/09_ArrayDequeAsStackAndQueue.c`](./easy/09_ArrayDequeAsStackAndQueue.c) | Foundational logic, boundary checks |
| 10 | **PriorityQueueMinAndMaxHeap** | [`easy/10_PriorityQueueMinAndMaxHeap.c`](./easy/10_PriorityQueueMinAndMaxHeap.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **TwoSumHashMapLookup** | [`medium/01_TwoSumHashMapLookup.c`](./medium/01_TwoSumHashMapLookup.c) | Optimal time/space, pointers, recursion |
| 2 | **GroupAnagramsCategorization** | [`medium/02_GroupAnagramsCategorization.c`](./medium/02_GroupAnagramsCategorization.c) | Optimal time/space, pointers, recursion |
| 3 | **TopKFrequentElements** | [`medium/03_TopKFrequentElements.c`](./medium/03_TopKFrequentElements.c) | Optimal time/space, pointers, recursion |
| 4 | **KthLargestElementInArray** | [`medium/04_KthLargestElementInArray.c`](./medium/04_KthLargestElementInArray.c) | Optimal time/space, pointers, recursion |
| 5 | **ValidParenthesesStackEvaluation** | [`medium/05_ValidParenthesesStackEvaluation.c`](./medium/05_ValidParenthesesStackEvaluation.c) | Optimal time/space, pointers, recursion |
| 6 | **LRUCacheLinkedHashMap** | [`medium/06_LRUCacheLinkedHashMap.c`](./medium/06_LRUCacheLinkedHashMap.c) | Optimal time/space, pointers, recursion |
| 7 | **SubarraySumEqualsK** | [`medium/07_SubarraySumEqualsK.c`](./medium/07_SubarraySumEqualsK.c) | Optimal time/space, pointers, recursion |
| 8 | **SortCharactersByFrequency** | [`medium/08_SortCharactersByFrequency.c`](./medium/08_SortCharactersByFrequency.c) | Optimal time/space, pointers, recursion |
| 9 | **FindAllDuplicatesInArray** | [`medium/09_FindAllDuplicatesInArray.c`](./medium/09_FindAllDuplicatesInArray.c) | Optimal time/space, pointers, recursion |
| 10 | **DesignUndergroundSystem** | [`medium/10_DesignUndergroundSystem.c`](./medium/10_DesignUndergroundSystem.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **FindMedianFromDataStream** | [`hard/01_FindMedianFromDataStream.c`](./hard/01_FindMedianFromDataStream.c) | Complex invariants, state trees, low-level bits |
| 2 | **SlidingWindowMaximumDeque** | [`hard/02_SlidingWindowMaximumDeque.c`](./hard/02_SlidingWindowMaximumDeque.c) | Complex invariants, state trees, low-level bits |
| 3 | **LFUCacheDesign** | [`hard/03_LFUCacheDesign.c`](./hard/03_LFUCacheDesign.c) | Complex invariants, state trees, low-level bits |
| 4 | **AllOOneDataStructure** | [`hard/04_AllOOneDataStructure.c`](./hard/04_AllOOneDataStructure.c) | Complex invariants, state trees, low-level bits |
| 5 | **FirstMissingPositiveArrayMap** | [`hard/05_FirstMissingPositiveArrayMap.c`](./hard/05_FirstMissingPositiveArrayMap.c) | Complex invariants, state trees, low-level bits |
| 6 | **DesignTwitterFeedSystem** | [`hard/06_DesignTwitterFeedSystem.c`](./hard/06_DesignTwitterFeedSystem.c) | Complex invariants, state trees, low-level bits |
| 7 | **MyCalendarThreeKBooking** | [`hard/07_MyCalendarThreeKBooking.c`](./hard/07_MyCalendarThreeKBooking.c) | Complex invariants, state trees, low-level bits |
| 8 | **MergeKSortedListsPriorityQueue** | [`hard/08_MergeKSortedListsPriorityQueue.c`](./hard/08_MergeKSortedListsPriorityQueue.c) | Complex invariants, state trees, low-level bits |

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
