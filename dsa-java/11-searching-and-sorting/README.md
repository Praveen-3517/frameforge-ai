# Topic 11: Searching and Sorting Algorithms

Searching and sorting form the algorithmic backbone of computer science and technical interviews.

---

## Searching Algorithms Overview

| Algorithm | Pre-requisite | Best Time | Average Time | Worst Time | Space |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Linear Search** | None | O(1) | O(N) | O(N) | O(1) |
| **Binary Search** | Monotonic / Sorted | O(1) | O(log N) | O(log N) | O(1) |
| **Ternary Search** | Unimodal / Sorted | O(1) | O(log3 N) | O(log3 N) | O(1) |
| **Exponential Search** | Sorted & Unbounded | O(1) | O(log I) | O(log I) | O(1) |

---

## Sorting Algorithms Overview

| Algorithm | Best Time | Average Time | Worst Time | Space | Stable? | In-Place? |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Bubble Sort** | O(N) | O(N^2) | O(N^2) | O(1) | Yes | Yes |
| **Selection Sort** | O(N^2) | O(N^2) | O(N^2) | O(1) | No | Yes |
| **Insertion Sort** | O(N) | O(N^2) | O(N^2) | O(1) | Yes | Yes |
| **Merge Sort** | O(N log N)| O(N log N) | O(N log N) | O(N) | Yes | No |
| **Quick Sort** | O(N log N)| O(N log N) | O(N^2) | O(log N)*| No | Yes |
| **Heap Sort** | O(N log N)| O(N log N) | O(N log N) | O(1) | No | Yes |
| **Counting Sort** | O(N + K) | O(N + K) | O(N + K) | O(K) | Yes | No |
| **Radix Sort** | O(D * (N + B))| O(D * (N + B))| O(D * (N + B))| O(N + B)| Yes | No |
| **Bucket Sort** | O(N + K) | O(N) | O(N^2) | O(N) | Yes | No |

*\* Recursion stack space.*

---

## Binary Search on Answer / Monotonic Predicates
Many complex interview problems do not feature a sorted array, but rather a monotonic boolean function:
$$f(x) = \text{true/false}$$
If there exists a transition point where $f(x)$ flips from `false` to `true`, Binary Search on Answer (or Capacity) solves the problem in $O(\log(\text{range}) \times \text{check})$.
Examples:
- Aggressive Cows
- Capacity to Ship Packages Within D Days
- Split Array Largest Sum
- Koko Eating Bananas

---

## Folder Structure
- `easy/`: 10 foundational implementations (Linear & Binary Search, Bubble, Selection, Insertion, Counting Sort).
- `medium/`: 10 core algorithmic problems (Search in Rotated Sorted Array, Merge Intervals, Dutch National Flag, QuickSelect).
- `hard/`: 8 advanced algorithmic problems (Median of Two Sorted Arrays, Count Inversions, Maximum Gap Bucket Sort, Russian Doll Envelopes).
