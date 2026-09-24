/**
 * Problem: Binary Tree Cameras (LeetCode 968)
 * Asked in: Google, Amazon, Microsoft
 * 
 * You are given the root of a binary tree. We install cameras on the tree nodes where
 * each camera can monitor its parent, itself, and its immediate children.
 * Return the minimum number of cameras needed to monitor all nodes of the tree.
 * 
 * Approach:
 * Greedy Bottom-Up DFS (Post-order):
 * Never place cameras on leaf nodes if avoidable; place cameras on parents of leaves!
 * Define 3 states:
 * - 0: NOT_COVERED (Node is not monitored by any camera)
 * - 1: HAS_CAMERA (A camera is installed at this node)
 * - 2: COVERED (Node is safely monitored by one of its children)
 * 
 * Logic:
 * - Null nodes are considered COVERED (2).
 * - If either child is NOT_COVERED (0): Current node MUST place a camera (return 1, cameras++).
 * - Else if either child HAS_CAMERA (1): Current node is now COVERED (return 2).
 * - Else (both children are COVERED): Current node is NOT_COVERED (return 0).
 * - Edge case: If root is NOT_COVERED after traversal, install one camera at root.
 * 
 * Time Complexity: O(N) visiting each node once.
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

static int cameraCount;

    int minCameraCover(TreeNode* root) {
        cameraCount = 0;
        if (dfs(root) == 0) {
            cameraCount++;
        }
        return cameraCount;
    }

    static int dfs(TreeNode* node) {
        if (node == NULL) return 2; // NULL nodes are considered covered

        int leftState = dfs(node->left);
        int rightState = dfs(node->right);

        // If any child is not covered, we must place a camera here
        if (leftState == 0 || rightState == 0) {
            cameraCount++;
            return 1;
        }

        // If any child has a camera, this node is covered
        if (leftState == 1 || rightState == 1) {
            return 2;
        }

        // Both children are covered, so this node is not covered yet
        return 0;
    }

    int main(void) {
        // [0, 0, NULL, 0, 0]
        TreeNode* root = createTreeNode(0);
        root->left = createTreeNode(0);
        root->left->left = createTreeNode(0);
        root->left->right = createTreeNode(0);

        printf("Min cameras: " + minCameraCover(root) + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
