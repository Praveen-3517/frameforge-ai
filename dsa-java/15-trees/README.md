# Topic 15: Trees (Binary Tree, BST, AVL, Trie, & Advanced Traversals)

## 1. Overview & Fundamentals

A **Tree** is a non-linear, hierarchical data structure composed of nodes connected by directed or undirected edges. A tree with $N$ nodes has exactly $N - 1$ edges with no cycles.

### Key Terminology:
- **Root**: Topmost node without parent.
- **Leaf (External Node)**: Node with zero children.
- **Internal Node**: Node with at least one child.
- **Height of Node**: Number of edges on the longest downward path from node to a leaf. Height of leaf is 0.
- **Depth of Node**: Number of edges from root to the node. Depth of root is 0.
- **Degree**: Number of subtrees/children attached to a node.

---

## 2. Tree Taxonomies

| Tree Type | Definition | Key Characteristics |
| :--- | :--- | :--- |
| **Full (Proper) BT** | Every node has either 0 or 2 children. | No node has exactly 1 child. |
| **Complete BT** | All levels filled except possibly the last, which is filled from left to right. | Array representation index: parent $i$, left $2i+1$, right $2i+2$. |
| **Perfect BT** | All internal nodes have 2 children, and all leaves are at the exact same depth. | $2^{h+1}-1$ nodes for height $h$. |
| **Balanced BT (AVL/Red-Black)** | Height difference between left & right subtree is bounded ($|h_L - h_R| \le 1$ for AVL). | Guaranteed $O(\log N)$ operations. |
| **Binary Search Tree (BST)** | For every node $X$: all nodes in left subtree $< X$, all nodes in right subtree $> X$. | In-order traversal produces sorted order! |
| **Trie (Prefix Tree)** | Tree where each edge/node represents a character in an alphabet. | Fast string prefix lookup in $O(L)$ where $L$ is word length. |

---

## 3. Tree Traversals

### Depth-First Search (DFS)
1. **Pre-Order (`Root -> Left -> Right`)**: Useful for copying/serializing a tree.
2. **In-Order (`Left -> Root -> Right`)**: Produces monotonically increasing sorted elements in a BST.
3. **Post-Order (`Left -> Right -> Root`)**: Useful for bottom-up computation (e.g., node deletion, tree height calculation, diameter).

### Breadth-First Search (BFS)
- **Level-Order Traversal**: Uses a FIFO `Queue<TreeNode>` to explore nodes tier-by-tier.
- **Zigzag / Spiral**: Traverses alternate levels left-to-right and right-to-left (using Deque or reversing arrays).

### Morris Traversal (Threading)
- Traverses a binary tree in **$O(1)$ auxiliary space** without stack or recursion.
- Modifies temporary pointers from the in-order predecessor's right pointer back to current node, then restores them.

---

## 4. Time & Space Complexity

| Operation | General Binary Tree | Balanced BST (AVL/Red-Black) | Degenerate BST (Skewed) |
| :--- | :--- | :--- | :--- |
| **Search** | $O(N)$ | $O(\log N)$ | $O(N)$ |
| **Insert** | $O(N)$ | $O(\log N)$ | $O(N)$ |
| **Delete** | $O(N)$ | $O(\log N)$ | $O(N)$ |
| **DFS Traversal** | $O(N)$ time, $O(H)$ space | $O(N)$ time, $O(\log N)$ space | $O(N)$ time, $O(N)$ space |
| **BFS Traversal** | $O(N)$ time, $O(W)$ space | $O(N)$ time, $O(N)$ space | $O(N)$ time, $O(1)$ space |

*(Where $N$ = number of nodes, $H$ = height, $W$ = max width)*

---

## 5. Directory Structure

```
15-trees/
├── README.md
├── easy/
│   ├── 01_BinaryTreePreorderTraversal.java
│   ├── 02_BinaryTreeInorderTraversal.java
│   ├── 03_BinaryTreePostorderTraversal.java
│   ├── 04_MaximumDepthOfBinaryTree.java
│   ├── 05_MinimumDepthOfBinaryTree.java
│   ├── 06_InvertBinaryTree.java
│   ├── 07_SameTree.java
│   ├── 08_SymmetricTree.java
│   ├── 09_PathSumRootToLeaf.java
│   └── 10_SearchInBinarySearchTree.java
├── medium/
│   ├── 01_BinaryTreeLevelOrderTraversal.java
│   ├── 02_BinaryTreeZigzagLevelOrder.java
│   ├── 03_LowestCommonAncestorBT.java
│   ├── 04_ValidateBinarySearchTree.java
│   ├── 05_ConstructTreeFromPreorderInorder.java
│   ├── 06_BinaryTreeRightSideView.java
│   ├── 07_DiameterOfBinaryTree.java
│   ├── 08_KthSmallestElementInBST.java
│   ├── 09_FlattenBinaryTreeToLinkedList.java
│   └── 10_ImplementTriePrefixTree.java
└── hard/
    ├── 01_BinaryTreeMaximumPathSum.java
    ├── 02_SerializeAndDeserializeBinaryTree.java
    ├── 03_VerticalOrderTraversalBinaryTree.java
    ├── 04_BinaryTreeCameras.java
    ├── 05_AllNodesDistanceKInBinaryTree.java
    ├── 06_MorrisTraversalInorderO1Space.java
    ├── 07_AVLTreeSelfBalancing.java
    └── 08_WordSearchTwoTrieBacktracking.java
```
