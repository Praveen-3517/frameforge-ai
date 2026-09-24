# C Data Structures & Algorithms (DSA) Master Repository

A production-grade, meticulously architected, and low-level C learning repository engineered for mastering Data Structures, Algorithms, Memory Management, and Systems Programming. Designed for cracking technical coding rounds at top-tier product giants (Google, Microsoft, Amazon, Meta, Apple, NVIDIA) and core engineering enterprises.

---

## 📚 Curriculum & Topic Roadmap

| # | Topic | Folder | Difficulty Breakdown | Core Concepts | Status |
|---|-------|--------|----------------------|---------------|:------:|
| 1 | **Variables & Data Types** | [`01-variables-and-data-types/`](./01-variables-and-data-types/) | Easy · Medium · Hard | Sizes, Limits, IEEE 754 Floats, Type Casting, Storage Classes | ✅ Complete |
| 2 | **Operators** | [`02-operators/`](./02-operators/) | Easy · Medium · Hard | Bitwise, Arithmetic, Precedence, Short-Circuit Evaluation | ✅ Complete |
| 3 | **Conditionals** | [`03-conditionals/`](./03-conditionals/) | Easy · Medium · Hard | If-Else, Switch-Case, Branch Prediction, Jump Tables | ✅ Complete |
| 4 | **Loops** | [`04-loops/`](./04-loops/) | Easy · Medium · Hard | For, While, Do-While, Loop Unrolling, Pattern Logic | ✅ Complete |
| 5 | **Arrays (1D & 2D)** | [`05-arrays/`](./05-arrays/) | Easy · Medium · Hard | Contiguous Memory, Multi-Dimensional Indexing, Row-Major Order | ✅ Complete |
| 6 | **Strings** | [`06-strings/`](./06-strings/) | Easy · Medium · Hard | Null-Terminated Buffers, string.h, Buffer Overflow Defense | ✅ Complete |
| 7 | **Functions & Recursion Basics** | [`07-functions-and-recursion-basics/`](./07-functions-and-recursion-basics/) | Easy · Medium · Hard | Call Stack Frames, Pass by Value vs Reference, Tail Calls | ✅ Complete |
| 8 | **Structures & Unions** | [`08-structures-and-unions/`](./08-structures-and-unions/) | Easy · Medium · Hard | Struct Padding, Memory Alignment, Bitfields, Function Pointers | ✅ Complete |
| 9 | **Pointers & Memory Management** | [`09-pointers-and-memory-management/`](./09-pointers-and-memory-management/) | Easy · Medium · Hard | Pointers to Pointers, malloc, calloc, realloc, free, Valgrind | ✅ Complete |
| 10 | **File I/O & Preprocessor** | [`10-file-io-and-preprocessor/`](./10-file-io-and-preprocessor/) | Easy · Medium · Hard | Streams, Binary Serialization, Macros, Conditional Directives | ✅ Complete |
| 11 | **Searching & Sorting** | [`11-searching-and-sorting/`](./11-searching-and-sorting/) | Easy · Medium · Hard | Quick Sort, Merge Sort, Binary Search, qsort Comparator | ✅ Complete |
| 12 | **Recursion & Backtracking** | [`12-recursion-and-backtracking/`](./12-recursion-and-backtracking/) | Easy · Medium · Hard | State Restoration, N-Queens, Sudoku, Permutations, Pruning | ✅ Complete |
| 13 | **Linked Lists** | [`13-linked-list/`](./13-linked-list/) | Easy · Medium · Hard | Singly, Doubly, Circular Lists, Fast & Slow Pointers, LRU | ✅ Complete |
| 14 | **Stack & Queue** | [`14-stack-and-queue/`](./14-stack-and-queue/) | Easy · Medium · Hard | Dynamic Array / Node Stacks, Circular Queue, Monotonic Stack | ✅ Complete |
| 15 | **Trees & Binary Search Trees** | [`15-trees/`](./15-trees/) | Easy · Medium · Hard | Traversals, BST Properties, AVL Balancing, LCA, Serialization | ✅ Complete |
| 16 | **Graphs** | [`16-graphs/`](./16-graphs/) | Easy · Medium · Hard | Adjacency List/Matrix, BFS, DFS, Dijkstra, Tarjan, Kruskal | ✅ Complete |
| 17 | **Dynamic Programming** | [`17-dynamic-programming/`](./17-dynamic-programming/) | Easy · Medium · Hard | Memoization, Tabulation, Knapsack, LCS, LIS, Interval DP | ✅ Complete |
| 18 | **Heaps & Greedy Algorithms** | [`18-heaps-and-greedy/`](./18-heaps-and-greedy/) | Easy · Medium · Hard | Binary Min/Max Heap, Priority Queue, Huffman Coding, Greedy | ✅ Complete |
| 19 | **Bit Manipulation** | [`19-bit-manipulation/`](./19-bit-manipulation/) | Easy · Medium · Hard | Kernighan's Algorithm, Bitmask DP, Bit-Twiddling Hacks | ✅ Complete |
| 20 | **Sliding Window & Two Pointers** | [`20-sliding-window-two-pointers/`](./20-sliding-window-two-pointers/) | Easy · Medium · Hard | Fixed/Variable Windows, Two-Pointers, In-Place Mutators | ✅ Complete |

---

## 🛠️ Repository Structure Standard

Each topic folder follows a consistent modular architecture:
```
<topic-folder>/
├── README.md           # Theoretical notes, memory layouts, ASCII diagrams, edge cases, common traps
├── easy/               # Foundational problems (Campus Placements, TCS, Infosys, Wipro, Cognizant)
├── medium/             # Core interview DSA problems (Amazon, Microsoft, Adobe, Uber, Startups)
└── hard/               # Advanced algorithmic puzzles & low-level memory optimizations (Google, Meta, Directi)
```

Each C program file contains:
1. **Header Docstring**: Problem statement, target company tags, and algorithmic approach.
2. **Standard C Headers**: `<stdio.h>`, `<stdlib.h>`, `<stdbool.h>`, `<string.h>`, `<limits.h>`, etc.
3. **Core Functions**: Algorithmic solutions implemented with clean pointer semantics, input validation, and boundary protection.
4. **`int main(void)` Test Harness**: Fully compilable entry point validating edge cases, custom arrays/inputs, and printing readable formatted output.
5. **Memory Leak Prevention**: All dynamically allocated memory (`malloc`/`calloc`) is explicitly cleaned up via `free()`.
6. **Complexity Analysis**: Big-O Time and Auxiliary Space complexity summary at the footer.

---

## 🚀 How to Compile & Run

### Standard Compilation (GCC / Clang):
```bash
# Compile single program with C11 standard and warnings enabled
gcc -std=c11 -Wall -Wextra -O2 01_ProblemName.c -o solution

# Execute on Windows:
./solution.exe

# Execute on Linux / macOS:
./solution
```

### Memory Sanitization & Leak Checking:
```bash
# Compile with AddressSanitizer & UndefinedBehaviorSanitizer
gcc -std=c11 -Wall -Wextra -g -fsanitize=address,undefined 01_ProblemName.c -o solution
./solution

# Run with Valgrind (Linux / WSL)
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./solution
```
