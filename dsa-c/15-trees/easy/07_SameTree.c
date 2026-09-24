/**
 * Problem: Same Tree (LeetCode 100)
 * Asked in: Amazon, Google, Bloomberg
 * 
 * Given the roots of two binary trees p and q, write a function to check if they
 * are the same or not. Two binary trees are considered the same if they are
 * structurally identical, and the nodes have the same value.
 * 
 * Approach:
 * Recursive DFS:
 * - If both nodes are null, return true.
 * - If only one is null or values differ, return false.
 * - Return isSameTree(p.left, q.left) && isSameTree(p.right, q.right).
 * 
 * Time Complexity: O(min(N, M)) where N, M are number of nodes.
 * Space Complexity: O(min(H1, H2)) stack space.
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

bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == NULL && q == NULL) return true;
        if (p == NULL || q == NULL) return false;
        if (p->val != q->val) return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }

    int main(void) {
        // Tree p: [1, 2, 3]
        TreeNode* p = createTreeNode(1);
        p->left = createTreeNode(2);
        p->right = createTreeNode(3);

        // Tree q: [1, 2, 3]
        TreeNode* q = createTreeNode(1);
        q->left = createTreeNode(2);
        q->right = createTreeNode(3);

        printf("Are trees equal: " + isSameTree(p, q) + " (Expected: true)\n");

        TreeNode* r = createTreeNode(1);
        r->left = createTreeNode(2); // right is NULL

        printf("Are trees equal: " + isSameTree(p, r) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
