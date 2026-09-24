# Binary Trees, BST & AVL Trees in C

> Node pointers, recursive and iterative DFS/BFS traversals, Binary Search Tree invariants, AVL tree balancing rotations, and Lowest Common Ancestor.

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
| 1 | **BinaryTreePreorderTraversal** | [`easy/01_BinaryTreePreorderTraversal.c`](./easy/01_BinaryTreePreorderTraversal.c) | Foundational logic, boundary checks |
| 2 | **BinaryTreeInorderTraversal** | [`easy/02_BinaryTreeInorderTraversal.c`](./easy/02_BinaryTreeInorderTraversal.c) | Foundational logic, boundary checks |
| 3 | **BinaryTreePostorderTraversal** | [`easy/03_BinaryTreePostorderTraversal.c`](./easy/03_BinaryTreePostorderTraversal.c) | Foundational logic, boundary checks |
| 4 | **MaximumDepthOfBinaryTree** | [`easy/04_MaximumDepthOfBinaryTree.c`](./easy/04_MaximumDepthOfBinaryTree.c) | Foundational logic, boundary checks |
| 5 | **MinimumDepthOfBinaryTree** | [`easy/05_MinimumDepthOfBinaryTree.c`](./easy/05_MinimumDepthOfBinaryTree.c) | Foundational logic, boundary checks |
| 6 | **InvertBinaryTree** | [`easy/06_InvertBinaryTree.c`](./easy/06_InvertBinaryTree.c) | Foundational logic, boundary checks |
| 7 | **SameTree** | [`easy/07_SameTree.c`](./easy/07_SameTree.c) | Foundational logic, boundary checks |
| 8 | **SymmetricTree** | [`easy/08_SymmetricTree.c`](./easy/08_SymmetricTree.c) | Foundational logic, boundary checks |
| 9 | **PathSumRootToLeaf** | [`easy/09_PathSumRootToLeaf.c`](./easy/09_PathSumRootToLeaf.c) | Foundational logic, boundary checks |
| 10 | **SearchInBinarySearchTree** | [`easy/10_SearchInBinarySearchTree.c`](./easy/10_SearchInBinarySearchTree.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **BinaryTreeLevelOrderTraversal** | [`medium/01_BinaryTreeLevelOrderTraversal.c`](./medium/01_BinaryTreeLevelOrderTraversal.c) | Optimal time/space, pointers, recursion |
| 2 | **BinaryTreeZigzagLevelOrder** | [`medium/02_BinaryTreeZigzagLevelOrder.c`](./medium/02_BinaryTreeZigzagLevelOrder.c) | Optimal time/space, pointers, recursion |
| 3 | **LowestCommonAncestorBT** | [`medium/03_LowestCommonAncestorBT.c`](./medium/03_LowestCommonAncestorBT.c) | Optimal time/space, pointers, recursion |
| 4 | **ValidateBinarySearchTree** | [`medium/04_ValidateBinarySearchTree.c`](./medium/04_ValidateBinarySearchTree.c) | Optimal time/space, pointers, recursion |
| 5 | **ConstructTreeFromPreorderInorder** | [`medium/05_ConstructTreeFromPreorderInorder.c`](./medium/05_ConstructTreeFromPreorderInorder.c) | Optimal time/space, pointers, recursion |
| 6 | **BinaryTreeRightSideView** | [`medium/06_BinaryTreeRightSideView.c`](./medium/06_BinaryTreeRightSideView.c) | Optimal time/space, pointers, recursion |
| 7 | **DiameterOfBinaryTree** | [`medium/07_DiameterOfBinaryTree.c`](./medium/07_DiameterOfBinaryTree.c) | Optimal time/space, pointers, recursion |
| 8 | **KthSmallestElementInBST** | [`medium/08_KthSmallestElementInBST.c`](./medium/08_KthSmallestElementInBST.c) | Optimal time/space, pointers, recursion |
| 9 | **FlattenBinaryTreeToLinkedList** | [`medium/09_FlattenBinaryTreeToLinkedList.c`](./medium/09_FlattenBinaryTreeToLinkedList.c) | Optimal time/space, pointers, recursion |
| 10 | **ImplementTriePrefixTree** | [`medium/10_ImplementTriePrefixTree.c`](./medium/10_ImplementTriePrefixTree.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **BinaryTreeMaximumPathSum** | [`hard/01_BinaryTreeMaximumPathSum.c`](./hard/01_BinaryTreeMaximumPathSum.c) | Complex invariants, state trees, low-level bits |
| 2 | **SerializeAndDeserializeBinaryTree** | [`hard/02_SerializeAndDeserializeBinaryTree.c`](./hard/02_SerializeAndDeserializeBinaryTree.c) | Complex invariants, state trees, low-level bits |
| 3 | **VerticalOrderTraversalBinaryTree** | [`hard/03_VerticalOrderTraversalBinaryTree.c`](./hard/03_VerticalOrderTraversalBinaryTree.c) | Complex invariants, state trees, low-level bits |
| 4 | **BinaryTreeCameras** | [`hard/04_BinaryTreeCameras.c`](./hard/04_BinaryTreeCameras.c) | Complex invariants, state trees, low-level bits |
| 5 | **AllNodesDistanceKInBinaryTree** | [`hard/05_AllNodesDistanceKInBinaryTree.c`](./hard/05_AllNodesDistanceKInBinaryTree.c) | Complex invariants, state trees, low-level bits |
| 6 | **MorrisTraversalInorderO1Space** | [`hard/06_MorrisTraversalInorderO1Space.c`](./hard/06_MorrisTraversalInorderO1Space.c) | Complex invariants, state trees, low-level bits |
| 7 | **AVLTreeSelfBalancing** | [`hard/07_AVLTreeSelfBalancing.c`](./hard/07_AVLTreeSelfBalancing.c) | Complex invariants, state trees, low-level bits |
| 8 | **WordSearchTwoTrieBacktracking** | [`hard/08_WordSearchTwoTrieBacktracking.c`](./hard/08_WordSearchTwoTrieBacktracking.c) | Complex invariants, state trees, low-level bits |

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
