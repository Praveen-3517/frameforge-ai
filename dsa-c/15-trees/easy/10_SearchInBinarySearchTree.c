/**
 * Problem: Search in a Binary Search Tree (LeetCode 700)
 * Asked in: Amazon, Adobe, Microsoft
 * 
 * You are given the root of a binary search tree (BST) and an integer val.
 * Find the node in the BST that the node's value equals val and return the
 * subtree rooted with that node. If such a node does not exist, return null.
 * 
 * Approach:
 * BST Property:
 * - If target val < root.val, search in left subtree.
 * - If target val > root.val, search in right subtree.
 * - If target val == root.val, return root.
 * Can be solved iteratively in O(1) extra space!
 * 
 * Time Complexity: O(H) where H is tree height (O(log N) for balanced BST, O(N) worst case).
 * Space Complexity: O(1) auxiliary space using iterative search.
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

TreeNode* searchBST(TreeNode* root, int val) {
        TreeNode* curr = root;
        while (curr != NULL && curr->val != val) {
            if (val < curr->val) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return curr;
    }

    int main(void) {
        // BST: [4, 2, 7, 1, 3]
        TreeNode* root = createTreeNode(4);
        root->left = createTreeNode(2);
        root->right = createTreeNode(7);
        root->left->left = createTreeNode(1);
        root->left->right = createTreeNode(3);

        TreeNode* result2 = searchBST(root, 2);
        printf("Search 2: " + (result2 != NULL ? result2->val : "NULL") + " (Expected: 2)\n");

        TreeNode* result5 = searchBST(root, 5);
        printf("Search 5: " + (result5 != NULL ? result5->val : "NULL") + " (Expected: NULL)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
