/**
 * Problem: Minimum Depth of Binary Tree (LeetCode 111)
 * Asked in: Facebook, Amazon, Bloomberg
 * 
 * Given a binary tree, find its minimum depth.
 * The minimum depth is the number of nodes along the shortest path from the
 * root node down to the nearest leaf node (a node with no children).
 * 
 * Approach:
 * If a node has only one child, we cannot consider the null path as depth 0!
 * We must continue down the non-null child's path.
 * - If root == null, return 0.
 * - If left is null, return 1 + minDepth(right).
 * - If right is null, return 1 + minDepth(left).
 * - Otherwise return 1 + min(minDepth(left), minDepth(right)).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H) recursion stack.
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

int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        if (root->left == NULL) return 1 + minDepth(root->right);
        if (root->right == NULL) return 1 + minDepth(root->left);
        return 1 + MIN(minDepth(root->left), minDepth(root->right));
    }

    int main(void) {
        // [3, 9, 20, NULL, NULL, 15, 7]
        TreeNode* root1 = createTreeNode(3);
        root1->left = createTreeNode(9);
        root1->right = createTreeNode(20);
        root1->right->left = createTreeNode(15);
        root1->right->right = createTreeNode(7);

        printf("Min Depth 1: " + minDepth(root1) + " (Expected: 2)\n");

        // Skewed tree: 2 -> 3 -> 4 -> 5 -> 6
        TreeNode* root2 = createTreeNode(2);
        root2->right = createTreeNode(3);
        root2->right->right = createTreeNode(4);
        root2->right->right->right = createTreeNode(5);
        root2->right->right->right->right = createTreeNode(6);

        printf("Min Depth 2: " + minDepth(root2) + " (Expected: 5)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
