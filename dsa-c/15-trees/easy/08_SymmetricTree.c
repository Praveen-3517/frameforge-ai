/**
 * Problem: Symmetric Tree (LeetCode 101)
 * Asked in: Amazon, Microsoft, Bloomberg, Apple
 * 
 * Given the root of a binary tree, check whether it is a mirror of itself
 * (i.e., symmetric around its center).
 * 
 * Approach:
 * Helper function isMirror(t1, t2):
 * - If both null -> true.
 * - If one null -> false.
 * - Return (t1.val == t2.val) && isMirror(t1.left, t2.right) && isMirror(t1.right, t2.left).
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

bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        return isMirror(root->left, root->right);
    }

    static bool isMirror(TreeNode* t1, TreeNode* t2) {
        if (t1 == NULL && t2 == NULL) return true;
        if (t1 == NULL || t2 == NULL) return false;
        return (t1->val == t2->val) 
            && isMirror(t1->left, t2->right) 
            && isMirror(t1->right, t2->left);
    }

    int main(void) {
        // [1, 2, 2, 3, 4, 4, 3] -> Symmetric
        TreeNode* root1 = createTreeNode(1);
        root1->left = createTreeNode(2);
        root1->right = createTreeNode(2);
        root1->left->left = createTreeNode(3);
        root1->left->right = createTreeNode(4);
        root1->right->left = createTreeNode(4);
        root1->right->right = createTreeNode(3);

        printf("Tree 1 Symmetric: " + isSymmetric(root1) + " (Expected: true)\n");

        // [1, 2, 2, NULL, 3, NULL, 3] -> Not symmetric
        TreeNode* root2 = createTreeNode(1);
        root2->left = createTreeNode(2);
        root2->right = createTreeNode(2);
        root2->left->right = createTreeNode(3);
        root2->right->right = createTreeNode(3);

        printf("Tree 2 Symmetric: " + isSymmetric(root2) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
