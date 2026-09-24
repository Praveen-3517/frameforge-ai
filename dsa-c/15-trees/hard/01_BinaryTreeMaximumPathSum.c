/**
 * Problem: Binary Tree Maximum Path Sum (LeetCode 124)
 * Asked in: Facebook, Google, Amazon, Microsoft, ByteDance
 * 
 * A path in a binary tree is a sequence of nodes where each pair of adjacent nodes
 * has an edge connecting them. A node can only appear in the sequence at most once.
 * The path sum is the sum of the node's values in the path.
 * Given the root of a binary tree, return the maximum path sum of any non-empty path.
 * 
 * Approach:
 * Post-order DFS:
 * For each node:
 * - Recursively find max path gain from left and right children (clamped to >= 0).
 * - Max path sum passing THROUGH current node as turning point:
 *     node.val + leftGain + rightGain.
 * - Update global maximum.
 * - Return to parent: node.val + max(leftGain, rightGain) (since a path cannot branch to both children if extending to parent).
 * 
 * Time Complexity: O(N) visiting each node once.
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

static int globalMax;

    int maxPathSum(TreeNode* root) {
        globalMax = INT_MIN;
        maxGain(root);
        return globalMax;
    }

    static int maxGain(TreeNode* node) {
        if (node == NULL) return 0;

        // If gain is negative, ignore that branch (take 0)
        int leftGain = MAX(0, maxGain(node->left));
        int rightGain = MAX(0, maxGain(node->right));

        // Price of the path where current node is the highest point
        int currentPathSum = node->val + leftGain + rightGain;
        globalMax = MAX(globalMax, currentPathSum);

        // Return max single branch gain to parent
        return node->val + MAX(leftGain, rightGain);
    }

    int main(void) {
        // [-10, 9, 20, NULL, NULL, 15, 7]
        TreeNode* root = createTreeNode(-10);
        root->left = createTreeNode(9);
        root->right = createTreeNode(20);
        root->right->left = createTreeNode(15);
        root->right->right = createTreeNode(7);

        printf("Max Path Sum: " + maxPathSum(root) + " (Expected: 42)\n");
        // Path: 15 -> 20 -> 7 = 42
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
