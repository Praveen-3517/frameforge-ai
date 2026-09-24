/**
 * Problem: Path Sum (LeetCode 112)
 * Asked in: Amazon, Microsoft, Facebook, Oracle
 * 
 * Given the root of a binary tree and an integer targetSum, return true if the tree
 * has a root-to-leaf path such that adding up all the values along the path equals targetSum.
 * A leaf is a node with no children.
 * 
 * Approach:
 * Recursive DFS:
 * - If root == null, return false.
 * - If root is a leaf (left == null && right == null), check if root.val == targetSum.
 * - Recurse on left and right with remaining sum: targetSum - root.val.
 * 
 * Time Complexity: O(N) visiting each node at most once.
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

bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == NULL) return false;

        // Check if current node is a leaf
        if (root->left == NULL && root->right == NULL) {
            return targetSum == root->val;
        }

        int remainingSum = targetSum - root->val;
        return hasPathSum(root->left, remainingSum) || hasPathSum(root->right, remainingSum);
    }

    int main(void) {
        // [5, 4, 8, 11, NULL, 13, 4, 7, 2, NULL, NULL, NULL, 1]
        TreeNode* root = createTreeNode(5);
        root->left = createTreeNode(4);
        root->right = createTreeNode(8);
        root->left->left = createTreeNode(11);
        root->left->left->left = createTreeNode(7);
        root->left->left->right = createTreeNode(2);
        root->right->left = createTreeNode(13);
        root->right->right = createTreeNode(4);
        root->right->right->right = createTreeNode(1);

        printf("Path sum 22: " + hasPathSum(root, 22) + " (Expected: true)\n");
        printf("Path sum 26: " + hasPathSum(root, 26) + " (Expected: true)\n");
        printf("Path sum 50: " + hasPathSum(root, 50) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
