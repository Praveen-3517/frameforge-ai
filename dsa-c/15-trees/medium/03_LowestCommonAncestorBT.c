/**
 * Problem: Lowest Common Ancestor of a Binary Tree (LeetCode 236)
 * Asked in: Facebook, Amazon, Microsoft, Apple, Google
 * 
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 * The LCA is defined between two nodes p and q as the lowest node in T that has both
 * p and q as descendants (where we allow a node to be a descendant of itself).
 * 
 * Approach:
 * Post-order recursive DFS:
 * 1. Base case: if root is null, or root == p, or root == q, return root.
 * 2. Recurse on left and right subtrees.
 * 3. If left != null && right != null, both targets were found in distinct subtrees;
 *    hence current root is their lowest common ancestor!
 * 4. Otherwise, return the non-null child (left != null ? left : right).
 * 
 * Time Complexity: O(N) visiting each node at most once.
 * Space Complexity: O(H) call stack where H is tree height.
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

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q) {
            return root;
        }

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left != NULL && right != NULL) {
            return root;
        }

        return left != NULL ? left : right;
    }

    int main(void) {
        // [3, 5, 1, 6, 2, 0, 8, NULL, NULL, 7, 4]
        TreeNode* root = createTreeNode(3);
        root->left = createTreeNode(5);
        root->right = createTreeNode(1);
        root->left->left = createTreeNode(6);
        root->left->right = createTreeNode(2);
        root->right->left = createTreeNode(0);
        root->right->right = createTreeNode(8);
        root->left->right->left = createTreeNode(7);
        root->left->right->right = createTreeNode(4);

        TreeNode* lca1 = lowestCommonAncestor(root, root->left, root->right); // LCA(5, 1) = 3
        printf("LCA(5, 1): " + (lca1 != NULL ? lca1->val : "NULL") + " (Expected: 3)\n");

        TreeNode* lca2 = lowestCommonAncestor(root, root->left, root->left->right->right); // LCA(5, 4) = 5
        printf("LCA(5, 4): " + (lca2 != NULL ? lca2->val : "NULL") + " (Expected: 5)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
