/**
 * Problem: Maximum Depth of Binary Tree (LeetCode 104)
 * Asked in: Amazon, Apple, Microsoft, Google
 * 
 * A binary tree's maximum depth is the number of nodes along the longest path
 * from the root node down to the farthest leaf node.
 * 
 * Approach:
 * Depth-First Search (DFS) Recursion:
 * - Base case: if root is null, depth is 0.
 * - Recursive step: maxDepth(root) = 1 + max(maxDepth(root.left), maxDepth(root.right)).
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(H) recursion stack where H is tree height.
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

int maxDepth(TreeNode* root) {
        if (root == NULL) return 0;
        return 1 + MAX(maxDepth(root->left), maxDepth(root->right));
    }

    int main(void) {
        // [3, 9, 20, NULL, NULL, 15, 7]
        TreeNode* root = createTreeNode(3);
        root->left = createTreeNode(9);
        root->right = createTreeNode(20);
        root->right->left = createTreeNode(15);
        root->right->right = createTreeNode(7);

        printf("Max Depth: " + maxDepth(root) + " (Expected: 3)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
