# 20 - Sliding Window & Two Pointers

## Concept Overview

**Sliding Window** and **Two Pointers** are complementary techniques that turn brute-force O(N²) or O(N³) solutions into elegant O(N) ones by maintaining a "window" or two index pointers that traverse the array in a coordinated fashion.

---

## Two Pointers

Two index variables (`left` and `right`) start at specific positions and move toward (or away from) each other based on a condition.

### Key Variants

| Pattern | Setup | Motion | Example Use-case |
|---|---|---|---|
| Opposite ends | left=0, right=n-1 | Move toward each other | Two Sum in Sorted Array |
| Same direction (slow-fast) | slow=0, fast=k | fast advances ahead | Remove Duplicates, Cycle Detection |
| Partitioning | left=0, right=n-1 | Swap to partition | Dutch National Flag, Quicksort partition |

---

## Sliding Window

A window `[left, right]` expands by moving `right` and contracts by moving `left`.

### Fixed-Size Window

```java
// Window of size k
int windowSum = 0;
for (int right = 0; right < n; right++) {
    windowSum += arr[right];
    if (right >= k) {
        windowSum -= arr[right - k]; // remove element leaving window
    }
    if (right >= k - 1) {
        // process window
    }
}
```

### Variable-Size Window (Expand / Shrink)

```java
int left = 0;
for (int right = 0; right < n; right++) {
    // Expand: include arr[right] in window

    while (/* window is invalid */) {
        // Shrink: remove arr[left] from window
        left++;
    }

    // Window [left, right] is now valid — record answer
}
```

---

## Time & Space Complexity

| Technique | Time | Space |
|---|---|---|
| Two Pointers (sorted array) | O(N) | O(1) |
| Sliding Window (fixed) | O(N) | O(1) |
| Sliding Window (variable) | O(N) amortized | O(K) for frequency map |
| Nested loops (brute force) | O(N²) | O(1) |

---

## When to Apply

| Situation | Technique |
|---|---|
| Contiguous subarray / substring with condition | Sliding Window |
| Two elements summing to target in sorted array | Two Pointers (opposite ends) |
| Remove Nth node from list, detect cycle | Two Pointers (slow/fast) |
| Partition around pivot | Two Pointers (swap) |
| Minimum / Maximum window satisfying constraint | Variable Sliding Window |

---

## Common Interview Problems

### Easy
| # | Problem | Key Idea |
|---|---|---|
| 01 | Maximum Sum Subarray of Size K | Fixed window sum |
| 02 | Contains Duplicate II | Window existence check |
| 03 | Two Sum II (sorted input) | Opposite-end pointers |
| 04 | Minimum Size Subarray Sum ≥ Target | Variable window shrink |
| 05 | Move Zeroes | Slow-fast pointer partition |
| 06 | Remove Duplicates from Sorted Array | Slow writer / fast reader |
| 07 | Squares of a Sorted Array | Two-end merge |
| 08 | Check if String is Palindrome | Opposite-end char compare |
| 09 | Average of Subarrays of Size K | Fixed window average |
| 10 | Reverse String (in-place) | Opposite-end swap |

### Medium
| # | Problem | Key Idea |
|---|---|---|
| 01 | Longest Substring Without Repeating Characters | Variable window + HashSet |
| 02 | Longest Repeating Character Replacement | Variable window + freq map |
| 03 | Permutation in String | Fixed window frequency match |
| 04 | 3Sum | Sort + two-pointer for each pivot |
| 05 | Container With Most Water | Opposite-end maximize |
| 06 | Subarray Product Less Than K | Variable window product |
| 07 | Max Consecutive Ones III | Variable window with at-most-K zeros |
| 08 | Find All Anagrams in a String | Fixed window + freq compare |
| 09 | Minimum Window Substring | Variable window + need/have tracking |
| 10 | Longest Subarray of 1s After Deleting One Element | Variable window at-most-1 zero |

### Hard
| # | Problem | Key Idea |
|---|---|---|
| 01 | Minimum Window Substring (exact) | Variable window two-freq maps |
| 02 | Sliding Window Maximum | Monotonic deque |
| 03 | Substring with Concatenation of All Words | Multi-word fixed window |
| 04 | Minimum Number of K Consecutive Bit Flips | Variable window prefix XOR |
| 05 | Count Subarrays with Bounded Maximum | Two-pointer count |

---

## Company Tags

- **Google**: Minimum Window Substring, Sliding Window Maximum, Permutation in String
- **Amazon**: Longest Substring Without Repeating Characters, 3Sum, Container with Most Water
- **Facebook / Meta**: Move Zeroes, 3Sum, Minimum Size Subarray Sum
- **Microsoft**: Two Sum II, Remove Duplicates, Squares of a Sorted Array
- **Apple**: Container with Most Water, Longest Substring Without Repeating Characters
