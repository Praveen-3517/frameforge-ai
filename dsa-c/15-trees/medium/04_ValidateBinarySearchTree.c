/**
 * Problem: Validate Binary Search Tree (LeetCode 98)
 * Asked in: Amazon, Bloomberg, Microsoft, Facebook, Apple
 * 
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 * A valid BST is defined as:
 * - The left subtree of a node contains only nodes with keys strictly less than the node's key.
 * - The right subtree of a node contains only nodes with keys strictly greater than the node's key.
 * - Both the left and right subtrees must also be binary search trees.
 * 
 * Approach:
 * Range DFS with Long bounds:
 * Pass allowable range [minVal, maxVal] for each node.
 * - For root: (-infinity, +infinity).
 * - For left child of node: (minVal, node.val).
 * - For right child of node: (node.val, maxVal).
 * - If current node value not in (minVal, maxVal), return false.
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

bool isValidBST(TreeNode* root) {
        return validate(root, LLONG_MIN, LLONG_MAX);
    }

    static bool validate(TreeNode* node, long long minVal, long long maxVal) {
        if (node == NULL) return true;

        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }

        return validate(node->left, minVal, node->val) 
            && validate(node->right, node->val, maxVal);
    }

    int main(void) {
        // Valid BST: [2, 1, 3]
        TreeNode* root1 = createTreeNode(2);
        root1->left = createTreeNode(1);
        root1->right = createTreeNode(3);
        printf("Tree 1 Valid: " + isValidBST(root1) + " (Expected: true)\n");

        // Invalid BST: [5, 1, 4, NULL, NULL, 3, 6]
        TreeNode* root2 = createTreeNode(5);
        root2->left = createTreeNode(1);
        root2->right = createTreeNode(4);
        root2->right->left = createTreeNode(3);
        root2->right->right = createTreeNode(6);
        printf("Tree 2 Valid: " + isValidBST(root2) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
