/**
 * Problem: Binary Tree Level Order Traversal (LeetCode 102)
 * Asked in: Amazon, Microsoft, Facebook, Google, Bloomberg
 * 
 * Given the root of a binary tree, return the level order traversal of its nodes'
 * values (i.e., from left to right, level by level).
 * 
 * Approach:
 * Breadth-First Search (BFS) using a FIFO Queue:
 * 1. If root is null, return empty list.
 * 2. Enqueue root.
 * 3. While queue is not empty, get current level size = queue.size().
 * 4. Iterate 'size' times: dequeue node, record its value, enqueue left & right children if non-null.
 * 5. Append current level list to final result.
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(W) where W is max width of tree (up to N/2 in complete binary tree).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

static TreeNode* createTreeNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) exit(1);
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int*> levelOrder(TreeNode* root) {
        int*> result = new ArrayList<>();
        if (root == NULL) return result;

        Queue<TreeNode> queue = new ArrayDeque<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            int* currentLevel = new ArrayList<>(levelSize);

            for (int i = 0; i < levelSize; i++) {
                TreeNode* curr = queue.poll();
                currentLevel.add(curr->val);

                if (curr->left != NULL) queue.offer(curr->left);
                if (curr->right != NULL) queue.offer(curr->right);
            }
            result.add(currentLevel);
        }

        return result;
    }

    int main(void) {
        // [3, 9, 20, NULL, NULL, 15, 7]
        TreeNode* root = createTreeNode(3);
        root->left = createTreeNode(9);
        root->right = createTreeNode(20);
        root->right->left = createTreeNode(15);
        root->right->right = createTreeNode(7);

        printf("Level Order: %d\n", levelOrder(root));
        // Expected: [[3], [9, 20], [15, 7]]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
