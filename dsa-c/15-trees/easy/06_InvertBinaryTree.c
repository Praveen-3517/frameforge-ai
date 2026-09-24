/**
 * Problem: Invert Binary Tree (LeetCode 226)
 * Asked in: Google, Amazon, Twitter, Microsoft
 * 
 * Given the root of a binary tree, invert the tree (mirror reflection) and return its root.
 * 
 * Approach:
 * Recursively invert left and right subtrees, then swap the left and right pointers.
 * 
 * Time Complexity: O(N) where N is number of nodes.
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

TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return NULL;

        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        root->left = right;
        root->right = left;

        return root;
    }

    // Helper to print inorder
    static void printInorder(TreeNode* root) {
        if (root == NULL) return;
        printInorder(root->left);
        printf("%s", root->val + " ");
        printInorder(root->right);
    }

    int main(void) {
        // Tree: 4, left: 2 (1, 3), right: 7 (6, 9)
        TreeNode* root = createTreeNode(4);
        root->left = createTreeNode(2);
        root->right = createTreeNode(7);
        root->left->left = createTreeNode(1);
        root->left->right = createTreeNode(3);
        root->right->left = createTreeNode(6);
        root->right->right = createTreeNode(9);

        printf("%s", "Original Inorder: ");
        printInorder(root);
        printf("\n");

        TreeNode* inverted = invertTree(root);

        printf("%s", "Inverted Inorder: ");
        printInorder(inverted);
        printf("\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
