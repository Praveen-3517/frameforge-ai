import os
import re
import json
import subprocess

JAVA_ROOT = r'f:\AI tool\dsa-java'
C_ROOT = r'f:\AI tool\dsa-c'

with open(r'f:\AI tool\dsa_java_map.json', 'r', encoding='utf-8') as f:
    TOPICS_MAP = json.load(f)

# Topic titles and conceptual descriptions for README.md
TOPIC_INFO = {
    "01-variables-and-data-types": {
        "title": "Variables, Data Types & Memory Representation in C",
        "desc": "Mastering fundamental C data types, sizes via sizeof, limits.h, IEEE 754 float internals, integer overflow undefined behavior, type promotions, and storage classes."
    },
    "02-operators": {
        "title": "Operators, Precedence & Bit-Level Manipulation in C",
        "desc": "Arithmetic, logical, relational, bitwise operators, operator precedence/associativity tables, sequence points, and branchless arithmetic."
    },
    "03-conditionals": {
        "title": "Conditionals, Branching & Decision Control in C",
        "desc": "If-else statements, switch-case jump tables, ternary operators, Duff's device, and structured error handling patterns using goto cleanup."
    },
    "04-loops": {
        "title": "Iteration, Loops & Pattern Algorithms in C",
        "desc": "For, while, and do-while loops, loop unrolling for cache performance, nested pattern algorithms, and convergence series."
    },
    "05-arrays": {
        "title": "1D and 2D Arrays & Contiguous Memory in C",
        "desc": "Row-major memory layout, pointer decay, passing arrays to functions, dynamic allocation, prefix sums, Kadane's algorithm, and Boyer-Moore voting."
    },
    "06-strings": {
        "title": "C Strings, Character Arrays & Memory Safety",
        "desc": "Null-terminated character arrays, pointer arithmetic on strings, safe vs unsafe string.h APIs, KMP search, Rabin-Karp, and buffer overflow defense."
    },
    "07-methods-and-recursion-basics": {
        "title": "Functions, Stack Frames & Recursion Basics in C",
        "desc": "Pass-by-value vs pass-by-pointer, activation records in call stack, base conditions, tail call optimization (-O2), and function pointers as callbacks."
    },
    "08-oop": {
        "title": "Object-Oriented Programming & Structures in C",
        "desc": "Emulating OOP in C using structures, unions, bit-fields, encapsulation, inheritance via composition, and polymorphism via function pointer vtables."
    },
    "09-exception-handling": {
        "title": "Error Handling, Memory Safety & Resilience in C",
        "desc": "Robust error handling in C: return codes, errno, setjmp/longjmp, structured goto cleanups, memory leak detection, and boundary validation."
    },
    "10-collections-framework": {
        "title": "Custom Data Structures & Containers in C",
        "desc": "Building standard containers from scratch in C: dynamic vector (ArrayList), hash table with chaining/open addressing, and generic void* collections."
    },
    "11-searching-and-sorting": {
        "title": "Searching & Sorting Algorithms in C",
        "desc": "Linear/binary search, Quick Sort with median-of-three, Merge Sort, Counting/Radix Sort, and standard library qsort with custom comparators."
    },
    "12-recursion-and-backtracking": {
        "title": "Recursion & Backtracking Algorithms in C",
        "desc": "State space exploration, N-Queens, Sudoku solver, Rat in a Maze, subsets, permutations, and tree pruning techniques."
    },
    "13-linked-list": {
        "title": "Linked Lists & Pointer Manipulation in C",
        "desc": "Singly, doubly, and circular linked lists, Floyd's cycle detection, list reversal, merge sort on lists, and LRU cache with hash table in C."
    },
    "14-stack-and-queue": {
        "title": "Stacks, Queues & Monotonic Structures in C",
        "desc": "Array and linked list stack/queue implementations, circular queues, monotonic stacks (Next Greater Element), and double-ended queues."
    },
    "15-trees": {
        "title": "Binary Trees, BST & AVL Trees in C",
        "desc": "Node pointers, recursive and iterative DFS/BFS traversals, Binary Search Tree invariants, AVL tree balancing rotations, and Lowest Common Ancestor."
    },
    "16-graphs": {
        "title": "Graph Algorithms & Network Traversal in C",
        "desc": "Adjacency matrices and adjacency lists, BFS, DFS, Dijkstra's shortest path, Bellman-Ford, Disjoint Set Union (Union-Find), and Kruskal's MST."
    },
    "17-dynamic-programming": {
        "title": "Dynamic Programming & Optimization in C",
        "desc": "1D and 2D dynamic programming, 0/1 Knapsack, Longest Common Subsequence, Longest Increasing Subsequence, Edit Distance, and Matrix Chain Multiplication."
    },
    "18-heaps-and-greedy": {
        "title": "Heaps, Priority Queues & Greedy Algorithms in C",
        "desc": "Binary Min/Max-heap array representations, heapify, Priority Queue, Huffman lossless compression, Activity Selection, and Fractional Knapsack."
    },
    "19-bit-manipulation": {
        "title": "Bit Manipulation & Low-Level Twiddling in C",
        "desc": "Bitwise masks, Brian Kernighan's bit-counting, XOR properties, subset generation via bitmasks, power of two checks, and bit-level arithmetic."
    },
    "20-sliding-window-two-pointers": {
        "title": "Sliding Window & Two-Pointer Techniques in C",
        "desc": "Fixed-size and dynamically expanding sliding windows, two-pointer inward and outward scans, container with most water, and subarray optimizations."
    }
}

def generate_topic_readme(topic_key, easy_files, med_files, hard_files):
    info = TOPIC_INFO.get(topic_key, {"title": topic_key, "desc": "C DSA module."})
    title = info["title"]
    desc = info["desc"]
    
    md = f"""# {title}

> {desc}

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
"""
    for idx, f in enumerate(easy_files, 1):
        c_name = f.replace('.java', '.c')
        clean_name = re.sub(r'^\d+_', '', f.replace('.java', ''))
        md += f"| {idx} | **{clean_name}** | [`easy/{c_name}`](./easy/{c_name}) | Foundational logic, boundary checks |\n"

    md += """
### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
"""
    for idx, f in enumerate(med_files, 1):
        c_name = f.replace('.java', '.c')
        clean_name = re.sub(r'^\d+_', '', f.replace('.java', ''))
        md += f"| {idx} | **{clean_name}** | [`medium/{c_name}`](./medium/{c_name}) | Optimal time/space, pointers, recursion |\n"

    md += """
### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
"""
    for idx, f in enumerate(hard_files, 1):
        c_name = f.replace('.java', '.c')
        clean_name = re.sub(r'^\d+_', '', f.replace('.java', ''))
        md += f"| {idx} | **{clean_name}** | [`hard/{c_name}`](./hard/{c_name}) | Complex invariants, state trees, low-level bits |\n"

    md += """
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
"""
    return md

print("Readme generator ready.")
